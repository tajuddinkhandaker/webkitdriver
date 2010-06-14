/*
 * Copyright 2007-2009 WebDriver committers
 * Copyright 2007-2009 Google Inc.
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

import org.openqa.selenium.Alert;
import org.openqa.selenium.By;
import org.openqa.selenium.Cookie;
import org.openqa.selenium.html5.ApplicationCache;
import org.openqa.selenium.html5.AppCacheEntry;
import org.openqa.selenium.html5.AppCacheType;
import org.openqa.selenium.html5.AppCacheStatus;
import org.openqa.selenium.html5.BrowserConnection;
import org.openqa.selenium.html5.DatabaseStorage;
import org.openqa.selenium.html5.Location;
import org.openqa.selenium.html5.LocationContext;
import org.openqa.selenium.html5.ResultSet;
import org.openqa.selenium.html5.LocalStorage;
import org.openqa.selenium.html5.SessionStorage;
import org.openqa.selenium.html5.WebStorage;
import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.NoAlertPresentException;
import org.openqa.selenium.NoSuchElementException;
import org.openqa.selenium.NoSuchFrameException;
import org.openqa.selenium.NoSuchWindowException;
import org.openqa.selenium.OutputType;
import org.openqa.selenium.StaleElementReferenceException;
import org.openqa.selenium.SearchContext;
import org.openqa.selenium.Speed;
import org.openqa.selenium.TakesScreenshot;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.WebDriverException;
import org.openqa.selenium.WebDriver.Timeouts;
import org.openqa.selenium.webkit.WebKitSerializer;
import org.openqa.selenium.html5.AppCacheEntry;
import org.openqa.selenium.html5.DatabaseStorage;
import org.openqa.selenium.html5.Location;
import org.openqa.selenium.html5.ResultSet;
import org.openqa.selenium.internal.Base64Encoder;
import org.openqa.selenium.internal.FindsById;
import org.openqa.selenium.internal.FindsByLinkText;
import org.openqa.selenium.internal.FindsByName;
import org.openqa.selenium.internal.FindsByTagName;
import org.openqa.selenium.internal.FindsByXPath;
import org.openqa.selenium.internal.ReturnedCookie;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import java.lang.reflect.*;
import java.lang.Thread;
import java.net.ConnectException;
import java.net.URL;
import java.net.MalformedURLException;
import java.net.UnknownHostException;
import java.net.Socket;
import java.net.ServerSocket;
import java.security.GeneralSecurityException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import java.nio.ByteBuffer;
import java.lang.Process;
import java.lang.ProcessBuilder;
import java.io.IOException;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.lang.IllegalThreadStateException;


public class WebKitDriver implements WebDriver, SearchContext, JavascriptExecutor,
        FindsById, FindsByLinkText, FindsByXPath, FindsByName, FindsByTagName,
        BrowserConnection, ApplicationCache, DatabaseStorage, LocationContext,
        WebStorage, TakesScreenshot {
  private long default_controller = 0;
  private long controller = 0;
  private WebKitInterface jni = (WebKitInterface)WebKitJNI.getInstance();
  private Speed speed = Speed.FAST;
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
    private BufferedReader err;
    private Socket dataSocket;
    private DataOutputStream dataOut;
    private DataInputStream dataIn;
    private boolean isRunning;
    private WebKitDriver parent;

    public Forwarder(WebKitDriver parent) {
        this.parent = parent;
        ProcessBuilder pb = new ProcessBuilder(System.getProperty("java.home") +"/bin/java", "-classpath", System.getProperty("java.class.path") ,
            "org.openqa.selenium.webkit.WebKitWrapper", Integer.toString(pipe.getServerPort()));
        try {
            wrapper = pb.start();
            dataSocket = pipe.connect();
            dataOut = new DataOutputStream(dataSocket.getOutputStream());
            dataIn  = new DataInputStream(dataSocket.getInputStream());
            in  = new BufferedReader(new InputStreamReader(wrapper.getInputStream()));
            err = new BufferedReader(new InputStreamReader(wrapper.getErrorStream()));
            isRunning = true;
        } catch (IOException e) {
            throw new WebDriverException("WebKitDriver wrapper can not be spawned");
        }
    }

    public Object invoke(Object proxy, Method method, Object[] args)
    {
        if (!isRunning) {
           throw new WebDriverException("Child process is not running");
        }
        try {
            // Serialize and send request to remove process
            WebKitSerializer.putMethodIntoStream(dataOut, method, args);
            dataOut.flush();

            // Child's stderr printing
            while (err.ready()) {
                System.err.println("Child's err: " + err.readLine());
            }

            // Child's stdout printing
            while (in.ready()) {
                System.out.println("Child's out: " + in.readLine());
            }

            // Receive response and deserialize it
            return WebKitSerializer.deserialize(dataIn, parent);
        } catch (Exception e) {
            try {
                wrapper.exitValue();
                isRunning = false;
            } catch(IllegalThreadStateException ie) {};
            throw new WebDriverException("Unexpected invocation exception on method " + method.getName() + ": " + e.getMessage());
        }
    }
  }

  public WebKitDriver() {
    this(null);
  }

  public WebKitDriver(String userAgent) {
    if (!WebKitJNI.isMainThread())
    {
        if (pipe == null)
            pipe = new Pipe();
        Forwarder handler = new Forwarder(this);
        jni = (WebKitInterface)Proxy.newProxyInstance(
                            WebKitInterface.class.getClassLoader(),
                            new Class[] { WebKitInterface.class },
                            handler);
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
      controller = default_controller = 0;
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
        long ref = Integer.parseInt(handle);
        jni.destroy(ref);
      }
      controller = 0;
      default_controller = 0;
      jni.deleteCookie(controller, null);
    }
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
    return (List<AppCacheEntry>)jni.getAppCache(controller);
  }

  public AppCacheStatus getStatus()
  {
    int status = jni.getAppCacheStatus(controller);
    if (status < 0) {
      throw new WebDriverException("Can not determine application cache status");
    }
    return AppCacheStatus.values()[status];
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

        public Speed getSpeed() {
            return WebKitDriver.this.speed;
        }
        public Timeouts timeouts() {
            return new WebKitTimeouts();
        }

        public void setSpeed(Speed speed) {
            WebKitDriver.this.speed = speed;
        }

      // private String getDomainForCookie(Cookie cookie) {
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
  }

  class WebKitTimeouts implements Timeouts {
      public Timeouts implicitlyWait(long time, TimeUnit unit) {
        WebKitDriver.this.implicitWait =
            TimeUnit.MILLISECONDS.convert(Math.max(0, time), unit);
        return this;
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
      throw new WebDriverException("Can not convert Storage to Set");
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

}
