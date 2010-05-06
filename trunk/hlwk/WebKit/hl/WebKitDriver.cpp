/*
 * Copyright (C) 2007 Kevin Ollivier  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
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
    printf("Clean up databases\n");
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
 
    // Initialize path to database and appcache unless already initialized
    if (WebCore::DatabaseTracker::tracker().databaseDirectoryPath().isNull()) {
        // FIXME: unix-specific code below
        char tempDirTemplate[] = "/tmp/webkitdriverXXXXXX";
        char *tempDirName = mktemp(tempDirTemplate);
        if (tempDirName) {
            WebCore::String tempDir = WebCore::String::fromUTF8(tempDirName);
            WebCore::DatabaseTracker::tracker().setDatabaseDirectoryPath(tempDir);
            WebCore::cacheStorage().setCacheDirectory(tempDir);
            setDatabaseEnabled(true);
        } else {
            WTFLog(&WebCore::LogStorageAPI, "Failed to initialize temporary directory, storage API disabled");
        }
    }
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

void WebKitDriver::Stop() {
}

void WebKitDriver::Reload() {
    if (priv->frame && priv->frame->loader()) {
        priv->frame->loader()->reload();
    }
}

void WebKitDriver::LoadURL(const char* url) {
    WebCore::String str = WebCore::String::fromUTF8(url);
    WebCore::KURL kurl = WebCore::KURL(WebCore::KURL(), str, WebCore::UTF8Encoding());
    priv->frame->loader()->load(kurl, false);
    waitFrameLoaded();
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

bool WebKitDriver::CanGoBack()
{
//    if (priv->frame && priv->frame->page() && priv->frame->page()->backForwardList())
//        return priv->frame->page()->backForwardList()->backItem() != NULL;

    return false;
}

bool WebKitDriver::CanGoForward() {
//    if (priv->frame && priv->frame->page() && priv->frame->page()->backForwardList())
//        return priv->frame->page()->backForwardList()->forwardItem() != NULL;

    return false;
}

void WebKitDriver::Undo() {
}

void WebKitDriver::Redo() {
}

bool WebKitDriver::CanUndo() {
    return false;
}

bool WebKitDriver::CanRedo() {
    return false;
}

bool WebKitDriver::CanIncreaseTextSize() const {
    return false;
}

void WebKitDriver::IncreaseTextSize() {
}

bool WebKitDriver::CanDecreaseTextSize() const {
    return false;
}

void WebKitDriver::DecreaseTextSize() {        
}

void WebKitDriver::ResetTextSize() {
}

void WebKitDriver::MakeEditable(bool enable) {
    m_isEditable = enable;
}

bool WebKitDriver::CanCopy() {
    return false;
}

void WebKitDriver::Copy() {
}

bool WebKitDriver::CanCut() {
    return false;
}

void WebKitDriver::Cut() {
}

bool WebKitDriver::CanPaste() {
    return false;
}

void WebKitDriver::Paste() {
}

bool WebKitDriver::ShouldClose() const {
    return true;
}

void WebKitDriver::processAllEvents() {
    while ( Headless::processTimer() ) {
        WTFLog(&WebCore::LogEvents, "Process timers...\n");
    };
}

