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

import org.openqa.selenium.Capabilities;
import org.openqa.selenium.remote.DesiredCapabilities;

import java.util.HashMap;
import java.util.Map;


/**
 * Unit tests for the {@link WebKitDriver} class.
 *
 */
public class WebKitDriverTest extends TestCase {

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

  private final static String getDriverUserAgent(WebKitDriver driver) {
    driver.get("about:blank");
    return (String) (driver.executeScript("return navigator.userAgent;"));
  }
}
