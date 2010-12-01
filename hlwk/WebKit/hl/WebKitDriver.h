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
    class DatabaseTrackerClientHl;
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

    static bool initialize();
    static void cleanup();
    
    ~WebKitDriver();
    
    bool GoBack();
    bool GoForward();
    void Reload();
    
    void IncreaseTextSize();
    void DecreaseTextSize();
    void ResetTextSize();
    bool IsEditable() const { return m_isEditable; }

    bool IsReady() const { return m_loading == 0; }
    
    WebCore::Frame* GetFrame();
    void SetFrame(WebCore::Frame*);
    WebCore::Frame* GetMainFrame();
    WebCore::GeolocationControllerClientHl* GetGeolocationClient();
    WebCore::DatabaseTrackerClientHl* GetSQLClient();
    bool setDatabaseEnabled(bool);

    // HTML 5 asynchronous work support
    // generic state to provide information on who is doing asynchronous work
    // bitmask allows for several states at a time 
    static const int GEOLOCATION = 1; 
    static const int DATABASE = 2;
    static const int APPCACHE = 4;
    static const int ALL = -1; 

    bool IsBusy(int who = ALL);
    // By default will be returned busy state for whole system
    void SetBusyState (bool isBusy, int who = ALL);

private:
    bool waitFrameLoaded();
    
    float m_textMagnifier;
    bool m_isEditable;
    bool m_isInitialized;
    bool m_beingDestroyed;

    WebKitDriverPrivate *priv;
    int m_loading;  // Number of loading frames
    int m_state; // greater then 0 if some asynchronous tasks is working
    static int instances; // Number of WebKitDriver instances;
};

namespace Headless {
	bool processTimer();
	void processExpiredTimers();
}

#endif // ifndef WEBKITDRIVER_H
