/*
Copyright 2007-2010 WebDriver committers

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

#include "config.h"
#include "ApplicationCacheStorage.h"
#include "CString.h"
#include "DatabaseTracker.h"
#include "Document.h"
#include "Editor.h"
#include "Element.h"
#include "EventHandler.h"
#include "Frame.h"
#include "FrameLoader.h"
#include "FrameView.h"
#include "FocusController.h"
#include "Geolocation.h"
#include "Headless.h"
#include "HitTestResult.h"
#include "HTMLFrameOwnerElement.h"
#include "markup.h"
#include "Logging.h"
#include "Node.h"
#include "NodeList.h"
#include "PlatformString.h"
#include "StaticNodeList.h"
#include "Page.h"
#include "PlatformString.h"
#include "RenderTreeAsText.h"
#include "RenderObject.h"
#include "RenderView.h"
#include "ScriptController.h"
#include "ScriptSourceCode.h"
#include "ScriptValue.h"
#include "Settings.h"
#include "SubstituteData.h"
#include "TextEncoding.h"
#include "XPathResult.h"

#include "JSDOMBinding.h"
#include <runtime/JSValue.h>
#include <runtime/UString.h>

#include "GeolocationControllerClientHl.h"
#include "EditorClientHl.h"
#include "DragClientHl.h"
#include "InspectorClientHl.h"
#include "ContextMenuClientHl.h"
#include "FrameLoaderClientHl.h"
#include "ChromeClientHl.h"
#include "DatabaseTrackerClient.h"

#include <wtf/CurrentTime.h>
#include <wtf/MainThread.h>

#include <unistd.h>

#include "WebKitDriver.h"
#include "WebKitDriverPrivate.h"


// Match Safari's min/max zoom sizes by default
#define MinimumTextSizeMultiplier       0.5f
#define MaximumTextSizeMultiplier       3.0f
#define TextSizeMultiplierRatio         1.2f

namespace Headless {
    static void (*timer_callback)(void) = NULL;
    double timer_time = 0;

    void set_timer_callback( void (*callback)(void), double timeSpec)
    {
        timer_callback = callback;
        timer_time = timeSpec;
    }

    // Waits for nearest callback event time and processes event queue.
    // One of these process timer functions have to be called in all get-functions
    // which may be used in a waiting loop.
    // See comment for processExpiredTimers below.
    bool processTimer() {
        // Process events scheduled from other threads first
        WTF::dispatchFunctionsFromMainThread();
        if (timer_callback && timer_time > 0) {
            double now = currentTime();
            if (timer_time > now) {
                unsigned long interval = \
                    (unsigned long)((timer_time - now) * 1000000);
                usleep(interval);
            }
            timer_time = 0;
            timer_callback();
            return true;
        }
        return false;
    }

    // Provides non-blocking processing queue of all callback events in main thread.
    // So it should be called within all get functions like findElement, getTitle, etc.
    // Especially when they are used in a loop for waiting changes in a page. Without
    // such calls all events will be frozen.
    void processExpiredTimers() {
        // Process events scheduled from other threads first
        WTF::dispatchFunctionsFromMainThread();
        while (timer_callback && timer_time > 0 && timer_time <= currentTime()) {
            timer_time = 0;
            timer_callback();
        }
    }
}

int WebKitDriver::instances = 0;

// Clean up temporary files and directories if exist
void WebKitDriver::cleanup()
{
    WTFLog(&WebCore::LogStorageAPI, "Clean up databases");
    WebCore::String path = WebCore::DatabaseTracker::tracker().databaseDirectoryPath();
    if (path.isNull())
        return;

    // Close all open databases, except ApplicationCache
    WebCore::DatabaseTracker::tracker().deleteAllDatabases();

    // If application cache database exists, remove it manually
    WebCore::String cacheFile = WebCore::pathByAppendingComponent(WebCore::cacheStorage().cacheDirectory(), "ApplicationCache.db");
    if (WebCore::fileExists(cacheFile)) {
        WebCore::cacheStorage().empty();
        WebCore::deleteFile(cacheFile);
    }

    // And finally remove database directory if exists
    if (WebCore::fileExists(path)) {
        WebCore::deleteEmptyDirectory(path);
    }
}

WebKitDriver::WebKitDriver(WebCore::String userAgent) :
    m_textMagnifier(1.0),
    m_isEditable(false),
    m_isInitialized(false),
    m_beingDestroyed(false),
    m_loading(0),
    priv() {

    WTF::initializeThreading();
    WebCore::InitializeLoggingChannelsIfNecessary();

    WebCore::HTMLFrameOwnerElement* parentFrame = 0;

    priv = new WebKitDriverPrivate;

    WebCore::EditorClientHl* editorClient = new WebCore::EditorClientHl();
#if ENABLE(CLIENT_BASED_GEOLOCATION)
    priv->geoClient = new WebCore::GeolocationControllerClientHl();
#endif
#if ENABLE(DATABASE)
    priv->dbClient = new WebCore::DatabaseTrackerClientHl(this);
#endif
    priv->page = new WebCore::Page(
        new WebCore::ChromeClientHl(this),
        new WebCore::ContextMenuClientHl(),
        editorClient,
        new WebCore::DragClientHl(),
        new WebCore::InspectorClientHl(),
        0,
        priv->geoClient
    );
    priv->page->setGroupName("headless");
#if ENABLE(CLIENT_BASED_GEOLOCATION)
    priv->geoClient->setController(priv->page->geolocationController());
#endif
    editorClient->setPage(priv->page);

    WebCore::FrameLoaderClientHl* loaderClient = new WebCore::FrameLoaderClientHl();
    if (!userAgent.isEmpty())
        loaderClient->setUserAgent(userAgent);
    RefPtr<WebCore::Frame> f = WebCore::Frame::create(priv->page, 0, loaderClient);
    priv->frame = priv->mainFrame = f.get();

    loaderClient->setFrame(this);
    priv->frame->init();

    WebCore::Settings* settings = priv->page->settings();
    settings->setLoadsImagesAutomatically(true);
    settings->setDefaultFixedFontSize(13);
    settings->setDefaultFontSize(16);
    settings->setSerifFontFamily("Times New Roman");
    settings->setFixedFontFamily("Courier New");
    settings->setSansSerifFontFamily("Arial");
    settings->setStandardFontFamily("Times New Roman");
    settings->setJavaScriptEnabled(true);
    settings->setJavaScriptCanOpenWindowsAutomatically(true);
    settings->setAllowScriptsToCloseWindows(true);

    WebCore::DatabaseTracker::tracker().setClient(priv->dbClient);
    // Initialize path to database and appcache unless already initialized
    if (WebCore::DatabaseTracker::tracker().databaseDirectoryPath().isNull()) {
        // FIXME: unix-specific code below
        char tempDirTemplate[] = "/tmp/webkitdriverXXXXXX";
        char *tempDirName = mktemp(tempDirTemplate);
        if (tempDirName) {
            WebCore::String tempDir = WebCore::String::fromUTF8(tempDirName);
            WebCore::DatabaseTracker::tracker().setDatabaseDirectoryPath(tempDir);
            WebCore::cacheStorage().setCacheDirectory(tempDir);
        } else {
            WTFLog(&WebCore::LogStorageAPI, "Failed to initialize temporary directory, storage API disabled");
        }
    }
    setDatabaseEnabled(true);
    instances++;
    m_isInitialized = true;
}

WebKitDriver::~WebKitDriver() {
    if (priv) {
        priv->page->focusController()->setActive(false);
        if (priv->mainFrame)
            priv->mainFrame->loader()->detachFromParent();
        if (priv->page) {
            delete priv->page;
            priv->page = 0;
        }
        delete priv;
    }
    if (!--instances) {
        WebKitDriver::cleanup();
    }
}

bool WebKitDriver::waitFrameLoaded() {
    while (priv->frame->loader()->isLoading() && Headless::processTimer()) {
        WTFLog(&WebCore::LogLoading, "Wait for loaded frame\n");
    };
    // TODO: return frame loading result - true if loaded successfully, false otherwise
    return true;
}

bool WebKitDriver::setDatabaseEnabled(bool enable)
{
    // Enable database and storage API only if database path was set successfully
    if (enable && WebCore::DatabaseTracker::tracker().databaseDirectoryPath().isNull()) {
        return false;
    }
    WebCore::Settings* settings = priv->page->settings();
    settings->setDatabasesEnabled(enable);
    settings->setLocalStorageEnabled(enable);
    settings->setOfflineWebApplicationCacheEnabled(enable);
}

WebCore::GeolocationControllerClientHl* WebKitDriver::GetGeolocationClient() {
    return priv->geoClient;
}

WebCore::DatabaseTrackerClientHl* WebKitDriver::GetSQLClient() {
    return priv->dbClient;
}

WebCore::Frame* WebKitDriver::GetFrame() {
    if (priv->frame == priv->mainFrame && priv->frame->document()->isFrameSet())
        return priv->frame->tree()->child(0);
    return priv->frame;
}

WebCore::Frame* WebKitDriver::GetMainFrame() {
    return priv->mainFrame;
}

void WebKitDriver::SetFrame(WebCore::Frame *frame) {
    priv->frame = frame;
}

void WebKitDriver::Reload() {
    if (priv->frame && priv->frame->loader()) {
        priv->frame->loader()->reload();
    }
}

bool WebKitDriver::GoBack() {
    if (priv->frame && priv->frame->page())
        return priv->frame->page()->goBack() && waitFrameLoaded();

    return false;
}

bool WebKitDriver::GoForward() {
    if (priv->frame && priv->frame->page())
        return priv->frame->page()->goForward() && waitFrameLoaded();

    return false;
}

void WebKitDriver::SetBusyState (bool isBusy, int who) {
    m_state = (m_state & !who) | (isBusy ? who : 0);
}

bool WebKitDriver::IsBusy(int who) {
    return m_state & who;
}
