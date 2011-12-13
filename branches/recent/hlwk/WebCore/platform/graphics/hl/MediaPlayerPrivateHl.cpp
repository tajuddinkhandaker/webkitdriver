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

#include "config.h"

#if ENABLE(VIDEO)
#include "IntRect.h"
#include "MediaPlayerPrivateHl.h"
#include "NotImplemented.h"
#include "TimeRanges.h"
#include <wtf/HashSet.h>

namespace WebCore {
MediaPlayerPrivate::MediaPlayerPrivate(MediaPlayer* player):
    m_player(player),
    m_muted(false),
    m_paused(false),
    m_currentTime(0.0)
{
    ;
}

void MediaPlayerPrivate::registerMediaEngine(MediaEngineRegistrar registrar)
{
     registrar(create, getSupportedTypes, supportsType);
}

void MediaPlayerPrivate::load(const String& url)
{
    m_currentTime = 0.0;
    notImplemented();
}

void MediaPlayerPrivate::cancelLoad()
{
    notImplemented();
}

void MediaPlayerPrivate::play()
{
    m_paused = false;
    notImplemented();
}

void MediaPlayerPrivate::pause()
{
    m_paused = true;
    notImplemented();
}

IntSize MediaPlayerPrivate::naturalSize() const
{
    notImplemented();
    return IntSize(640,480);
}

bool MediaPlayerPrivate::hasVideo() const
{
    notImplemented();
    return true;
}

bool MediaPlayerPrivate::hasAudio() const
{
    notImplemented();
    return true;
}

void MediaPlayerPrivate::setVisible(bool)
{
    notImplemented();
}

float MediaPlayerPrivate::duration() const
{
    notImplemented();
    return 100.0;
}

float MediaPlayerPrivate::currentTime() const
{
    notImplemented();
    return m_currentTime;
}

void MediaPlayerPrivate::seek(float pos)
{
    m_currentTime = pos;
    notImplemented();
}

bool MediaPlayerPrivate::seeking() const
{
    notImplemented();
    return false;
}

void MediaPlayerPrivate::setRate(float)
{
    notImplemented();
}

void MediaPlayerPrivate::setVolume(float)
{
    m_muted = false;
    notImplemented();
}

MediaPlayer::NetworkState MediaPlayerPrivate::networkState() const
{
    notImplemented();
    return MediaPlayer::Loaded;
}

MediaPlayer::ReadyState MediaPlayerPrivate::readyState() const
{
    notImplemented();
    return MediaPlayer::HaveEnoughData;
}

float MediaPlayerPrivate::maxTimeSeekable() const
{
    notImplemented();
    return 100.0;
}

PassRefPtr<TimeRanges> MediaPlayerPrivate::buffered() const
{
    notImplemented();
    return TimeRanges::create();
}

unsigned MediaPlayerPrivate::bytesLoaded() const
{
    notImplemented();
    return 0;
}

void MediaPlayerPrivate::setSize(const IntSize&)
{
    notImplemented();
}

void MediaPlayerPrivate::paint(GraphicsContext*, const IntRect&)
{
    notImplemented();
}

#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
void MediaPlayerPrivate::deliverNotification(MediaPlayerProxyNotificationType);
{
    notImplemented();
}

void MediaPlayerPrivate::setMediaPlayerProxy(WebMediaPlayerProxy*)
{
    notImplemented();
}
#endif

MediaPlayerPrivateInterface* MediaPlayerPrivate::create(MediaPlayer* player)
{
    return new MediaPlayerPrivate(player);
}

void MediaPlayerPrivate::getSupportedTypes(HashSet<String>&)
{
    notImplemented();
}

MediaPlayer::SupportsType MediaPlayerPrivate::supportsType(const String&, const String&)
{
    // FIXME: do the real thing
    notImplemented();
    return MediaPlayer::IsNotSupported;
}

}
#endif
