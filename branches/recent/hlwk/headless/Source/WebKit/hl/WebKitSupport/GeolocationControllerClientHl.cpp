/*
 * Copyright (C) 2009 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "GeolocationControllerClientHl.h"

#include "GeolocationPosition.h"
#include "GeolocationController.h"
#include "Timer.h"

#if ENABLE(CLIENT_BASED_GEOLOCATION)

#include <stdio.h>

namespace WebCore {

GeolocationControllerClientHl::GeolocationControllerClientHl()
    : m_position(0)
    , m_controller(0)
    , m_updating(false)
    , m_timer(this, &WebCore::GeolocationControllerClientHl::timerCallback) {
}

GeolocationControllerClientHl::~GeolocationControllerClientHl() {
}

GeolocationPosition* GeolocationControllerClientHl::lastPosition() {
    return m_position.get(); 
}

void GeolocationControllerClientHl::startUpdating() { 
    m_updating = true;
    // starting timer to emulate asynchronous client work
    m_timer.startOneShot(0);
}

void GeolocationControllerClientHl::stopUpdating() { 
    m_updating = false;
    m_timer.stop();
}

void GeolocationControllerClientHl::setPosition(PassRefPtr<GeolocationPosition> position) { 
    m_position = position;
    sendUpdate(); 
}

void GeolocationControllerClientHl::sendUpdate() {
    if (m_controller && m_updating && m_position.get())
        m_controller->positionChanged(lastPosition());
}

void GeolocationControllerClientHl::setController(GeolocationController* controller) {
   m_controller = controller;
} 

void GeolocationControllerClientHl::timerCallback(Timer<GeolocationControllerClientHl>*) {
    m_timer.stop();
    sendUpdate();
}

} // namespace WebCore
#endif
