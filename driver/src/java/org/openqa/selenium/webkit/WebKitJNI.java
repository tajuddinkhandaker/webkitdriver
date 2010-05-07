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

public class WebKitJNI {

  private static final WebKitJNI INSTANCE = new WebKitJNI();

  /**
   * Delete cookie with name for current document.
   * Delete all cookies for current document if name is empty.
   * Delete all cookies for all documents if ref is null.
   *
   * @param ref - reference to WebDriver instance
   * @return
   */
  public native long deleteCookie(long ref, String cName);

  /**
   * Set all cookies in internal format for current document.
   *
   * @param cookies - cookie string in internal format
   * @param ref - reference to WebDriver instance
   * @return
   */
  public native long setCookieJar(long ref, String cookies);

  /**
   * Get all cookies in internal format for current document.
   * Get all cookies in internal format for all documents if ref is null.
   *
   * @param ref - reference to WebDriver instance
   * @return - all cookies in internal format
   */
  public native String getCookieJar(long ref);

  /**
   * Set cookies for current document.
   *
   * @param cookies - string with all appended cookies
   * @param ref     - reference to WebDriver instance
   * @return
   */
  public native long setCookie(long ref, String cookies);

  /**
   * Get cookies of current document.
   *
   * @param ref - reference to WebDriver instance
   * @return    - string with all appended cookies
   */
  public native String cookies(long ref);

  /**
   * Go to previous element in browse history.
   *
   * @param ref - reference to WebDriver instance
   * @return
   */
  public native long goBack(long ref);

  /**
   * Go to next element in browse history.
   *
   * @param ref - reference to WebDriver instance
   * @return
   */
  public native long goForward(long ref);

  /**
   * Reload current document.
   *
   * @param ref - reference to WebDriver instance
   * @return
   */
  public native long refresh(long ref);

  /**
   * for getting ref to Document
   *
   * @param inObj - controller reference
   * @return ref on Document instance
   */
  public native long getDocument(long ref);

  /**
   * Document.cpp
   *
   * @param ref - reference to document
   * @param query - id
   * @return reference to Element instance
   */
  public native long getElementById(long ref, String query);

  /**
   * Node.cpp
   *
   * @param ref - reference to Node
   * @param query - tagName
   * @return reference to NodeList instance
   */
  public native long getElementsByTagName(long ref, String query);

  /**
   * Node.cpp
   *
   * @param ref - reference to Node
   * @param query - tagName
   * @return reference to NodeList instance
   */
  public native long getElementsByName(long ref, String query);

  /**
   * Node.cpp
   *
   * @param ref - reference to Node
   * @param query - tagName
   * @return reference to NodeList instance
   */
  public native long getElementsByXpath(long ref, String query);

  /**
   * NodeList.cpp
   *
   * @param ref - reference to NodeList
   * @return size of NodeList
   */
  public native long nodeListLength(long ref);

  /**
   * NodeList.cpp
   *
   * @param ref - reference to NodeList
   * @return size of NodeList
   */
  public native long nodeListGet(long ref, int i);

  /**
   * Release NodeList after it is not needed anymore
   *
   * @param ref - reference to NodeList
   * @return size of NodeList
   */
  public native long nodeListRelease(long ref);

  /**
   * Element.cpp
   *
   * @param ref - reference to Element instance
   * @return
   */
  public native String getTagName(long ref);

  /**
   * Element.cpp
   *
   * @param ref - reference to Element instance
   * @return
   */
  public native String getAttribute(long ref, String name);

  /**
   * Element.cpp
   *
   * @param ref - reference to Element instance
   * @param name - property name
   * @return property value
   */
  public native String getProperty(long ref, String name);

  /**
   * Element.cpp
   *
   * @param ref - reference to Element instance
   * @return
   */
  public native String getText(long ref);

  /**
   * InputElement.cpp
   *
   * @param ref - reference
   * @return
   */
  public native String getValue(long ref);

  /**
   * Send keys
   *
   * @param ref - reference
   * @return
   */
  public native long sendKeys(long ref, String val);

  /**
   * InputElement.cpp
   *
   * @param ref - reference
   * @return
   */
  public native long setValue(long ref, String val);

  /**
   * Get current frame title
   *
   * @param ref - reference to WebKitDriver
   * @return frame title
   */
  public native String getTitle(long ref);

  /**
   * Get page source
   *
   * @param ref - reference to WebKitDriver
   * @return page source as HTML
   */
  public native String getPageSource(long ref);

  /**
   * Get current frame URL
   *
   * @param ref - reference to WebKitDriver
   * @return frame URL
   */
  public native String getUrl(long ref);

  /**
   * Create instance of WebKitDriver
   *
   * @param userAgent - user agent string to use
   * @return ref on Document instance
   */
  public native long create(String userAgent);

  /**
   * Destroys instance of WebKitDriver
   *
   * @param ref - reference to WebKitDriver
   * @return 1 - destroyed correctly, 0 - empty ref passed
   */
  public native long destroy(long ref);

  /**
   * Load URL
   *
   * @param ref - reference to WebKitDriver
   * @param query - URL to load
   * @return ref on Document instance
   */
  public native long get(long ref, String query);

  /**
   * Click on input element
   *
   * @param ref - reference to DOM element
   * @return success or not
   */
  public native long click(long ref);

  /**
   * Reset input element to default value
   *
   * @param ref - reference to DOM element
   * @return success or not
   */
  public native long reset(long ref);

  /**
   * Submit a form
   *
   * @param ref - reference to DOM element
   * @return success or not
   */
  public native long submit(long ref);

  /**
   * Toggle checkbox of selection option
   *
   * @param ref - reference to DOM element
   * @return current state, -1 in case of error
   */
  public native long toggle(long ref);

  /**
   * Check if element is selected
   *
   * @param ref - reference to DOM element
   * @return 1 - selected, 0 - not selected, -1 - error
   */
  public native long selected(long ref);

  /**
   * Make element selected
   *
   * @param ref - reference to DOM element
   * @return 0 - OK, -1 in case of error
   */
  public native long setSelected(long ref);

  /**
   * Get option element index
   *
   * @param ref - reference to DOM element
   * @return index starting with 0, -1 in case of error
   */
  public native long optionIndex(long ref);

  /**
   * Get active element
   *
   * @param ref - reference to WebKitDriver object
   * @return reference to active element
   */
  public native long activeElement(long ref);

  /**
   * Select frame by name
   *
   * @param ref - reference to WebKitDriver object
   * @param name - frame name
   * @return 1 - success, 0 - failure
   */
  public native long selectFrameByName(long ref, String name);

  /**
   * Select frame by idx
   *
   * @param ref - reference to WebKitDriver object
   * @param name - frame idx
   * @return 1 - success, 0 - failure
   */
  public native long selectFrameByIdx(long ref, long idx);

  /**
   * Select window by name
   *
   * @param ref - reference to WebKitDriver object
   * @param name - window name
   * @return refernece to page controller object, 0 if not found
   */
  public native long selectWindow(long ref, String name);

  /**
   * Get current window handle
   *
   * @param ref - reference to WebKitDriver object
   * @return current window handle
   */
  public native String getWindowHandle(long ref);

  /**
   * Get all window handles
   *
   * @return string of comma-separated windows handles
   */
  public native String getAllWindowHandles();

  /**
   * Select main frame
   *
   * @param ref - reference to WebKitDriver object
   * @return 1 - success, 0 - failure
   */
  public native long defaultContent(long ref);

  /**
   * Move focus on the element
   *
   * @param ref - reference to DOM element to focus
   * @return 0 if element can not be focused, 1 otherwise
   */
  public native long focus(long ref);

  /**
   * Drag element
   *
   * @param ref - reference to DOM element to drag
   * @param toX, toY - end cordinates
   * @param duration - operation duration in ms
   * @return
   */
  public native long drag(long ref, int toX, int toY, int duration);

  public static WebKitJNI getInstance() {
    return INSTANCE;
  }

  /**
   * Evaluating Java Script
   *
   * @param ref - Reference to WebDriver
   * @param script - Java Script to evaluate
   * @return reference on JS Value
   */
  public native Object evaluateJS (long ref, Object[] arguments);

  /**
   * Check if element is stale
   *
   * @param ref - reference to DOM element
   * @return 1 - stale, 0 - not stale, -1 error
   */
  public native long stale(long ref);

  /**
   * Check if element is visible
   *
   * @param ref - reference to DOM element
   * @return boolean
   */
  public native boolean isVisible(long ref);

  /**
   * Get's actual element size (from renderer)
   *
   * @param ref - reference to DOM element
   * @return Rectangle
   */
  public native Object getRect(long ref);

  /**
   * Get text of current alert message
   *
   * @param ref - reference to WebKitDriver object
   * @param clr - clear alert status
   * @return Alert text or null
   */
  public native String getAlertText(long ref, boolean clr);
  
  /**
   * Get Geolocation
   * 
   * @param ref - reference to WebKitDriverObject
   * @return return object GeoLocation
   */
  public native Object getPosition(long ref);

  /**
   * Helper function set new Geolocation in Client Controller
   * 
   * @param ref - reference to WebKitDriverObject
   * @param location - new Geolocation
   * @return return object GeoLocation
   */
  public native void setPosition(long ref, Object location);

  /**
   * Check if network state is online
   *
   * @return 1 - selected, 0 - not selected, -1 - error
   */
  public native long online();

  /**
   * Set current network state
   *
   * @param online - true if new state is online, false otherwise
   * @return 0 - OK, -1 in case of error
   */
  public native long setOnline(boolean online);

  /**
   * Check is media/codec supported for HTMLMediaElement 
   *
   * @param ref - reference to HTMLMediaElement
   * @param contentType - string with content media type and codec info
   * @return true - content type may be played
   */
  public native boolean canPlayType(long ref, String contentType);

  /**
   * Do play/pause for HTMLMediaElement
   *
   * @param ref - reference to HTMLMediaElement
   * @param doPlay - perform pause() for false and play() for true
   * @return true - content type may be played
   */
  public native void mediaPlay(long ref, boolean doPlay);

  /**
   * Get application cache entries
   *
   * @param ref - reference to controller
   * @return list of cache elements
   */
  public native Object getAppCache(long ref);

  /**
   * Get number of entries in DOM storage
   *
   * @param ref - reference to controller
   * @param sesson - true for session storage, false for local storage
   * @return numner of items in a session or local storage, -1 in case of error
   */
  public native long storageLength(long ref, boolean session);

  /**
   * Clear DOM storage
   *
   * @param ref - reference to controller
   * @param sesson - true for session storage, false for local storage
   * @return true on success, false otherwise
   */
  public native boolean storageClear(long ref, boolean session);

  /**
   * Get DOM storage key by index
   *
   * @param ref - reference to controller
   * @param sesson - true for session storage, false for local storage
   * @param idx - key index
   * @return key name
   */
  public native String storageKey(long ref, boolean session, long idx);

  /**
   * Get DOM storage value by key
   *
   * @param ref - reference to controller
   * @param sesson - true for session storage, false for local storage
   * @param key - key name
   * @return value for a given key
   */
  public native String storageGetValue(long ref, boolean session, String key);

  /**
   * Set DOM storage value
   *
   * @param ref - reference to controller
   * @param sesson - true for session storage, false for local storage
   * @param key - key to set
   * @param value - value to set. If null, key is removed from a storage
   * @return value for a given key
   */
  public native Object storageSetValue(long ref, boolean session, String key, String value);

  static {
    System.loadLibrary("hlwk");
  }

}
