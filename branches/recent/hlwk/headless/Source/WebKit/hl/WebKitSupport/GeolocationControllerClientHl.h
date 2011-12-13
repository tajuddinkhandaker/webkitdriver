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

#ifndef GeolocationControllerClientHl_h
#define GeolocationControllerClientHl_h

#include "config.h"
#include "GeolocationClient.h"
#include "Timer.h"
#include <wtf/PassRefPtr.h>
#include <wtf/RefCounted.h>
#include <wtf/RefPtr.h>


namespace WebCore {

class GeolocationPosition;
class GeolocationController;

class GeolocationControllerClientHl : public GeolocationClient {
#if ENABLE(CLIENT_BASED_GEOLOCATION)
public:
    GeolocationControllerClientHl();
    // set WebCore::GeolocationController for callbacks handling 
    void setController (GeolocationController*);

    // Not supported yet
    virtual void geolocationDestroyed() {}

    // Start updating Geolocation, upon completition callback is called
    virtual void startUpdating();
    virtual void stopUpdating();

    // Last known Geoposition
    virtual GeolocationPosition* lastPosition();

    // WebKit support - set Geoposition (for testng purposes)
    void setPosition(PassRefPtr<GeolocationPosition> position);

    // Timer callback which is called when Geoposition is found
    // We neeed this function for emulation asynchronous work
    void timerCallback(Timer<GeolocationControllerClientHl>*);
    // are we finished with updates
    bool isBusy() { return m_updating; }

protected:
    virtual ~GeolocationControllerClientHl();

private:
    PassRefPtr<GeolocationPosition> m_position;
    bool m_updating;
    Timer<GeolocationControllerClientHl> m_timer;
    GeolocationController* m_controller;

    void sendUpdate();
#endif
};

} // namespace WebCore

#endif // GeolocationControllerClientHl_h
