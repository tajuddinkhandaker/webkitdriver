/*
 * Copyright 2007-2010 WebDriver committers
 * Copyright 2007-2010 Google Inc.
 * Portions copyright 2007 ThoughtWorks, Inc
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

package org.openqa.selenium.webkit;

import com.google.common.io.CharStreams;
import com.google.common.io.InputSupplier;

import org.openqa.selenium.Alert;
import org.openqa.selenium.By;
import org.openqa.selenium.Capabilities;
import org.openqa.selenium.Cookie;
import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.NoAlertPresentException;
import org.openqa.selenium.NoSuchElementException;
import org.openqa.selenium.NoSuchFrameException;
import org.openqa.selenium.NoSuchWindowException;
import org.openqa.selenium.OutputType;
import org.openqa.selenium.SearchContext;
import org.openqa.selenium.StaleElementReferenceException;
import org.openqa.selenium.TakesScreenshot;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebDriverException;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.html5.AppCacheEntry;
import org.openqa.selenium.html5.AppCacheStatus;
import org.openqa.selenium.html5.ApplicationCache;
import org.openqa.selenium.html5.BrowserConnection;
import org.openqa.selenium.html5.DatabaseStorage;
import org.openqa.selenium.html5.LocalStorage;
import org.openqa.selenium.html5.Location;
import org.openqa.selenium.html5.LocationContext;
import org.openqa.selenium.html5.ResultSet;
import org.openqa.selenium.html5.SessionStorage;
import org.openqa.selenium.html5.WebStorage;
import org.openqa.selenium.internal.Base64Encoder;
import org.openqa.selenium.internal.FindsById;
import org.openqa.selenium.internal.FindsByLinkText;
import org.openqa.selenium.internal.FindsByName;
import org.openqa.selenium.internal.FindsByTagName;
import org.openqa.selenium.internal.FindsByXPath;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.URL;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Date;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.TimeUnit;
import java.util.logging.Level;
import java.util.logging.Logger;

public class WebKitDriver implements WebDriver, SearchContext, JavascriptExecutor,
        FindsById, FindsByLinkText, FindsByXPath, FindsByName, FindsByTagName,
        BrowserConnection, ApplicationCache, DatabaseStorage, LocationContext,
        WebStorage, TakesScreenshot {

  private static final Logger LOGGER = Logger.getLogger(WebKitDriver.class.getName());

  private static final String USER_AGENT_KEY = "user-agent";

  private long default_controller = 0;
  private long controller = 0;
  private WebKitInterface jni = WebKitJNI.getInstance();
  private WebKitAlert currentAlert;
  private long implicitWait = 0;
  private Pipe pipe;

  /**
   * Pipe class provides communication between java processes via TCP sockets.
   */
  private class Pipe {
    private int serverPort;
    private ServerSocket serverSocket;

    public Pipe() {
      try {
        serverSocket = new ServerSocket(0);
        serverPort = serverSocket.getLocalPort();
      } catch (IOException e) {
        throw new WebDriverException("WebKitDriver server socket creation error: " +
            e.getMessage());
      }

    }

    public int getServerPort() {
      return serverPort;
    }

    public Socket connect() {
      try {
        Socket dataSocket = serverSocket.accept();
        dataSocket.setTcpNoDelay(true);
        return dataSocket;
      } catch (IOException e) {
        throw new WebDriverException("WebKitDriver client socket creation error:" +
            e.getMessage());
      }
    }
  }

  /**
   * Forwarder class implements InvocationHandler interface and
   * used as a dymanic proxy for invoking JNI methods in a separate
   * java process hosting headless WebKit library.
  */
  private class Forwarder implements InvocationHandler
  {
    private Process wrapper;
    private BufferedReader in;
    private Socket dataSocket;
    private DataOutputStream dataOut;
    private DataInputStream dataIn;
    private boolean isRunning;
    private WebKitDriver parent;

    public Forwarder(WebKitDriver parent) {
        this.parent = parent;

        // Get the classpath values for the spawned process
        String webkitdriverClassPath = WebKitDriver.class.getProtectionDomain().
                getCodeSource().getLocation().toString();
        String seleniumClassPath = WebDriver.class.getProtectionDomain().
                getCodeSource().getLocation().toString();
        String classPath = webkitdriverClassPath + System.getProperty("path.separator")
                + seleniumClassPath;

        ProcessBuilder pb = new ProcessBuilder(System.getProperty("java.home") +"/bin/java",
              "-classpath", classPath, "-Djava.library.path=" + System.getProperty("java.library.path"),
              "org.openqa.selenium.webkit.WebKitWrapper", Integer.toString(pipe.getServerPort()));

        pb.redirectErrorStream(true);

        String sep = System.getProperty("path.separator");
        String[] paths = System.getProperty("java.class.path").split(sep);

        try {
            wrapper = pb.start();
            dataSocket = pipe.connect();
            dataOut = new DataOutputStream(dataSocket.getOutputStream());
            dataIn  = new DataInputStream(dataSocket.getInputStream());
            in  = new BufferedReader(new InputStreamReader(wrapper.getInputStream()));
            isRunning = true;
        } catch (IOException e) {
            throw new WebDriverException("WebKitDriver wrapper could not be spawned: "
                     + e.getMessage());
        }
    }

    public Object invoke(Object proxy, Method method, Object[] args) {
        if (!isRunning) {
           throw new WebDriverException("Child process is not running");
        }
        boolean endOfSession = false;
        try {
            // Serialize and send request to remote process
            WebKitSerializer.putMethodIntoStream(dataOut, method, args);
            dataOut.flush();

            // Print child's standard out
            while (in.ready()) {
                LOGGER.log(Level.INFO, "Child's out: " + in.readLine());
            }

            // Receive response and deserialize it
            Object result = WebKitSerializer.deserialize(dataIn, parent);
            if (method.getName().equals("destroy") && (Long)(args[0]) == 0) {
                endOfSession = true;
            }
            dataOut.writeBoolean(endOfSession);
            return result;
        } catch (Exception e) {
            String wrapperOutput = "";
            try {
                isRunning = false;
                //dataSocket.close();
                InputSupplier<InputStream> wrapperInputSupplier = new InputSupplier<InputStream>() {
                  @Override
                  public InputStream getInput() {
                    return wrapper.getInputStream();
                  }
                };

                wrapperOutput = CharStreams.toString(
                    CharStreams.newReaderSupplier(wrapperInputSupplier, Charset.defaultCharset()));

            } catch (IOException ioExc) {
                // Error while reading error output stream.
                throw new WebDriverException("Unable to read error output stream from process.",
                    ioExc);
            }
            String errorMessage = "Unexpected invocation exception on method " + method.getName() + "\n"
                    + "Output from the process is: " + wrapperOutput;
            throw new WebDriverException(errorMessage, e);
        }
    }
  }

  /**
   * Create a WebKitDriver instance.
   */
  public WebKitDriver() {
    this(null);
  }

  /**
   * Creates a new WebKitDriver instance with the given capabilities. Currently only the
   * "user-agent" is honored. If this is set, then the created WebKitDriver instance will have this
   * User-Agent string.
   *
   * If a capability with no user-agent strings set is provided, then the created WebKitDriver
   * instance will use the default Apple WebKit user-agent.
   *
   * @param capabilities The {@link Capabilities} that specifies the properties of the WebKitDriver
   *     instance to be created.
   */
  public WebKitDriver(Capabilities capabilities) {
    // Create new WebkitDriver process, and establish socket connection with it.
    if (pipe == null)
      pipe = new Pipe();
    Forwarder handler = new Forwarder(this);
    jni = (WebKitInterface)Proxy.newProxyInstance(
        WebKitInterface.class.getClassLoader(),
        new Class[] { WebKitInterface.class },
        handler);
    // Check if a user-agent string is supplied with the capabilities.
    String userAgent = null;
    if (capabilities != null && capabilities.getCapability(USER_AGENT_KEY) != null) {
      userAgent = capabilities.getCapability(USER_AGENT_KEY).toString();
    }

    controller = jni.create(userAgent);
    default_controller = controller;
  }

  public WebKitDriver(long ref) {
    controller = ref;
  }

  public WebKitInterface jni() {
    return jni;
  }

  public long getController() {
    return controller;
  }

  public long getDefaultController() {
    return default_controller;
  }

  private WebKitWebElement rootNode()
  {
    try {
      return new WebKitWebElement(this, jni.getDocument(controller));
    } catch (StaleElementReferenceException e) {
      throw new NoSuchElementException(String.format("Document element is stale"));
    }
  }

  public void get(String url) {
    long status = jni.get(controller, url);
    if (status == 0) {
      throw new WebDriverException();
    }
  }

  public String getCurrentUrl() {
    assertInitialized();
    return jni.getUrl(controller);
  }

  public String getTitle() {
    return jni.getTitle(controller);
  }

  public WebElement findElement(By by) {
      long start = System.currentTimeMillis();
      while (true) {
        try {
          return by.findElement((SearchContext)this);
        } catch (NoSuchElementException e) {
          if (System.currentTimeMillis() - start > implicitWait) {
            throw e;
          }
          sleepQuietly(100);
        }
      }
  }

  public List<WebElement> findElements(By by) {
      long start = System.currentTimeMillis();
      List<WebElement> found;
      while (true) {
          found = by.findElements((SearchContext)this);
          if (!found.isEmpty() || System.currentTimeMillis() - start > implicitWait) {
            break;
          }
        sleepQuietly(100);
      }
      return found;
  }

  public String getPageSource() {
    return jni.getPageSource(controller);
  }

  public void close() {
    // Close current window and switch to default window.
    jni.destroy(controller);
    switchToDefaultWindow();
  }

  private void switchToDefaultWindow()
  {
    String wid = String.valueOf(default_controller);
    Set<String> handles = getWindowHandles();
    if (handles.contains(wid)) {
        switchTo().window(wid);
        return;
    }
    //If default window is closed, switch to the first
    // available window and make it default.
    if (handles.isEmpty()) {
      // All windows are closed, consider driver quit
      quit();
    } else {
      wid = handles.iterator().next();
      switchTo().window(wid);
      default_controller = controller;
    }
  }

  public void quit()
  {
    if (default_controller != 0) {
      for(String handle : getWindowHandles()) {
        long ref = Long.parseLong(handle);
        jni.destroy(ref);
      }
      controller = 0;
      default_controller = 0;
    }
    jni.deleteCookie(controller, null);
    // This call does nothing when called for single process webkitdriver.
    // It is used to terminate webkitdriver child process in multiprocess or remote use case
    jni.destroy(0);
  }

  public Set<String> getWindowHandles() {
    Set<String> allHandles = new HashSet<String>();
    if (default_controller != 0) {
      String handles = jni.getAllWindowHandles();
      if (handles.length() != 0) {
        for (String h : handles.split(","))    {
            allHandles.add(h);
        }
      }
    }
    return allHandles;
  }

  public String getWindowHandle() {
    return jni.getWindowHandle(controller);
  }

  private Object parseArgument (Object obj) {
    if (! (obj instanceof Number || obj instanceof String ||
        obj instanceof Collection || obj instanceof Boolean ||
        obj.getClass().isArray() || obj instanceof WebElement))
      throw new IllegalArgumentException(obj.toString());

    if (obj instanceof WebElement || obj instanceof Integer ||
        obj instanceof Boolean || obj instanceof Long ||
        obj instanceof String || obj instanceof Double ||
        obj.getClass().isArray()) {
      return obj;
    }

    if (obj instanceof Collection)
      return ((Collection)obj).toArray();
    else return null;
  }

  public Object executeScript(String script, Object... args) {
    if (getCurrentUrl().length() == 0)
      throw new WebDriverException("Calling script on an empty page");

    ArrayList<Object> scriptArgs = new ArrayList<Object>();
      for (Object obj : args)
        scriptArgs.add(parseArgument(obj));
    scriptArgs.add(script);
    Object result = jni.evaluateJS(this, controller, scriptArgs.toArray());
    if (result instanceof Exception) throw new WebDriverException();
    return result;
  }

  public TargetLocator switchTo() {
    return new WebKitTargetLocator();
  }

  public Navigation navigate() {
    return new WebKitNavigation();
  }

  public WebElement findElementByLinkText(String selector) {
    return rootNode().findElementByLinkText(selector);
  }

  public List<WebElement> findElementsByLinkText(String selector) {
    return rootNode().findElementsByLinkText(selector);
  }

  public WebElement findElementById(String id) {
    return rootNode().findElementById(id);
  }

  public List<WebElement> findElementsById(String id) {
    return rootNode().findElementsById(id);
  }

  public WebElement findElementByName(String name) {
    return rootNode().findElementByName(name);
  }

  public List<WebElement> findElementsByName(String name) {
    return rootNode().findElementsByName(name);
  }

  public WebElement findElementByTagName(String name) {
    return rootNode().findElementByTagName(name);
  }

  public List<WebElement> findElementsByTagName(String name) {
    return rootNode().findElementsByTagName(name);
  }

  public WebElement findElementByXPath(String selector) {
    return rootNode().findElementByXPath(selector);
  }

  public List<WebElement> findElementsByXPath(String selector) {
    return rootNode().findElementsByXPath(selector);
  }


  public boolean isJavascriptEnabled() {
    return jni.isJavascriptEnabled(controller);
  }

  public void setJavascriptEnabled(boolean enableJavascript) {
    jni.setJavascriptEnabled(controller, enableJavascript);
  }

  public ResultSet executeSQL(String db, String query, Object... args) {
    // Due to interface limitations we have to parse db string since it contains
    // all information to open DB
    String []temp = db.split("^\\s*'");
    if (temp.length == 2) temp[0] = temp[1];
    String[] dbparams = temp[0].split("(\\s*'*\\s*,\\s*'*)|(\\s*'\\s*$)");

    if (dbparams.length != 4)
      throw new WebDriverException("Wrong number of arguments for DB opening");
    // since we are getting DB size as a string and not as a number we have to
    // parse it ourselves in order to get actual number it's passed to JS engine currently
    // to do the parsing part
    Object len = executeScript("return "+dbparams[3]+";");
    if (!(len instanceof Long)) throw new WebDriverException ("Incorrect DB size");
    long dbRef = jni.openDatabase(controller, dbparams[0], dbparams[1], dbparams[2], (Long)len);
    Object result = jni.executeSQL(controller, dbRef, query, args);
    jni.closeDatabase(dbRef);
    if (result instanceof ResultSet) return (ResultSet)result;
    if (result instanceof WebDriverException) throw (WebDriverException)result;

    throw new WebDriverException("Unknown result type");
  }

  public List<AppCacheEntry> getAppCache()
  {
    List<AppCacheEntry> result = (List<AppCacheEntry>) jni.getAppCache(controller);
    if(result == null){
      throw new WebDriverException("Can not get application cache. Timeout exceeded");
    }
    return result;
  }

  public AppCacheStatus getStatus()
  {
    int status = jni.getAppCacheStatus(controller);
    if (status < 0) {
      throw new WebDriverException("Can not determine application cache status");
    }
    return AppCacheStatus.values()[status];
  }

  public void clear() {
    //TODO: implement
  }

  public boolean isOnline() {
    long state = jni.online();
    if (state == 1)
      return true;
    if (state == 0)
      return false;
    throw new WebDriverException("Can not determine current network state");
  }

  public void setOnline(boolean online) {
    long status = jni.setOnline(online);
    if (status != 0)
      throw new WebDriverException("Can not change current network state");
  }

  private boolean isAlert() {
      if (jni.getAlertText(controller, false) == null)
          return false;

      currentAlert = new WebKitAlert();
      return true;
  }

  private class WebKitTargetLocator implements TargetLocator {
    public WebDriver frame(int frameIndex) {
      long status = jni.selectFrameByIdx(controller, frameIndex);
      if (status == 0) {
        throw new NoSuchFrameException("Cannot find frame: " + frameIndex);
      }
      return WebKitDriver.this;
    }

    public WebDriver frame(String name) {
      long status = jni.selectFrameByName(controller, name);
      if (status == 0) {
        throw new NoSuchFrameException("Cannot find frame: " + name);
      }
      return WebKitDriver.this;
    }

    public WebDriver window(String windowId) {
      // Use default_controller, because controller may be destroyed at the moment
      long ref = jni.selectWindow(default_controller, windowId);
      if (ref == 0) {
        throw new NoSuchWindowException("Cannot find window: " + windowId);
      }
      controller = ref;
      return WebKitDriver.this;
    }

    public WebDriver defaultContent() {
      switchToDefaultWindow();
      if (controller != 0) {
        long status = jni.defaultContent(controller);
        if (status == 0) {
          throw new WebDriverException("Error switching to default content");
        }
      }
      return WebKitDriver.this;
    }

    public WebElement activeElement() {
      return new WebKitWebElement(WebKitDriver.this, jni.activeElement(controller));
    }

    @SuppressWarnings("unused")
    public Alert alert() {
        if (currentAlert != null || isAlert()) {
          return currentAlert;
        }

        throw new NoAlertPresentException();
      }

    /* (non-Javadoc)
     * @see org.openqa.selenium.WebDriver.TargetLocator#frame(org.openqa.selenium.WebElement)
     */
    @Override
    public WebDriver frame(WebElement element) {
      throw new UnsupportedOperationException("Finding frame by element is not supported.");
    }
  }

  private class WebKitNavigation implements Navigation {
    public void back() {
      jni.goBack(controller);
    }

    public void forward() {
      jni.goForward(controller);
    }

    public void to(String url) {
      get(url);
    }

    public void to(URL url) {
      get(url.toString());
    }

    public void refresh() {
      jni.refresh(controller);
    }
  }

    public Options manage() {
        return new WebKitOptions();
    }

     private class WebKitOptions implements Options {
        public ImeHandler ime() {
          throw new UnsupportedOperationException("ime");
        }

        private void verifyDomain(Cookie cookie, String expectedDomain) {
          String domain = cookie.getDomain();
          if (domain == null) {
            return;
          }

          if ("".equals(domain)) {
            throw new WebDriverException(
                "Domain must not be an empty string. Consider using null instead");
          }

          // Line-noise-tastic
          if (domain.matches(".*[^:]:\\d+$")) {
            domain = domain.replaceFirst(":\\d+$", "");
          }

          expectedDomain = expectedDomain.startsWith(".") ? expectedDomain : "." + expectedDomain;
          domain = domain.startsWith(".") ? domain : "." + domain;

          if (!expectedDomain.endsWith(domain)) {
            throw new WebDriverException(
                String.format(
                    "You may only add cookies that would be visible to the current domain: %s => %s",
                    domain, expectedDomain));
          }
        }

        /**
         * Cookie fields separated by TAB symbol:
         * 0 - domain - The domain that created AND that can read the variable.
         * 1 - flag - A TRUE/FALSE value indicating if all machines within a given
         *      domain can access the variable. This value is set automatically
         *      by the browser, depending on the value you set for domain.
         * 2 - path - The path within the domain that the variable is valid for.
         * 3 - secure - A TRUE/FALSE value indicating if a secure connection with
         *      the domain is needed to access the variable.
         * 4 - expiration - The UNIX time that the variable will expire on. UNIX time
         *      is defined as the number of seconds since Jan 1, 1970 00:00:00 GMT.
         * 5 - name - The name of the variable.
         * 6 - value - The value of the variable.
        **/
        public void addCookie(Cookie cookie) {

            //controller.evalJS("document.cookie =\"" + cookie.toString() + "\"");

            if (cookie.getName().length() == 0)
                return;

            String cookieStr = cookie.getName() + "=" + cookie.getValue();

            if (cookie.getExpiry() != null)
                cookieStr += ";expires=" + cookie.getExpiry().toGMTString();

            if (cookie.getPath() != null)
            {
                cookieStr += ";path=" + cookie.getPath();
            }

            if (cookie.getDomain() != null)
            {
                try {
                    String cookieDomain = getDomainForCookie();
                    verifyDomain(cookie, cookieDomain);
                    cookieStr += ";domain=" + cookie.getDomain();
                } catch (Exception e) {
                    System.out.println(e.getMessage());
                    return;
                }
            }

            if (cookie.isSecure())
                cookieStr += ";secure";

            if (jni.setCookie(controller, cookieStr) == 0)
                throw new WebDriverException("Add cookie error");
        }

        public Cookie getCookieNamed(String name) {
            //controller.evalJS("document.cookie =\"" + name + "=; expires=Thu, 01-Jan-70 00:00:01 GMT;\"");

            String rawCookies = jni.getCookieJar(controller);

            while (true)
            {
                final int cookieFieldsNum = 7;
                String[] field = rawCookies.split("\t", cookieFieldsNum + 1);

                if (field.length < cookieFieldsNum)
                    break;

                if (name.equals(field[5]))
                    return new Cookie(field[5], field[6], field[0], field[2],
                        new Date(Long.parseLong(field[4].trim()) * 1000));

                if (field.length < cookieFieldsNum + 1)
                    break;

                rawCookies = field[cookieFieldsNum];
            }

            // return new Cookie("", "");
            return null;
        }

        public void deleteCookieNamed(String name) {
            //controller.evalJS("document.cookie =\"" + name + "=; expires=Thu, 01-Jan-70 00:00:01 GMT;\"");
            jni.deleteCookie(controller, name);
        }

        public void deleteCookie(Cookie cookie) {
            String inRawCookies = jni.getCookieJar(controller);

            if (inRawCookies.length() == 0)
                return;

            String outRawCookies = "";
            String idCookie = cookie.getDomain() + cookie.getPath() + cookie.getName();
            boolean modified = false;

            while (true)
            {
                final int cookieFieldsNum = 7;
                String[] field = inRawCookies.split("\t", cookieFieldsNum + 1);

                if (field.length < cookieFieldsNum)
                    break;

                if (idCookie.equals(field[0] + field[2] + field[5]))
                {
                    modified = true;
                } else {
                    for (int i = 0; i < cookieFieldsNum; i++)
                        outRawCookies += "\t" + field[i];
                }

                if (field.length < cookieFieldsNum + 1)
                    break;

                inRawCookies = field[cookieFieldsNum];
            }

            if (modified)
            {
                // --- Trim leading TAB ---
                if (outRawCookies.length() > 0)
                    outRawCookies = outRawCookies.substring(1);

                jni.setCookieJar(controller, outRawCookies);
            }
        }

        public void deleteAllCookies() {
            //controller.evalJS("document.cookie = null");
            jni.deleteCookie(controller, null);
        }

        // --- Return all cookies for current document ---
        public Set<Cookie> getCookies() {
            Set<Cookie> retCookies = new HashSet<Cookie>();
            String rawCookies = jni.getCookieJar(controller);
            String path = "/";

            try {
                path = getPath();
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }

            while (true)
            {
                final int cookieFieldsNum = 7;
                String[] field = rawCookies.split("\t", cookieFieldsNum + 1);

                if (field.length < cookieFieldsNum)
                    break;

                if (path.startsWith(field[2]))
                    retCookies.add(new Cookie(field[5], field[6], field[0], field[2],
                            new Date(Long.parseLong(field[4].trim()) * 1000)));

                if (field.length < cookieFieldsNum + 1)
                    break;

                rawCookies = field[cookieFieldsNum];
            }

            return retCookies;
        }

        private String getHostName() throws java.net.MalformedURLException {
                URL url = new URL(getCurrentUrl());
                return url.getHost();
        }

        private String getPath() throws java.net.MalformedURLException {
                URL url = new URL(getCurrentUrl());
                return url.getPath();
        }

        public Timeouts timeouts() {
            return new WebKitTimeouts();
        }

      private String getDomainForCookie() {
            String domain = "";
            try {
                // domain = getHostName().replaceFirst("^[^.]*", "");
                domain = getHostName();
            } catch (Exception e) {
                throw new WebDriverException("Invalid cookie domain");
            }
            return domain;
      }

      public Window window() {
        throw new UnsupportedOperationException("Window interface is not supported yet.");
      }
  }

  public WebElement findElementByPartialLinkText(String using) {
    return rootNode().findElementByPartialLinkText(using);
  }

  public List<WebElement> findElementsByPartialLinkText(String using) {
    return rootNode().findElementsByPartialLinkText(using);
  }

  public Location location() {
    Location location = (Location)jni.getPosition(controller);
    if (location == null) throw new WebDriverException("Unable to get location");
    return location;
  }

  public void setLocation(Location location) {
    jni.setPosition(controller, location);
  }

  private void assertInitialized()
  {
     if (controller == 0)
        throw new WebDriverException();
  }

  private class WebKitAlert implements Alert
  {
      public void dismiss() {
        jni.getAlertText(controller, true);
        currentAlert = null;
      }

      public void accept() {
      }

      public String getText() {
        return jni.getAlertText(controller, false);
      }

      public void sendKeys(String keys) {
        throw new UnsupportedOperationException("Send keys is not yet support on alerts.");
      }
  }

  class WebKitTimeouts implements Timeouts {
      public Timeouts implicitlyWait(long time, TimeUnit unit) {
        WebKitDriver.this.implicitWait =
            TimeUnit.MILLISECONDS.convert(Math.max(0, time), unit);
        return this;
      }

      public Timeouts setScriptTimeout(long time, java.util.concurrent.TimeUnit unit) {
        throw new UnsupportedOperationException("Setting script timeout is not supported.");
      }
  }

  public class Storage implements SessionStorage, LocalStorage {
    private boolean isSession;

    public Storage(boolean isSession) {
      this.isSession = isSession;
    }

    public void clear() {
      jni.storageClear(controller, isSession);
    }

    public boolean containsKey(Object key)
    {
      return (null != jni.storageGetValue(controller, isSession, key.toString()));
    }

    public boolean containsValue(Object value)
    {
      return true;
    }

    public Set entrySet()
    {
      throw new WebDriverException("Can not convert Storage to Set");
    }

    public boolean equals(Object o)
    {
      return hashCode() == o.hashCode();
    }

    public String getItem(String key)
    {
      return (String)jni.storageGetValue(controller, isSession, key);
    }

    public int hashCode()
    {
      return (int)controller + (isSession ? 1 : 0);
    }

    public boolean isEmpty()
    {
      return (size() == 0);
    }

    public Set<String> keySet() {

      int storageLength = size();
      Set<String> storageKeySet = new HashSet<String>(storageLength);

      for (int i = 0; i < storageLength; i++) {
        storageKeySet.add(jni.storageKey(controller, isSession, i));
      }

      return Collections.unmodifiableSet(storageKeySet);
    }

    public void setItem(String key, String value) {
      jni.storageSetValue(controller, isSession, key, value);
    }

    public void putAll(Map t)
    {
      throw new WebDriverException("Can not copy Storage to another map");
    }

    public String removeItem(String key) {
      return (String)jni.storageSetValue(controller, isSession, key, null);
    }

    public int size() {
      long len = jni.storageLength(controller, isSession);
      if (len < 0)
        throw new WebDriverException("Can not access storage");
      return (int)len;
    }

    public Collection values()
    {
      throw new WebDriverException("Can not convert Storage to Collection");
    }
  }

  public SessionStorage getSessionStorage()
  {
    return new Storage(true);
  }

  public LocalStorage getLocalStorage()
  {
    return new Storage(false);
  }

  private static void sleepQuietly(long ms) {
      try {
        Thread.sleep(ms);
      } catch (InterruptedException ignored) {
      }
  }

  public <X> X getScreenshotAs(OutputType<X> target) {
      String dump = jni.getDOMDump(controller);
      String base64str = new Base64Encoder().encode(dump.getBytes());
      return target.convertFromBase64Png(base64str);
  }

  /* (non-Javadoc)
   * @see org.openqa.selenium.JavascriptExecutor#executeAsyncScript(java.lang.String, java.lang.Object[])
   */
  @Override
  public Object executeAsyncScript(String script, Object... args) {
    throw new UnsupportedOperationException("Async script execution is not supported by "
        + "WebKitDriver.");
  }

}
