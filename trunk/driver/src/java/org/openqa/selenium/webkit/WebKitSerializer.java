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

package org.openqa.selenium.webkit;

import java.awt.Rectangle;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.List;
import java.util.Collection;

import org.openqa.selenium.webkit.WebKitDriver;
import org.openqa.selenium.webkit.WebKitJNI;
import org.openqa.selenium.WebDriverException;
import org.openqa.selenium.html5.ResultSet;
import org.openqa.selenium.html5.ResultSetRows;
import org.openqa.selenium.html5.Location;
import org.openqa.selenium.html5.AppCacheEntry;
import org.openqa.selenium.html5.AppCacheType;

public class WebKitSerializer {
  private static final byte nullType              = 0;
  private static final byte longType              = 1;
  private static final byte intType               = 2;
  private static final byte doubleType            = 3;
  private static final byte stringType            = 4;
  private static final byte booleanType           = 5;
  private static final byte arrayType             = 6;
  private static final byte methodType            = 7;
  private static final byte mapType               = 8;
  private static final byte listType              = 9;
  private static final byte collectionType        = 10;
  private static final byte resultSetType         = 11;
  private static final byte resultSetRowsType     = 12;
  private static final byte locationType          = 13;
  private static final byte appCacheEntryType     = 14;
  private static final byte webKitDriverType      = 15;
  private static final byte webKitWebElementType  = 16;
  private static final byte webDriverExceptionType= 17;
  private static final byte rectangleType         = 18;
  private static final byte exceptionType         = 19;

  /**
   * Serialize method to stream for remote call
   *
   * @param method Method for serialization
   * @param args Array of arguments for the method
   * @return ByteBuffer with serialized method
   */
  public static ByteBuffer putMethodIntoStream(Method method, Object args[]) throws WebDriverException {
    ByteBuffer stream = ByteBuffer.allocate(30000);
    serialize(stream, method);
    for (int i = 0; i < method.getParameterTypes().length; i++) {
        serialize(stream, args[i]);
    }
    return stream;
  }

  /**
   * Invoke serialized method from a byte stream
   *
   * @param stream ByteBuffer with serialized method
   * @return Object as result of method invocation
   */
  public static Object invokeMethodFromStream(ByteBuffer stream) throws WebDriverException {
    Object method = deserialize(stream);
    if (!(method instanceof Method))
      throw new WebDriverException("Incorrect serialization format");

    ArrayList args = new ArrayList();
    for (int i = 0; i < ((Method)method).getParameterTypes().length; i++)
      args.add(deserialize(stream));
    try {
      Object result = ((Method)method).invoke(WebKitJNI.getInstance(), args.toArray());
      if (result instanceof WebDriverException) throw (WebDriverException)result;
      return result;
    } catch (IllegalAccessException e) {
      throw new WebDriverException("Illegal access to " + ((Method)method).getName());
    } catch (InvocationTargetException e) {
      throw new WebDriverException(e.toString());
    }
  }

  /**
   * Serialize object to a ByteBuffer
   *
   * @param stream ByteBuffer where object will be put
   * @param object Object to serialize
   */
  public static void serialize(ByteBuffer stream, Object object) {
    if (object == null) {
      stream.put(nullType);
      stream.putInt(0);
    } else if (object instanceof Long) {
      stream.put(longType);
      stream.putInt(-1);
      stream.putLong((Long)object);
    } else if (object instanceof Integer) {
      stream.put(intType);
      stream.putInt(-1);
      stream.putInt((Integer)object);
    } else if (object instanceof Double) {
      stream.put(doubleType);
      stream.putInt(-1);
      stream.putDouble((Double)object);
    } else if (object instanceof Boolean) {
      stream.put(booleanType);
      stream.putInt(-1);
      stream.put((Boolean)object ? (byte)1 : (byte)0);
    } else if (object instanceof Object[]) {
      Object[] array = (Object[])object;
      stream.put(arrayType);
      stream.putInt(array.length);
      for (int i = 0; i < array.length; i++) {
        serialize(stream, array[i]);
      }
    } else if (object instanceof String) {
      stream.put(stringType);
      stream.putInt(((String)object).getBytes().length);
      stream.put(((String)object).getBytes());
    } else if (object instanceof Method){
      stream.put(methodType);
      stream.putInt(((Method)object).getName().getBytes().length);
      stream.put(((Method)object).getName().getBytes());
    } else if (object instanceof Map) {
      final Map map = (Map)object;
      int len = map.size();
      stream.put(mapType);
      stream.putInt(len);
      for (Object entry : map.entrySet()) {
        serialize(stream, ((Map.Entry)entry).getKey());
        serialize(stream, ((Map.Entry)entry).getValue());
      }
    } else if (object instanceof List) {
      final List obj = (List)object;
      int size = obj.size();
      stream.put(listType);
      stream.putInt(size);
      serialize(stream, object.getClass().getName());
      for (Object entry : obj) {
        serialize(stream, entry);
        size--;
      }
      assert size == 0;
    } else if (object instanceof Collection) {
      final Collection obj = (Collection)object;
      int size = obj.size();
      stream.put(collectionType);
      stream.putInt(size);
      serialize(stream, object.getClass().getName());
      for (Object entry : obj) {
        serialize(stream, entry);
        size--;
      }
      assert size == 0;
    } else if (object instanceof ResultSetRows) {
      final ResultSetRows obj = (ResultSetRows)object;
      int size = obj.size();
      stream.put(resultSetRowsType);
      stream.putInt(size);
      for (int i = 0; i < size; i++) {
        serialize(stream, obj.item(i));
      }
    } else if (object instanceof ResultSet) {
      stream.put(resultSetType);
      stream.putInt(-1);
      final ResultSet obj = (ResultSet)object;
      stream.putInt(obj.getLastInsertedRowId());
      stream.putInt(obj.getNumberOfRowsAffected());
      serialize(stream, obj.rows());
    } else if (object instanceof Location) {
      stream.put(locationType);
      stream.putInt(-1);
      final Location obj = (Location)object;
      stream.putDouble(obj.getLatitude());
      stream.putDouble(obj.getLongitude());
      stream.putDouble(obj.getAltitude());
    } else if (object instanceof AppCacheEntry) {
      stream.put(appCacheEntryType);
      stream.putInt(-1);
      final AppCacheEntry obj = (AppCacheEntry)object;
      stream.putInt(obj.getType().value());
      serialize(stream, obj.getUrl());
      serialize(stream, obj.getMimeType());
    } else if (object instanceof WebKitDriver) {
      stream.put(webKitDriverType);
      stream.putInt(-1);
      stream.putLong(((WebKitDriver)object).getController());
    } else if (object instanceof WebKitWebElement) {
      stream.put(webKitWebElementType);
      ((WebKitWebElement)object).assertElementNotStale();
      stream.putInt(-1);
      stream.putLong(((WebKitDriver)((WebKitWebElement)object).getWrappedDriver()).getController());
      stream.putLong(((WebKitWebElement)object).getElement());
    } else if (object instanceof Rectangle) {
      stream.put(rectangleType);
      stream.putInt(-1);
      Rectangle rect = (Rectangle)object;
      stream.putDouble(rect.getX());
      stream.putDouble(rect.getY());
      stream.putDouble(rect.getSize().getWidth());
      stream.putDouble(rect.getSize().getHeight());
    } else if (object instanceof WebDriverException) {
      stream.put(webDriverExceptionType);
      serializeString(stream, ((WebDriverException)object).getMessage());
    } else if (object instanceof Exception) {
      stream.put(exceptionType);
      serializeString(stream, object.getClass().getName());
      serialize(stream, (((Exception)object).getMessage()));
    } else
      throw new WebDriverException("Unknow data type during serializationi " + object.toString());
  }

  /**
   * Deserialize object from Byte stream
   *
   * @param stream ByteBuffer with serialized object
   * @return deserialized object
   */
  public static Object deserialize(ByteBuffer stream, WebKitDriver driver) {
    byte type = stream.get();
    int size = stream.getInt();
    switch (type) {
      case nullType:
        return null;
      case longType:
        return stream.getLong();
      case intType:
        return stream.getInt();
      case doubleType:
        return stream.getDouble();
      case booleanType:
        byte bool = stream.get();
        if (bool == 0) return new Boolean(false);
        return new Boolean(true);
      case stringType:
        String s = new String(stream.array(), stream.position(), size);
        stream.position(stream.position()+size);
        return s;
      case arrayType:
        ArrayList array = new ArrayList(size);
        for (int i = 0; i < size; i++)
          array.add(deserialize(stream, driver));
        return array.toArray();
      case methodType:
        String name = new String(stream.array(), stream.position(), size);
        stream.position(stream.position()+size);
        try {
        // FIXME at the moment all methods should have different names
        // otherwise method lookup may fail
          Class webDriver = Class.forName("org.openqa.selenium.webkit.WebKitJNI");
          Method[] allMethods = webDriver.getDeclaredMethods();
          for (Method method : allMethods) {
            if (name.equals(method.getName())) return method;
          }
        } catch (ClassNotFoundException e) {
          throw new WebDriverException("Unable to found WebKitJNI class");
        }
        throw new WebDriverException("Unable to look up method " + name);
      case mapType:
        Map map = new HashMap();
        for (int i = 0; i < size; i++) {
          Object key   = deserialize(stream, driver);
          Object value = deserialize(stream, driver);
          map.put(key, value);
        }
        return map;
      case listType:
        String listTypeName = (String)deserialize(stream, driver);
        List list = null;
        try {
          list = (List)Class.forName(listTypeName).newInstance();
        } catch (Exception e) {
          throw new WebDriverException("Deserializer: List class not found: "
            + listTypeName);
        }
        for (int i = 0; i < size; i++)
          list.add(deserialize(stream, driver));
        return list;
      case collectionType:
        String collectionTypeName = (String)deserialize(stream, driver);
        Collection collection = null;
        try {
          collection = (Collection)Class.forName(collectionTypeName).newInstance();
        } catch (Exception e) {
          throw new WebDriverException("Deserializer: Collection class not found: "
            + collectionTypeName);
        }
        for (int i = 0; i < size; i++)
          collection.add(deserialize(stream, driver));
        return collection;
      case resultSetType: {
        int insertId       = stream.getInt();
        int rowsAffected   = stream.getInt();
        ResultSetRows rows = (ResultSetRows)deserialize(stream, driver);
        return new ResultSet(insertId, rowsAffected, rows);
      }
      case resultSetRowsType: {
        List<Map<String, Object>> rows = new ArrayList(size);
        for (int i = 0; i < size; i++) {
          rows.add((Map<String, Object>)deserialize(stream, driver));
        }
        return new ResultSetRows(rows);
      }
      case locationType: {
        double latitude  = stream.getDouble();
        double longitude = stream.getDouble();
        double altitude  = stream.getDouble();
        return new Location(latitude, longitude, altitude);
      }
      case appCacheEntryType: {
        final AppCacheType [] aACType = {
            AppCacheType.MASTER, AppCacheType.MANIFEST,
            AppCacheType.EXPLICIT, AppCacheType.FALLBACK
        };
        int i = stream.getInt();
        if (i < 0 || i >= aACType.length)
          throw new WebDriverException("Unknown AppCacheType");
        String url      = (String)deserialize(stream, driver);
        String mimeType = (String)deserialize(stream, driver);
        return new AppCacheEntry(aACType[i], url, mimeType);
      }
      case webKitDriverType:
        long webDriver = stream.getLong();
        if (driver == null) return new WebKitDriver(webDriver);
        return driver;
      case webKitWebElementType:
        long parent = stream.getLong();
        long element = stream.getLong(); 
        WebKitDriver driverFromStream = driver;
        if (driver == null) driverFromStream = new WebKitDriver(parent);
        return new WebKitWebElement(driverFromStream, element);
      case rectangleType:
        int x = (int)stream.getDouble();
        int y = (int)stream.getDouble();
        int width = (int)stream.getInt();
        int height = (int)stream.getInt();
        return new Rectangle(x, y, width, height);
      case webDriverExceptionType:
        String message = deserializeString(stream, size);
        throw new WebDriverException(message);
      case exceptionType:
        String className = deserializeString(stream, size);
        try {
          Class exceptionClass = Class.forName(className);
          Class stringClass = Class.forName("java.lang.String");
          Constructor constructor = exceptionClass.getConstructor(stringClass);
          Object errMessage = deserialize(stream);
          if (errMessage instanceof String || errMessage == null) {
              throw (Exception)constructor.newInstance((String)errMessage);
          }  else throw new WebDriverException("Exception of unknown type");
        } catch (Exception e) {
          throw new WebDriverException(e.toString());
        }
      default:
        throw new WebDriverException("Unknown data type during deserialization: " + type);
    }
  }

  public static Object deserialize(ByteBuffer stream) {
    return deserialize(stream, null);
  }
  
  private static void serializeString(ByteBuffer stream, String object) {
    stream.putInt(object.getBytes().length);
    stream.put(object.getBytes());
  }

  private static String deserializeString(ByteBuffer stream, int size) {
    String s = new String(stream.array(), stream.position(), size);
    stream.position(stream.position()+size);
    return s;
  }
}
