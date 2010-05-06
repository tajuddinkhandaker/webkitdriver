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
 
#ifndef WEBKITDRIVER_H
#define WEBKITDRIVER_H

#include "ResourceError.h"

class WebKitDriverPrivate;

namespace WebCore {
    class ChromeClientHl;
    class FrameLoaderClientHl;
    class EditorClientHl;
    class Frame;
    class GeolocationControllerClientHl;
}

class WebKitDriver
{
    // ChromeClientHl needs to get the Page* stored by the wxWebView
    // for the createWindow function. 
    friend class WebCore::ChromeClientHl;
    friend class WebCore::FrameLoaderClientHl;
    friend class WebCore::EditorClientHl;

public:
    WebKitDriver(WebCore::String userAgent=WebCore::String());

    static void processAllEvents();
    static void cleanup();
    
    ~WebKitDriver();
    
    void LoadURL(const char* url);
    bool GoBack();
    bool GoForward();
    void Stop();
    void Reload();
    
    bool CanGoBack();
    bool CanGoForward();
    
    bool CanCut();
    bool CanCopy();
    bool CanPaste();
    
    void Cut();
    void Copy();
    void Paste();
    
    bool CanUndo();
    bool CanRedo();
    
    void Undo();
    void Redo();
    
    bool CanIncreaseTextSize() const;
    void IncreaseTextSize();
    bool CanDecreaseTextSize() const;
    void DecreaseTextSize();
    void ResetTextSize();
    void MakeEditable(bool enable);
    bool IsEditable() const { return m_isEditable; }

    bool IsReady() const { return m_loading == 0; }
    
    WebCore::Frame* GetFrame();
    void SetFrame(WebCore::Frame*);
    WebCore::Frame* GetMainFrame();
    WebCore::GeolocationControllerClientHl* GetGeolocationClient();
    bool setDatabaseEnabled(bool);

    bool ShouldClose() const;

private:
    bool waitFrameLoaded();
    
    float m_textMagnifier;
    bool m_isEditable;
    bool m_isInitialized;
    bool m_beingDestroyed;

    WebKitDriverPrivate *priv;
    int m_loading;  // Number of loading frames
    static int instances; // Number of WebKitDriver instances;
};

namespace Headless {
	bool processTimer();
	void processExpiredTimers();
}

#endif // ifndef WEBKITDRIVER_H
