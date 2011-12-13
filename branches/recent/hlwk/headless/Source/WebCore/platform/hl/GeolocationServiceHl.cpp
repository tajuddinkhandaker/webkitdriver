/*
 * Copyright (C) 2009 Apple Inc. All Rights Reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"
#include "GeolocationServiceHl.h"

#include "Logging.h"
#include "Geolocation.h"
#include "Geoposition.h"
#include "PositionError.h"
#include "PositionOptions.h"

namespace WebCore {

GeolocationServiceHl::GeolocationServiceSet* GeolocationServiceHl::s_instances = 0;
RefPtr<Geoposition>* GeolocationServiceHl::s_lastPosition;
RefPtr<PositionError>* GeolocationServiceHl::s_lastError;

#if !ENABLE(CLIENT_BASED_GEOLOCATION)
GeolocationService::FactoryFunction* GeolocationService::s_factoryFunction = &GeolocationServiceHl::create;
#endif //CLIENT_BASED_GEOLOCATION

PassOwnPtr<GeolocationService> GeolocationServiceHl::create(GeolocationServiceClient* client)
{
    initStatics();
    return adoptPtr(new GeolocationServiceHl(client));
}

GeolocationServiceHl::GeolocationServiceHl(GeolocationServiceClient* client)
    : GeolocationService(client)
    , m_timer(this, &GeolocationServiceHl::timerFired)
    , m_isActive(false)
{
    s_instances->add(this);
}

GeolocationServiceHl::~GeolocationServiceHl()
{
    GeolocationServiceSet::iterator iter = s_instances->find(this);
    ASSERT(iter != s_instances->end());
    s_instances->remove(iter);
    cleanUpStatics();
}

void GeolocationServiceHl::setPosition(PassRefPtr<Geoposition> position)
{
    initStatics();
//    GeolocationService::useMock();
    *s_lastPosition = position;
    *s_lastError = 0;
    makeGeolocationCallbackFromAllInstances();
}

void GeolocationServiceHl::setError(PassRefPtr<PositionError> error)
{
    initStatics();
//    GeolocationService::useMock();
    *s_lastError = error;
    *s_lastPosition = 0;
    makeGeolocationCallbackFromAllInstances();
}

bool GeolocationServiceHl::startUpdating(PositionOptions*)
{
    m_isActive = true;
    m_timer.startOneShot(0);
    return true;
}

void GeolocationServiceHl::stopUpdating()
{
    m_isActive = false;
}

void GeolocationServiceHl::timerFired(Timer<GeolocationServiceHl>* timer)
{
    ASSERT_UNUSED(timer, timer == &m_timer);
    makeGeolocationCallback();
}

void GeolocationServiceHl::makeGeolocationCallbackFromAllInstances()
{
    GeolocationServiceSet::const_iterator end = s_instances->end();
    for (GeolocationServiceSet::const_iterator iter = s_instances->begin(); iter != end; ++iter)
        (*iter)->makeGeolocationCallback();
}

void GeolocationServiceHl::makeGeolocationCallback()
{
    if (!m_isActive)
        return;

    if (*s_lastPosition)
        positionChanged();
    else if (*s_lastError)
        errorOccurred();
}

void GeolocationServiceHl::initStatics()
{
    if (s_instances == 0) { 
        s_instances = new GeolocationServiceSet;
        s_lastPosition = new RefPtr<Geoposition>;
        s_lastError = new RefPtr<PositionError>;
    }
}

void GeolocationServiceHl::cleanUpStatics()
{
    if (s_instances->size() == 0) {
        delete s_instances;
        s_instances = 0;
        delete s_lastPosition;
        delete s_lastError;
    }
}

} // namespace WebCore

