/*
 * Copyright (C) 2009, 2010 Apple Inc. All rights reserved.
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

#ifndef MediaPlayerPrivateHl_h
#define MediaPlayerPrivateHl_h

#if ENABLE(VIDEO)

#include "MediaPlayerPrivate.h"

namespace WebCore {

//class IntRect;
//class IntSize;
//class String;

class MediaPlayerPrivate : public MediaPlayerPrivateInterface {
public:
    static void registerMediaEngine(MediaEngineRegistrar);
    ~MediaPlayerPrivate() {};

    virtual void load(const String& url);
    virtual void cancelLoad();
    
    virtual void prepareToPlay() { }
    virtual PlatformMedia platformMedia() const { return NoPlatformMedia; }
#if USE(ACCELERATED_COMPOSITING)
    virtual PlatformLayer* platformLayer() const { return 0; }
#endif

    virtual void play();
    virtual void pause();    

    virtual bool supportsFullscreen() const { return false; }
    virtual bool supportsSave() const { return false; }

    virtual IntSize naturalSize() const;

    virtual bool hasVideo() const;
    virtual bool hasAudio() const;

    virtual void setVisible(bool);

    virtual float duration() const;

    virtual float currentTime() const;
    virtual void seek(float);
    virtual bool seeking() const;

    virtual float startTime() const { return 0; }

    virtual void setRate(float);
    virtual void setPreservesPitch(bool) { }

    virtual bool paused() const { return m_paused; }

    virtual void setVolume(float);

    virtual bool supportsMuting() const { return true; }
    virtual void setMuted(bool muted) { m_muted = muted; }

    virtual bool hasClosedCaptions() const { return false; }    
    virtual void setClosedCaptionsVisible(bool) { }

    virtual MediaPlayer::NetworkState networkState() const;
    virtual MediaPlayer::ReadyState readyState() const;

    virtual float maxTimeSeekable() const;
    virtual PassRefPtr<TimeRanges> buffered() const;

    virtual unsigned bytesLoaded() const;

    virtual void setSize(const IntSize&);

    virtual void paint(GraphicsContext*, const IntRect&);

    virtual void paintCurrentFrameInContext(GraphicsContext* c, const IntRect& r) { paint(c, r); }

    virtual void setAutobuffer(bool) { };

    virtual bool hasAvailableVideoFrame() const { return readyState() >= MediaPlayer::HaveCurrentData; }

    virtual bool canLoadPoster() const { return false; }
    virtual void setPoster(const String&) { }

#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
    virtual void deliverNotification(MediaPlayerProxyNotificationType);
    virtual void setMediaPlayerProxy(WebMediaPlayerProxy*);
#endif

#if USE(ACCELERATED_COMPOSITING)
    // whether accelerated rendering is supported by the media engine for the current media.
    virtual bool supportsAcceleratedRendering() const { return false; }
    // called when the rendering system flips the into or out of accelerated rendering mode.
    virtual void acceleratedRenderingStateChanged() { }
#endif

    virtual bool hasSingleSecurityOrigin() const { return false; }

    virtual MediaPlayer::MovieLoadType movieLoadType() const { return MediaPlayer::Unknown; }

    private:
        MediaPlayerPrivate(MediaPlayer*);

        static PassOwnPtr<MediaPlayerPrivateInterface> create(MediaPlayer* player);

        static void getSupportedTypes(HashSet<String>&);
        static MediaPlayer::SupportsType supportsType(const String& type, const String& codecs);

        MediaPlayer*    m_player;
        bool    m_muted;
        bool    m_paused;
        float   m_currentTime;

};

}

#endif
#endif
