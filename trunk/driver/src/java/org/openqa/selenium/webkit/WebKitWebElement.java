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

package org.openqa.selenium.webkit;

import java.io.IOException;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import org.openqa.selenium.By;
import org.openqa.selenium.NoSuchElementException;
import org.openqa.selenium.Platform;
import org.openqa.selenium.SearchContext;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.RenderedWebElement;
import org.openqa.selenium.WebDriverException;
import org.openqa.selenium.StaleElementReferenceException;
import org.openqa.selenium.ElementNotVisibleException;
import org.openqa.selenium.internal.FindsByCssSelector;
import org.openqa.selenium.internal.FindsById;
import org.openqa.selenium.internal.FindsByLinkText;
import org.openqa.selenium.internal.FindsByTagName;
import org.openqa.selenium.internal.FindsByXPath;
import org.openqa.selenium.internal.WrapsDriver;
import org.openqa.selenium.internal.WrapsElement;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Attr;
import org.w3c.dom.NodeList;
import org.w3c.dom.Element;

import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.awt.Point;
import java.awt.Dimension;
import java.awt.Rectangle;

import static org.openqa.selenium.Keys.ENTER;
import static org.openqa.selenium.Keys.RETURN;

public class WebKitWebElement implements WebElement, RenderedWebElement,
    FindsById, FindsByLinkText, FindsByXPath, FindsByTagName, FindsByCssSelector,
    SearchContext, WrapsDriver {

  protected long element;
  protected WebKitDriver parent;
  
  public WebKitWebElement() {
    parent = null;
    element = 0;
  }

  public WebKitWebElement(WebKitDriver parent, long ref)
  {
    this(parent, ref, true);
  }

  public WebKitWebElement(WebKitDriver parent, long ref, boolean checkStale)
  {
    if (ref == 0) {
      throw new WebDriverException("Invalid element");
    }
    element = ref;
    this.parent = parent;
    if (checkStale)
        assertElementNotStale();
  }

  public void click() {
    assertElementDisplayed();

    parent.jni().click(element);
  }

  public void submit() {
    assertElementNotStale();
    if(parent.jni().submit(element) == 0) {
      throw new WebDriverException("Cannot find form element");
    }
  }

  public void clear() {
    assertElementNotStale();
    long ret = parent.jni().setValue(element, "");
    if (ret == 0) {
      throw new WebDriverException("Error whem clearing element");
    }
  }

  public void sendKeys(CharSequence... value) {
    assertElementDisplayed();

    String str = "";
    for (int i=0;i<value.length;i++) {
        str += value[i];
    }
    if(parent.jni().sendKeys(element, str) == 0) {
      throw new WebDriverException("Error sending keys to element");
    }
  }

  public String getTagName() {
    assertElementNotStale();
    return parent.jni().getTagName(element).toLowerCase();
  }

    /**
     * @deprecated Use {@link #getTagName()} instead, this method will be removed in the near future.
     */
  public String getElementName() {
    assertElementNotStale();
    return getTagName();
  }

  public String getValue() {
    assertElementNotStale();
    String val =  parent.jni().getValue(element);
    return (val == null) ? "" : val;
  }

  public String getAttribute(String name) {
    assertElementNotStale();
    String val = parent.jni().getAttribute(element, name);
    String lowerName = name.toLowerCase();
    if ("disabled".equals(lowerName)) {
      return ((val == null )? "false" : "true");
    }
    if ("checked".equals(lowerName)) {
      if (val == null)
        return isSelected() ? "true" : "false";
      else
        return !val.equals("checked") ? "false" : "true";
    }
    if ("selected".equals(lowerName)) {
      if (val == null)
        return isSelected() ? "true" : "false";
      else
        return val.equals("selected") ? "true" : "false";
    }
    if (val == null && "index".equals(lowerName) && getTagName().toLowerCase().equals("option")) {
        long idx = parent.jni().optionIndex(element);
        if (idx >= 0)
          val = String.valueOf(idx);
    }
    return val;
  }

  public boolean toggle() {
    assertElementDisplayed();

    long retval = parent.jni().toggle(element);
    if (retval < 0) {
      throw new UnsupportedOperationException( "You may only toggle checkboxes or options in a select which allows multiple selections: " + getTagName());
    }
    return retval > 0;
  }

  public boolean isSelected() {
    assertElementNotStale();
    long retval = parent.jni().selected(element);
    if (retval == -1) {
      throw new UnsupportedOperationException("Unable to determine if element is selected.");
    }
    return retval > 0;
  }

  public void setSelected() {
    assertElementNotStale();

    if (!isEnabled()) {
      throw new UnsupportedOperationException("You may not select a disabled element: " + getAttribute("disabled"));
    }

    assertElementDisplayed();

    long retval = parent.jni().setSelected(element);
    if (retval == -1) {
       throw new UnsupportedOperationException("Unable to select element.");
    }
  }

  public boolean valid() {
    return element != 0;
  }

  public boolean isEnabled() {
    assertElementNotStale();
    String val = getAttribute("disabled");
    return val.equals("false");
  }

  public String getText() {
    assertElementNotStale();
    String str = parent.jni().getText(element).trim();
    // Replace &nbsp character with ordinary space
    str = str.replace( (char)160, ' ');
    str = str.replaceAll("\r", "");
    return str;
  }

  public WebElement findElement(By by) {
    return by.findElement(this);
  }

  public List<WebElement> findElements(By by) {
    return by.findElements(this);
  }

  public WebElement findElementById(String id) {
    assertElementNotStale();
    return findElementByXPath(".//*[@id =\"" + id + "\"]");
  }

  public List<WebElement> findElementsById(String id) {
    assertElementNotStale();
    return findElementsByXPath(".//*[@id =\"" + id + "\"]");
  }

  public WebElement findElementByXPath(String xpathExpr) {
    assertElementNotStale();
    return firstElement(findElementsByXPath(xpathExpr));
  }

  public List<WebElement> findElementsByXPath(String xpathExpr) {
    assertElementNotStale();
    return fromNodeList (parent.jni().getElementsByXpath(element, xpathExpr));
  }

  public WebElement findElementByCssSelector(String selector) {
    assertElementNotStale();
    long ref = parent.jni().getElementByCssSelector(element, selector);
    if (ref != 0) {
       return new WebKitWebElement(parent, ref);
    }
    else {
      throw new NoSuchElementException(String.format("Cannot find element by CSS selector"));
    }
  }

  public List<WebElement> findElementsByCssSelector(String selector) {
    assertElementNotStale();
    return fromNodeList (parent.jni().getElementsByCssSelector(element, selector));
  }

  public WebElement findElementByLinkText(String linkText) {
    assertElementNotStale();
    return firstElement(findElementsByLinkText(linkText));
  }

  public List<WebElement> findElementsByLinkText(String linkText) {
    assertElementNotStale();
    List<WebElement> webElements = new ArrayList<WebElement>();
    for (WebElement e : findElementsByTagName("a")) {
      if (e.getText().equals(linkText)) {
        webElements.add(e);
      }
    }
    return webElements;
  }

  public WebElement findElementByPartialLinkText(String linkText) {
    assertElementNotStale();
    return firstElement(findElementsByPartialLinkText(linkText));
  }

  public List<WebElement> findElementsByPartialLinkText(String linkText) {
    assertElementNotStale();
    List<WebElement> webElements = new ArrayList<WebElement>();
    for (WebElement e : findElementsByTagName("a")) {
      if (e.getText().contains(linkText)) {
        webElements.add(e);
      }
    }
    return webElements;
  }

  public WebElement findElementByTagName(String name) {
    assertElementNotStale();
    String tag = name;
    // TODO Workaround for svg, better to correctly process namespaces
    if (name.startsWith("svg:"))
      tag = name.substring(4);
    return firstElement(findElementsByTagName(tag));
  }

  public List<WebElement> findElementsByTagName(String name) {
    assertElementNotStale();
    String tag = name;
    // TODO Workaround for svg, better to correctly process namespaces
    if (name.startsWith("svg:"))
      tag = name.substring(4);
    return fromNodeList (parent.jni().getElementsByTagName(element, tag));
  }

  public WebElement findElementByName(String name) {
    assertElementNotStale();
    return firstElement(findElementsByName(name));
  }

  public List<WebElement> findElementsByName(String name) {
    assertElementNotStale();
    return fromNodeList (parent.jni().getElementsByName(element, name));
  }

  public static List<WebElement> createNodeList(WebKitDriver parent, long noderef) {
    if (noderef == 0) {
      throw new NoSuchElementException(String.format("Cannot find elements"));
    }

    List<WebElement> webElements = new ArrayList<WebElement>();
    long len = parent.jni().nodeListLength(noderef);
    for(int i = 0; i < len; i++) {
      long ref = parent.jni().nodeListGet(noderef, i);
      if (ref != 0) {
        webElements.add ( new WebKitWebElement(parent, ref) );
      }
      else {
        parent.jni().nodeListRelease(noderef);
        throw new NoSuchElementException(String.format("Invalid element returned in search result"));
      }
    }
    parent.jni().nodeListRelease(noderef);
    return webElements;
  }


  private List<WebElement> fromNodeList(long noderef)
  {
    if (noderef == 0) {
      throw new NoSuchElementException(String.format("Cannot find elements"));
    }

    List<WebElement> webElements = new ArrayList<WebElement>();
    long len = parent.jni().nodeListLength(noderef);
    for(int i = 0; i < len; i++) {
      long ref = parent.jni().nodeListGet(noderef, i);
      if (ref != 0) {
        webElements.add ( new WebKitWebElement(this.parent, ref) );
      }
      else {
        parent.jni().nodeListRelease(noderef);
        throw new NoSuchElementException(String.format("Invalid element returned in search result"));
      }
    }
    parent.jni().nodeListRelease(noderef);
    return webElements;
  }

  private WebElement firstElement(List<WebElement> lst)
  {
    if ( lst.isEmpty() ) {
      throw new NoSuchElementException(String.format("Cannot find element"));
    }
    return lst.get(0);
  }

  private boolean isTextArea()
  {
    return getTagName().equalsIgnoreCase("TEXTAREA");
  }

  private boolean isInput()
  {
    return getTagName().equalsIgnoreCase("INPUT");
  }

  public boolean isDisplayed() {
    assertElementNotStale();
    return parent.jni().isVisible(element);
  }

  public Point getLocation() {
    assertElementNotStale();

    Rectangle rect = (Rectangle)parent.jni().getRect(element);
    if (rect == null) {
      throw new WebDriverException("Cannot determine location of element");
    }
    return rect.getLocation();
  }

  public Dimension getSize() {
    assertElementNotStale();

    Rectangle rect = (Rectangle)parent.jni().getRect(element);
    if (rect == null) {
      throw new WebDriverException("Cannot determine size of element");
    }
    return rect.getSize();
  }

  public void dragAndDropBy(int moveRightBy, int moveDownBy) {
    assertElementDisplayed();

    int duration = parent.manage().getSpeed().getTimeOut();
    parent.jni().drag(element, moveRightBy, moveDownBy, duration);
  }

  public void dragAndDropOn(RenderedWebElement element) {
    assertElementDisplayed();

    if (!element.isDisplayed())
        return;

    Point from   = getLocation();
    Point to     = element.getLocation();
    int duration = parent.manage().getSpeed().getTimeOut();

    parent.jni().drag(this.element, to.x - from.x, to.y - from.y, duration);
  }

  public String getValueOfCssProperty(String propertyName) {
    assertElementNotStale();
    String val = parent.jni().getProperty(element, propertyName);

    if (val == null) {
      return "";
    }

    if (val.startsWith("rgb"))
      return rgbToHex(val);

    return val;
  }

  // Convert colours to hex if possible
  private String rgbToHex(final String value) {
    final Pattern pattern = Pattern.compile("rgb\\((\\d{1,3}),\\s(\\d{1,3}),\\s(\\d{1,3})\\)");
    final Matcher matcher = pattern.matcher(value);

    if (value.equals("rgba(0, 0, 0, 0)")) return "transparent";
    if (matcher.find()) {
      String hex = "#";
      for (int i = 1; i <= 3; i++) {
        int colour = Integer.parseInt(matcher.group(i));
        String s = Integer.toHexString(colour);
        if (s.length() == 1)
          s = "0" + s;
        hex += s;
      }
      hex = hex.toLowerCase();
      return hex;
    }
    return value;
  }

  public void hover() {
    throw new UnsupportedOperationException("Hover is not supported by the WebKit driver");
  }

  public WebDriver getWrappedDriver() {
    return parent;
  }

  public boolean equals(Object obj) {
    if (!(obj instanceof WebElement)) {
      return false;
    }

    WebElement other = (WebElement) obj;
    if (other instanceof WrapsElement) {
      other = ((WrapsElement) obj).getWrappedElement();
    }

    return other instanceof WebKitWebElement && element == (((WebKitWebElement) other).element);
  }

  public int hashCode() {
    return (int)element;
  }

  public long getReference() {
    return element;
  }

  public void assertElementNotStale() {
      long retval = parent.jni().stale(element);
  if (retval != 0) {
          throw new StaleElementReferenceException(
            "Element appears to be stale. Did you navigate away from the page that contained it? And is the current window focussed the same as the one holding this element?");
  }
  //TODO: add
  }

  protected void assertElementDisplayed()
  {
    if (!isDisplayed()) {
      throw new ElementNotVisibleException("You may only select visible elements");
    }
  }

  /**
   * Can a player play this audio or video, (support this codec or not)
   */
  public boolean canPlayType(String contentType) {
      return parent.jni().canPlayType(element, contentType);
  }

  /**
   * Controls
   */
  public void play() {
      parent.jni().mediaPlay(element, true);
  }

  public void pause() {
      parent.jni().mediaPlay(element, false);
  }

  long getElement() {
    return element;
  }
}
