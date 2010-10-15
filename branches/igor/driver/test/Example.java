/*
Copyright 2007-2009 WebDriver committers
Copyright 2007-2009 Google Inc.
Portions copyright 2007 ThoughtWorks, Inc

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/*
 * Copyright 2007 ThoughtWorks, Inc
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
import java.util.Date;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.HashSet;
import java.lang.Thread;

import org.openqa.selenium.By;
import org.openqa.selenium.Cookie;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.RenderedWebElement;
import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.webkit.WebKitDriver;
import org.openqa.selenium.webkit.WebKitWebElement;

import static java.util.concurrent.TimeUnit.MILLISECONDS;

public class Example  {
    public static void main(String[] args) {
        Example ex = new Example();
//      ex.test0();
//      ex.testJS();
//      ex.testCookie();
//        ex.testGmail();
//        ex.testVisibility();
        ex.Google(null);
    }

    private void test0() {
        String log;
        WebDriver d1 = new WebKitDriver();
        d1.get("http://www.google.com.by");
        System.out.println("Title: " + d1.getTitle());
        System.out.println("URL: " + d1.getCurrentUrl());
/*        WebElement el = d1.findElement(By.id("ghead"));
        System.out.println("Found element with tag " + el.getTagName() +
                " and text " + el.getText());
        List<WebElement> lst = d1.findElements(By.tagName("div"));
        for (WebElement e : lst) {
                System.out.println("\tFound tag " + e.getTagName() +
                        " and text " + e.getText());
        }
        WebElement q = d1.findElement(By.name("q"));
        if (((WebKitWebElement)q).isDisplayed()) log = "displayed";
        else log = "not displayed";
        System.out.println("Element is "+log);
        q.sendKeys("Cheese!\n");
        d1.findElement(By.name("q")).click();
        System.out.println("Title: " + d1.getTitle());
        System.out.println("URL: " + d1.getCurrentUrl());
        d1.findElement(By.name("q")).submit();
        System.out.println("Title: " + d1.getTitle());
        System.out.println("URL: " + d1.getCurrentUrl());
*/      WebElement  q = d1.findElement(By.xpath("/html/head/title"));
        if (q == null) System.out.println ("No such element");
        System.out.println("Title (via XPATH) " + q.getText());
        if (((WebKitWebElement)q).isDisplayed()) log = "displayed";
        else log = "not displayed";
        System.out.println("Element is "+log);
    }

    private void testVisibility() {
        String log;
        WebDriver d1 = new WebKitDriver();
        d1.get("file:///home/igor/work/google/webdriver-mobile-public/common/src/web/javascriptPage.html");
        System.out.println("Title: " + d1.getTitle());
        System.out.println("URL: " + d1.getCurrentUrl());
        WebElement q = d1.findElement(By.id("hiddenlink"));
        if (((WebKitWebElement)q).isDisplayed()) System.out.println("Wrong - visible!"); else System.out.println("Correct - invisible");
        q = d1.findElement(By.id("style1"));
        if (!((WebKitWebElement)q).isDisplayed()) System.out.println("Wrong - invisible!"); else System.out.println ("Correct - visible");
        q = d1.findElement(By.id("zerowidth"));
        if (((WebKitWebElement)q).isDisplayed()) System.out.println("Wrong - visible!"); else System.out.println ("Correct - invisible");
        if (((WebKitWebElement)q).isDisplayed()) System.out.println("Wrong - visible!"); else System.out.println ("Correct - invisible");
        q = d1.findElement(By.id("child"));
        if (!((WebKitWebElement)q).isDisplayed()) System.out.println("Wrong - invisible!"); else System.out.println ("Correct - visible");
        d1.get("file:///home/igor/work/google/webdriver-mobile-public/common/src/web/formPage.html");
        q = d1.findElement(By.name("selectomatic"));
        if (((WebKitWebElement)q).isDisplayed()) log = "displayed";
        else log = "not displayed";
        System.out.println("Element is "+log);
        List<WebElement> options = q.findElements(By.tagName("option"));
        WebElement option = options.get(0);
        if (!((WebKitWebElement)option).isDisplayed()) System.out.println("Not visible!");
        option.isSelected();
//        option.toggle();
    
        d1.get("file:///home/igor/work/google/webdriver-mobile-public/common/src/web/xhtmlTest.html");
        System.out.println("URL: " + d1.getCurrentUrl());
        ((RenderedWebElement)d1.findElement(By.id("linkId"))).isDisplayed();
        d1.get("file:///home/igor/work/google/webdriver-mobile-public/common/src/web/rectangles.html");
        System.out.println("URL: " + d1.getCurrentUrl());
        ((RenderedWebElement)d1.findElement(By.id("r2"))).isDisplayed();
    }

    private void testJS() {
        WebDriver d1 = new WebKitDriver();
        d1.get("http://google.co.uk");
        System.out.println("Init finished"+d1.getCurrentUrl());
        String JS = "return 'correct '+'string';";
        Object scriptValue = ((JavascriptExecutor)d1).executeScript(JS);
        if (scriptValue instanceof String)
            System.out.println("This string is a "+(String)scriptValue);
        else System.out.println ("Error: String expected");
        JS = "var loc='http://www.tut.by'; window.location=loc;";
        ((JavascriptExecutor)d1).executeScript(JS);
        System.out.println("New title is "+d1.getTitle()+" URL is "+d1.getCurrentUrl());
/*        JS = "return document.title;";
        scriptValue = ((JavascriptExecutor)d1).executeScript(JS);
        if (scriptValue instanceof String)
            System.out.println("This string is a "+(String)scriptValue);
        else System.out.println ("Error: String expected");
        JS = "return arguments[0];";
        String helloArg = "Hello";
        scriptValue = ((JavascriptExecutor)d1).executeScript(JS, helloArg);
        if (scriptValue instanceof String) 
            System.out.println("This string is a "+(String)scriptValue);
        else System.out.println ("Error: String expected");
        JS = "return 3==4";
        scriptValue = ((JavascriptExecutor)d1).executeScript(JS);
        if (scriptValue instanceof Boolean)
            System.out.println(JS+" is "+(Boolean)scriptValue);
        else System.out.println("Error: Boolean was expected");
        JS = "return 2+2";
        scriptValue = ((JavascriptExecutor)d1).executeScript(JS);
        if (scriptValue instanceof Long)
            System.out.println(JS+"="+(Long)scriptValue);
        else System.out.println("Error: Long was expected");
        JS = "return document.title;";
        scriptValue = ((JavascriptExecutor)d1).executeScript(JS);
        if (scriptValue instanceof String)
            System.out.println("Document title is "+(String)scriptValue);
        else System.out.println ("Error: String expected");
        JS = "return ['zero', 'one', 'two'];";
        scriptValue = ((JavascriptExecutor)d1).executeScript(JS);
        if (scriptValue instanceof List)
            System.out.println("Array with "+((List<Object>)scriptValue).size()+ " elements");
        else System.out.println ("Error: Array expected");
        JS = "return {abc: '123', tired: 'false'};";
        scriptValue = ((JavascriptExecutor)d1).executeScript(JS);
        if (scriptValue instanceof Map)
            System.out.println("Map with "+((Map)scriptValue).size()+ " elements");
        else System.out.println ("Error: Map expected");
        JS = "return {foo: 'bar', baz: ['a','b','c'],"+
            "person: {first: 'John', last: 'Doe'}};";
        scriptValue = ((JavascriptExecutor)d1).executeScript(JS);
        if (scriptValue instanceof Map)
            System.out.println("Map with "+((Map)scriptValue).size()+ " elements");
        else System.out.println ("Error: Map expected");
        JS = "return arguments[0] == true;";
        Boolean arg = true;
        scriptValue = ((JavascriptExecutor)d1).executeScript(JS, arg);
        if (scriptValue instanceof Boolean)
            System.out.println("It is "+(Boolean)scriptValue);
        else System.out.println ("Error: Boolean expected");
        Object[] arrayArg = {"1", "3.14", "set", "Bogey"};
        JS = "return arguments[0].length;";
        scriptValue = ((JavascriptExecutor)d1).executeScript(JS, arrayArg);
        if (scriptValue instanceof Long)
            System.out.println("Array length is "+(Long)scriptValue);
        else System.out.println ("Error: Long expected");
        HashSet<Object> setArg = new HashSet<Object>();
        setArg.add("Cheddar");
        setArg.add("Brie");
        setArg.add("7");
        JS = "return arguments[0].length;";
        scriptValue = ((JavascriptExecutor)d1).executeScript(JS, setArg);
        if (scriptValue instanceof Long) 
            System.out.println("Set length is "+(Long)scriptValue);
        else System.out.println ("Error: Long expected");
        try {
            JS = "return squiggle();";
            scriptValue = ((JavascriptExecutor)d1).executeScript(JS);
            System.out.println("Error exception expected");
        }
        catch(Exception e) {
            System.out.println("Correct, exception");
        }
        JS = "return document.getElementById('ghead');";
        scriptValue = ((JavascriptExecutor)d1).executeScript(JS);
        if (scriptValue == null) System.out.println ("NULL!!!!");
        if (scriptValue instanceof WebElement) 
            System.out.println("Works fine");
        else System.out.println ("Error: Object expected");
        WebKitWebElement webEl = (WebKitWebElement)scriptValue;
        JS = "return arguments[0].tagName";
        scriptValue = ((JavascriptExecutor)d1).executeScript(JS, webEl);
        if (scriptValue instanceof String) 
            System.out.println("This string is a "+(String)scriptValue);
        else System.out.println ("Error: String expected");

      JS = "return document.getElementsByTagName('div');";
        scriptValue = ((JavascriptExecutor)d1).executeScript(JS);
        if (scriptValue == null) System.out.println ("NULL!!!!");
        if (scriptValue instanceof List) 
            System.out.println("Works fine");
        else System.out.println ("Error: Object expected");*/

    }

    private void printCookie(Cookie c){
        System.out.println("\nName   = " + c.getName());
        System.out.println("Value  = " + c.getValue());
        System.out.println("Domain = " + c.getDomain());
        System.out.println("Path   = " + c.getPath());
        System.out.println("Expiry = " + c.getExpiry() + "\n");
    }

    private void printAllCookies(WebDriver wd){
        Set<Cookie> cookies = wd.manage().getCookies();

        for (Cookie c: cookies)
            printCookie(c);
    }

    private void testCookie() {
        WebDriver d1 = new WebKitDriver();
        d1.get("http://www.google.com.by:80");
//        d1.get("http://www.yahoo.com");
        System.out.println("Init finished");
/*
        d1.manage().addCookie(new Cookie("Name", "Value", ".google.com", "/", new Date()));
        printAllCookies(d1);
        System.out.println("Delete all cookies");
        d1.manage().deleteAllCookies();
        printAllCookies(d1);
*/
/*
        String JS = "return document.cookie";
        Object scriptValue = ((JavascriptExecutor)d1).executeScript(JS);
        if (scriptValue instanceof String)
            System.out.println("This string is a " + (String)scriptValue);
        else System.out.println ("Error: String expected");

        ((JavascriptExecutor)d1).executeScript("document.cookie='abc=123'");
        printAllCookies(d1);

        scriptValue = ((JavascriptExecutor)d1).executeScript(JS);
        if (scriptValue instanceof String)
            System.out.println("This string is a " + (String)scriptValue);
        else System.out.println ("Error: String expected");

        d1.manage().addCookie(new Cookie("Name", "Value", ".google.com", "/", new Date()));
        printAllCookies(d1);
*/

        printAllCookies(d1);

        Cookie c = d1.manage().getCookieNamed("PREF");
        System.out.println("=== PREF cookie");
        printCookie(c);
        d1.manage().deleteCookie(c);
        System.out.println("=== PREF cookie is deleted");
        printAllCookies(d1);

        d1.manage().deleteCookieNamed("PREF");
        System.out.println("=== Delete all PREF cookies");
        printAllCookies(d1);

        d1.manage().deleteAllCookies();
        System.out.println("=== Delete all cookies");
        printAllCookies(d1);

        c = new Cookie("Name", "Value", ".google.com.by", "/", new Date());
        System.out.println("=== New cookie");
        printCookie(c);

        d1.manage().addCookie(c);
        System.out.println("=== Add new cookie");
        printAllCookies(d1);

        d1.get("http://www.google.com.by");
        System.out.println("===== Reload page");
        printAllCookies(d1);

        c = new Cookie("Name1", "Value", ".google.com.by", "/", new Date("4 Apr 2031 21:54:27 GMT"));
        d1.manage().addCookie(c);
        System.out.println("=== Update new cookie");
        printAllCookies(d1);

        d1.get("http://www.google.com.by");
        System.out.println("===== Reload page");
        printAllCookies(d1);
/*
        Date d = new Date();
        System.out.println(d.toString());
        System.out.println(d.toGMTString());
*/
/*
        Cookie c = d1.manage().getCookieNamed("PREF");
        printCookie(c);

        printAllCookies(d1);

        System.out.println("=========");
        d1.manage().deleteCookieNamed("PREF");
        printAllCookies(d1);

        System.out.println("=========");
        d1.manage().addCookie(new Cookie("Name", "Value", ".google.com", "/", new Date()));
        c = d1.manage().getCookieNamed("Name");
        printCookie(c);

        d1.manage().deleteCookie(c);
        printAllCookies(d1);

        System.out.println("=========");
        d1.manage().addCookie(new Cookie("Name", "Value", ".google.com", "/", new Date()));
        printAllCookies(d1);
        d1.manage().deleteAllCookies();
        printAllCookies(d1);
*/
    }


    private void testGmail() {
        WebDriver d1 = new WebKitDriver();
         d1.get("http://mail.google.com/mail/s");
//        d1.get("http://mail.google.com/mail/?nocheckbrowser");

//        System.out.println(d1.getPageSource());

        WebElement passwd = d1.findElement(By.id("Passwd"));
        System.out.println("= 1 =");
        WebElement email = d1.findElement(By.id("Email"));
        System.out.println("= 2 =");
        WebElement login = d1.findElement(By.name("signIn"));

        System.out.println("= 3 =");
        email.sendKeys("@gmail.com");
        System.out.println("= 4 =");
        passwd.sendKeys("");

        System.out.println("= 5 =");
        login.submit();

        System.out.println(d1.getPageSource());

        System.out.println("= 6 =");
        // --- Sample from Baran ---
        /*
        WebElement loginFormDiv = d1.findElement(
            By.id("gaia_loginbox"));

        if (loginFormDiv == null) {
            System.out.println("Logged in!");
            return;
        }

        System.out.println("Logged Failed!!!");
        System.out.println(d1.getPageSource());
        */
        try {
            WebElement loginFormDiv = d1.findElement(
                By.id("gaia_loginbox"));
        } catch (Exception e) {
            System.out.println("Logged in!");
            return;
        }

        System.out.println("Logged Failed!!!");
        System.out.println(d1.getPageSource());
    }

    private void Google(String userAgent) {
      long timeInMillis = System.currentTimeMillis();
      System.out.println("=> 0");
      WebKitDriver driver = new WebKitDriver(userAgent);
      // driver.manage().timeouts().implicitlyWait(1000, MILLISECONDS);
      System.out.println("=> 1");
      driver.get("http://google.com");
      System.out.println("=> 2");
      try { Thread.sleep(500); }
      catch (InterruptedException ignore) {}
      WebElement q = driver.findElement(By.name("q"));
      System.out.println("=> 3");
      q.sendKeys("London\n");
      System.out.println("=> 4");
      System.out.println("Found " + driver.findElements(By.tagName("a")).size());
      System.out.println("=> 5");
      for(WebElement e : driver.findElements(By.tagName("a"))) {
          System.out.println("=> 6");
          System.out.println("Link " + e.getText());
      }
      driver.quit();
      System.out.println("Test took " + (System.currentTimeMillis() - timeInMillis));
    }
}
