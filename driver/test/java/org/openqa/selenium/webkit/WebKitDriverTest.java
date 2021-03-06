/*
 * Copyright 2007-2010 WebDriver committers Copyright 2007-2010 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

package org.openqa.selenium.webkit;

import junit.framework.TestCase;

import org.openqa.selenium.By;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.WebDriverException;
import org.openqa.selenium.remote.DesiredCapabilities;

import java.util.concurrent.CountDownLatch;


/**
 * Unit tests for the {@link WebKitDriver} class.
 *
 */
public class WebKitDriverTest extends TestCase {

  WebKitDriver driver1;
  final String webPath = System.getProperty("user.dir").replaceFirst("[^/]+$", "driver/src/web/");

  public void setUp() {
    driver1 = new WebKitDriver();
  }

  @Override
  public void runTest() throws java.lang.Throwable {
    System.out.println(getName());
    super.runTest();
  }

  public void tearDown() {
    driver1.quit();
  }

  public void testConstructWebKitDriverWithDefaultUserAgent() {
    WebKitDriver driver = new WebKitDriver();
    assertTrue(getDriverUserAgent(driver).contains("AppleWebKit/418.9.1 (KHTML, like Gecko)"));
  }

  public void testConstructsWithDefaultUAWhenCapabilitiesAreNull() {
    WebKitDriver driver = new WebKitDriver(null);
    assertTrue(getDriverUserAgent(driver).contains("AppleWebKit/418.9.1 (KHTML, like Gecko)"));
  }

  public void testConstructsWebKitDriverWithUserAgent() {
    DesiredCapabilities capabilities = new DesiredCapabilities();
    capabilities.setCapability("user-agent", "A-USER-AGENT");
    WebKitDriver driver = new WebKitDriver(capabilities);

    assertEquals(getDriverUserAgent(driver), "A-USER-AGENT");
  }

  public void testAllowsAccessFromAChildThread() throws InterruptedException {
    final CountDownLatch latch = new CountDownLatch(1);
    Thread myThread = new Thread(new Runnable() {
      @Override
      public void run() {
        try {
          driver1.get("http://www.google.com");
          WebElement element = driver1.findElement(By.name("q"));
          assertEquals("input", element.getTagName());
        } finally {
          latch.countDown();
        }
      }
    });
    myThread.start();
    latch.await();
  }

  public void testCanSubmitGoogleForm() {
  
    DesiredCapabilities capabilities = new DesiredCapabilities();
    capabilities.setCapability("user-agent", "Mozilla/5.0 (iPhone; U; CPU iPhone OS 4_0 like Mac OS X; en-us) AppleWebKit/532.9 (KHTML, like Gecko) Version/4.0.5 Mobile/8A293 Safari/6531.22.7");
    WebKitDriver driver = new WebKitDriver(capabilities);
    driver.get("http://www.google.com");
    WebElement searchBox = driver.findElement(By.name("q"));
    searchBox.sendKeys("Kittens");
    searchBox.submit();

    String title = driver.getTitle();
    System.out.println(driver.getCurrentUrl());
    assertTrue("Title does not contain Kittens: \"" + title + "\"", title.contains("Kittens"));

  }

  public void testQuitsWebDriverProperly() {
    // Call quit on the driver.
    driver1.quit();
    try {
      driver1.get("http://www.google.com");
      fail("Should have thrown an exception here, since the driver was quit.");
    } catch (WebDriverException exc) {
     // Do nothing, this is expected.
    }
    
    // Re-instantiating the object however should work fine.
    driver1 = new WebKitDriver();
    driver1.get("http://www.google.com");
    assertTrue(driver1.getTitle().contains("Google"));
  }

  
  public void testQuitsWhenCloseCalledOnLastWindow() throws InterruptedException {
    // Call quit on the driver.
    driver1.close();
    try {
      driver1.get("http://www.google.com");
      fail("Should have thrown an exception here, since the driver was closed.");
    } catch (WebDriverException exc) {
      // Do nothing, this is expected.
    }
  }

  public void testCanvasPath() {
    WebKitDriver wd = new WebKitDriver();
    wd.get("file://" + webPath + "canvas2d.html");
    wd.quit();
  }

  private final static String getDriverUserAgent(WebKitDriver driver) {
    driver.get("about:blank");
    return (String) (driver.executeScript("return navigator.userAgent;"));
  }
}
