# Introduction #

Add your content here.

# WebKit #
## Code structure ##
WebKit code is divided into several directories, but in general it can be divided into tree big subprojects, which are tightly coupled with each other:
  * _JavaScriptCore_
  * _WebCore_
  * _WebKit_

**JavaScriptCode** contains source code of javascript engine used in WebKit by default (it can use other JS engines, e.g. V8 in case of Chome browser). Despite its name, it also contains a number of utility classes and functions used all across WebKit source code, as well as essential system-specific functions like thread creation and synchronization, access to system time.

**WebCore** contains source code of core browser functionality, like fetching, parsing and rendering of web pages, rendering form controls, access to local storage etc. Thought it contains mostly a generic code, a lot of code is system and port-specific.

**WebKit** contains source code specific to each port - Qt, Wx, Gtk, Chrome. It provides high-level API and widgets.

WebKit does not provide any generic library. Instead, several ports exists, which produce port-specific dynamic libraries linking together generic WebKit code and port-specific code. There is no clear distinction between generic and port-specific code - any port can redefine almost any generic functionality when needed. This leads to situation when header files are filled with lots of port-specific defines. Except this, the code has clear structure; all port-specific code is kept in port-specific directories.

## Data types ##
  * String, PlatformString, StringImpl, AtomicString
  * RefPtr
  * Hash, Vector

# Headless WebKit #

## Code structure ##

Code structure of headless port resembles code structure of other exsistings WebKit ports such as Gtk, Qt or Wx. Headless port was derived from Wx implementation and its code structure is almost completely matches code structure of Wx port sources. In general, there is a number of directories containing files specific for headless port, as well as modifications of common header files selected with C preprocessor.

Headless port does not implement actual page rendering and integration with windowing system, thus lots of the classes and methods it provides are just empty stubs to comply general WebKit interfaces.

Headless specific files live in the following directories:
  * _JavaScriptCore/wtf/hl_ - stubs for threading primitives
  * _WebCore/platform/hl_ - general functions
  * _WebCore/platform/graphics/hl_ - code related to drawing, widget and font rendering
  * _WebCore/platform/image-decoders/hl_ - stubs for unused but required decoding functions
  * _WebCore/platform/network/hl_ - implementation of cookie jar and local modifications of files originating from
  * _WebCore/platform/network/curl_

## Build System ##
Headless webkit port uses rake as a build system. Build instructions can be found in Rakefile located in hlwk directory. This rake script uses several helper functions which are kept separately and can be found in _hlwk/WebKitTool/hl/cc\_library.rb_ file.

Resulting library _libhlwk.so_ is placed to _hlwk/WebKitBuild/Release_ directory along with jsc binary, which is standalone command-line javascript interpreter.

## Modifications of original WebKit source code ##
While most of the headless-specific code is kept separately in _hl_ directories, modifications of common header files are requires to specify platform-specific data types. These modifications can be found in header files of WebCore project, guarded with preprocessor directives:
```
#if PLATFORM(HEADLESS)
...
#endif
```

In most cases this is used to provide stubs instead of OS or windowing system objects in the code related to on-screen rendering. This approach can be used to modification of class interfaces, but it is highly not recommended and acceptable only if same functionality can not be implemented in other way.

Known modification of interfaces:
  * Public method `void networkStateChange(bool online)` is added to `NetworkStateNotifier` class to make it possible emulate switching between online and offline mode.

## Handling scheduled events ##
A lot of WebKit functionality relies on scheduled events, which should be called from main thread event loop. The top-level interface for scheduling functions is WebCore::Timer class. Timer “fire“ method is invoked after specified interval of time. It is a common practice to create timers with zero interval to invoke a function as soon as possible from main event loop.

All windowing systems or libraries provide main event loop concept, however this is not true for headless port. Headless port is not event-driven, so it does not need endless event loop. Instead, headless port provide utility functions to process scheduled events when needed. Unlike real event loop, these functions should be invoked explicitly by programmer.

`bool Headless::processTimer()` process oldest scheduled timer if any. If timer interval is elapsed, it is fired immediately, otherwise execution is blocked till it is elapsed. The function returns true if timer was fired, false if there are no scheduled timers remain. Note that scheduled function can spawn another scheduled function.

`bool Headless::processExpiredTimers()` is a helper function which invokes all scheduled timers with elapsed intervals. Its semantics can be described as “process all scheduled events which will not block execution of the current function“.

These high-level functions depends on functionality provided by very simple functions from _WebCore/platform/SharedTimerHl.cpp_  which are used as a backend by all timer classes. Headless SharedTimer implementation does not use any system-specific timer or scheduling mechanisms. Instead, it just handles variable for function pointer and time when it should be fired, leaving all handling logics to 'processTimer' function.

## Threads synchronization ##
While most of the web page rendering functionality is done within a single thread, there is number of exceptions. Such features as database support or workers spawn separate threads which require synchronization with main thread. Extra threads can schedule invocation of a function in main thread. Main thread should call `WTF::dispatchFunctionsFromMainThread()` function to invoke such scheduled functions. Since headless port does not have native event loop, this functions is invoked each time processTimer or processExpiredTimers functions are invoked to provide transparent thread synchronization.

## Keyboard events ##
There is no real keyboard in headless mode, however lots of the test cases send key presses and expect they are correctly handled by browser. To achieve this, headless port have own implementation of `PlatformKeyboardEvent` class. The class is designed to match keyboard interface of WebDriver. Unlike other platform, headless PlatformKeyboardEvent is constructed using unicode character code, which can represent either any keyboard character, navigation or modifier key like LEFT, RIGHT, SHIFT. Each unicode character code is analyzed and converted to such keyboard event properties as virtual key code, key character and modifier keys state, so it can hardly be distinguished from real keyboard event in platform-independent WebKit code, including javascript.

## Fonts handling ##
Font rendering is not supported at the moment by headless webkit (though it is planned in next releases). However, headless webkit has to provide stubs for font rendering to integrate with other WebKit subsystems.

Headless WebKit provides very simple font stubs, which allows only querying of some fake font characteristics like accent, font size, font family, etc. This is sufficient to WebKit functionality, however can result in unexpected results when calculating dimensions of region occupied by text.

## Rendering ##
Rendering is completely torn off at the moment. There exists stubs for some font controls, like checkbox and input which are used to adjust control dimensions only.

# WebKitDriver #

WebKitDriver is one of the drivers of WebDriver project, built on top of headless webkit

## Code Structure ##
WebKitDriver consists of Java part, C++ bindings implementing JNI interface and unit tests. Java part is located in _driver/java_ directory, tests can be found in _driver/test_. JNI bindings are kept separately in WebKit tree, the path is
_hlwk/WebKit/hl_.

Java part consists of the following files:
  * _WebKitDriver.java_ - implementation of WebDriver and related interfaces
  * _WebKitWebElement.java_ - implementation of WebElement and related interfaces
  * _WebKitInterface_ - interface describing methods which are invoked using JNI
  * _WebKitJNI_ - class providing access to JNI methods
  * _WebKitSerilze_ - implementation of serialization for inter-process communication
  * _WebKitWrapper_ - implementation of child process wrapper

C++ part consists of JNI bindings and helper functions for headless WebKit integration:
  * JavaBindings.cpp - JNI bindings, contain most of WebDriver-specific logics
  * WebKitDriver.cpp - high-level driver object

## Events handling ##
## Multiple processes and threads ##
Current implementation of WebKit implies lots of functions can be called only from main thread. Though WebKit supports multiple threads, its threads have strict roles, e.g. SQL execution thread, WebWorker thread, etc. However, most of the rendering and html processing can be done only in main thread. To assure this, entry points have assertions checking they are invoked from main thread, and no synchronization primitives like mutexes or semaphores are used to protect access to global variables and objects. Besides that, WebKit uses several singleton objects, making it difficult to co-exist completely independent instances of WebKitDriver at same time.

To solve this limitation, WebKitDriver is able to spawn headless WebKit in a separate process when WebKitDriver object is created in a thread other than main. This approach solves all object access issues, however brings some delay due to need of object serialization and exchange between separate processes.

WebKitDriver constructor checks, is current thread is main one, and spawns separate process and creates dynamic proxy object for `WebKitInterface` interface instead of direct access JNI functions. This proxy object uses custom `WebKitSerialize` class to serialize and de-serialize objects when passing to the spawned process via TCP socket.

Spawned process is created using ProcessBuilder API. It is a very simple Java wrapper around headless webkit, which connects to TCP port of loopback interface, specified on command line, and then reads incoming data, deserializes it, invokes JNI method, serializes and sends response back. The wrapper is implemented in `WebKitWrapper` class.


## Dependencies ##

Java, JNI

## Limitations ##

  * Database, application cache and cookie storage is shared between all instances of WebKitDriver, living within a process.
  * CSS offsets are rounded to integers
  * DesignMode is not properly supported
  * Online/offline mode is shared between all instances of WebKitDriver within a process.

## Extending WebKitDriver ##

### Adding new keyboard shortcuts ###
WebKitDriver does not use system-specific events, and any keyboard shortcut which may be handled by operating system automatically (e.g. Control-C) require explicit support in WebKitDriver. The number of such shortcuts can be large and they can depend on operating system, thus only a limited set of most widel-used and important shortcuts is implemented right now.  However, new shortcut can be added quite easily thanks to WebKit internal editor implementation.

The list of supported shortcuts is:
  * **Ctrl-C** - copy selection to clipboard
  * **Ctrl-V** - paste data from clipboard
  * **Ctrl-X** - move selection to clipboard
  * **Ctrl-A** - select all
  * Shift + navigation keys - move cursor and modify selection

WebKit editor has a large list of available editing actions, which can be found in _WebCore/editing/EditorCommand.cpp_ file in WebKit source tree. Developer only need to map keyboard shortcut to
one of this actions. This can be done in `handleKeyboardEvent` method of `EditorClientHl` class, defined in _WebKit/hl/WebKitSupport/EditorClientHl.cpp_ file. This method analyses keyboard code and modifiers of keyboard event and invokes appropriate editor method.