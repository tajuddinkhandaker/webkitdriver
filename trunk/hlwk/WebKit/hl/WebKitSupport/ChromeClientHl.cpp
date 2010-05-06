/*
 * Copyright (C) 2007 Kevin Ollivier <kevino@theolliviers.com>
 *
 * All rights reserved.
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
#include "CString.h"
#include "ChromeClientHl.h"
#include "Console.h"
#if ENABLE(DATABASE)
#include "DatabaseTracker.h"
#endif
#include "FileChooser.h"
#include "FloatRect.h"
#include "Frame.h"
#include "Page.h"
#include "Geolocation.h"
#include "PageGroup.h"
#include "FrameLoaderClient.h"
#include "FrameLoadRequest.h"
#include "NotImplemented.h"
#include "PlatformString.h"

#include "WebKitDriver.h"
#include "WebKitDriverPrivate.h"

#include <stdio.h>

namespace WebCore {

ChromeClientHl::ChromeClientHl(WebKitDriver *drv) :
      driver(drv)
{
}

ChromeClientHl::~ChromeClientHl()
{
}

void ChromeClientHl::chromeDestroyed()
{
    notImplemented();
}

void ChromeClientHl::setWindowRect(const FloatRect&)
{
    notImplemented();
}

FloatRect ChromeClientHl::windowRect()
{
    notImplemented();
    return FloatRect(0,0,800,600);
}

FloatRect ChromeClientHl::pageRect()
{
    notImplemented();
    return FloatRect(0,0,800,600);
}

float ChromeClientHl::scaleFactor()
{
    notImplemented();
    return 1.0;
}

void ChromeClientHl::focus()
{
    notImplemented();
}

void ChromeClientHl::unfocus()
{
    notImplemented();
}

bool ChromeClientHl::canTakeFocus(FocusDirection)
{
    notImplemented();
    return true;
}

void ChromeClientHl::takeFocus(FocusDirection)
{
    notImplemented();
}

void ChromeClientHl::focusedNodeChanged(Node*)
{
}

Page* ChromeClientHl::createWindow(Frame* frame, const FrameLoadRequest& request, const WindowFeatures&)
{
    WebKitDriver *drv = new WebKitDriver(frame->loader()->client()->userAgent(request.resourceRequest().url()));
    return drv->priv->page;
}

Page* ChromeClientHl::createModalDialog(Frame*, const FrameLoadRequest&)
{
    notImplemented();
    return 0;
}

void ChromeClientHl::show()
{
    notImplemented();
}

bool ChromeClientHl::canRunModal()
{
    notImplemented();
}

void ChromeClientHl::runModal()
{
    notImplemented();
}

void ChromeClientHl::setToolbarsVisible(bool)
{
    notImplemented();
}

bool ChromeClientHl::toolbarsVisible()
{
    notImplemented();
    return false;
}

void ChromeClientHl::setStatusbarVisible(bool)
{
    notImplemented();
}

bool ChromeClientHl::statusbarVisible()
{
    notImplemented();
    return false;
}

void ChromeClientHl::setScrollbarsVisible(bool)
{
    notImplemented();
}

bool ChromeClientHl::scrollbarsVisible()
{
    notImplemented();
    return false;
}

void ChromeClientHl::setMenubarVisible(bool)
{
    notImplemented();
}

bool ChromeClientHl::menubarVisible()
{
    notImplemented();
    return false;
}

void ChromeClientHl::setResizable(bool)
{
    notImplemented();
}

void ChromeClientHl::addMessageToConsole(MessageSource source,
                                          MessageType type,
                                          MessageLevel level,
                                          const String& message,
                                          unsigned int lineNumber,
                                          const String& sourceID)
{
    notImplemented();
    fprintf(stderr, "[JS error at %s:%d]: %s\n",sourceID.utf8().data(), 
            lineNumber, message.utf8().data());
}

bool ChromeClientHl::canRunBeforeUnloadConfirmPanel()
{
    notImplemented();
    return true;
}

bool ChromeClientHl::runBeforeUnloadConfirmPanel(const String& string,
                                                  Frame* frame)
{
    notImplemented();
    return true;
}

void ChromeClientHl::closeWindowSoon()
{
    if (driver) {
        delete driver;
        driver = 0;
    }
}

/*
    Sites for testing prompts: 
    Alert - just type in a bad web address or http://www.htmlite.com/JS002.php
    Prompt - http://www.htmlite.com/JS007.php
    Confirm - http://www.htmlite.com/JS006.php
*/

void ChromeClientHl::runJavaScriptAlert(Frame* frame, const String& string)
{
    alertText = string;
    fprintf(stderr, "JS alert: %s\n", string.utf8().data());
}

String& ChromeClientHl::accessAlertText()
{
    return alertText;
}

bool ChromeClientHl::runJavaScriptConfirm(Frame* frame, const String& string)
{
    bool result = false;
    notImplemented();
    return result;
}

bool ChromeClientHl::runJavaScriptPrompt(Frame* frame, const String& message, const String& defaultValue, String& result)
{
    notImplemented();
    return false;
}

void ChromeClientHl::setStatusbarText(const String&)
{
    notImplemented();
}

bool ChromeClientHl::shouldInterruptJavaScript()
{
    notImplemented();
    return false;
}

bool ChromeClientHl::tabsToLinks() const
{
    notImplemented();
    return false;
}

IntRect ChromeClientHl::windowResizerRect() const
{
    notImplemented();
    return IntRect();
}

void ChromeClientHl::repaint(const IntRect& rect, bool contentChanged, bool immediate, bool repaintContentOnly)
{
    notImplemented();
}

IntRect ChromeClientHl::windowToScreen(const IntRect& rect) const
{
    notImplemented();
    return rect;
}

IntPoint ChromeClientHl::screenToWindow(const IntPoint& point) const
{
    notImplemented();
    return point;
}

PlatformPageClient ChromeClientHl::platformPageClient() const
{
    notImplemented();
    return 0;
}

void ChromeClientHl::contentsSizeChanged(Frame*, const IntSize&) const
{
    notImplemented();
}

void ChromeClientHl::scrollBackingStore(int dx, int dy, 
                    const IntRect& scrollViewRect, 
                    const IntRect& clipRect)
{
    notImplemented();
}

void ChromeClientHl::updateBackingStore()
{
    notImplemented();
}

void ChromeClientHl::mouseDidMoveOverElement(const HitTestResult&, unsigned modifierFlags)
{
    notImplemented();
}

void ChromeClientHl::setToolTip(const String& tip, TextDirection)
{
    notImplemented();
}

void ChromeClientHl::print(Frame*)
{
    notImplemented();
}

#if ENABLE(DATABASE)
void ChromeClientHl::exceededDatabaseQuota(Frame* frame, const String&)
{
    if (Document* document = frame->document()) {
        unsigned long long quota = 5 * 1024 * 1024;
        if (!DatabaseTracker::tracker().hasEntryForOrigin(document->securityOrigin()))
            DatabaseTracker::tracker().setQuota(document->securityOrigin(), quota);
    }
}
#endif

#if ENABLE(OFFLINE_WEB_APPLICATIONS)
void ChromeClientHl::reachedMaxAppCacheSize(int64_t spaceNeeded)
{
    notImplemented();
}
#endif

void ChromeClientHl::scroll(const IntSize&, const IntRect&, const IntRect&)
{
    notImplemented();
}

void ChromeClientHl::runOpenPanel(Frame*, PassRefPtr<FileChooser>)
{
    notImplemented();
}

bool ChromeClientHl::setCursor(PlatformCursorHandle)
{
    notImplemented();
    return false;
}

void ChromeClientHl::requestGeolocationPermissionForFrame(Frame* frame, Geolocation* geolocation)
{
    // See the comment in WebCore/page/ChromeClient.h
    geolocation->setIsAllowed(true);
}
#if 0
void cancelGeolocationPermissionRequestForFrame(Frame*)
{
    notImplemented();
}

void iconForFiles(const Vector<String>&, PassRefPtr<FileChooser>)
{
    notImplemented();
}
#endif
}
