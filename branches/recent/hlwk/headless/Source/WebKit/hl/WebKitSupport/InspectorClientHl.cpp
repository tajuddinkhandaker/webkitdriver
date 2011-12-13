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
#include "InspectorClientHl.h"

#include "NotImplemented.h"
#include "Page.h"
#include "PlatformString.h"

namespace WebCore {

InspectorClientHl::InspectorClientHl()
{
    notImplemented();
}

InspectorClientHl::~InspectorClientHl()
{
    notImplemented();
}

void InspectorClientHl::inspectorDestroyed()
{
    notImplemented();
}

void InspectorClientHl::openInspectorFrontend(WebCore::InspectorController*)
{
    notImplemented();
}

void InspectorClientHl::closeInspectorFrontend()
{
    notImplemented();
}

void InspectorClientHl::bringFrontendToFront()
{
    notImplemented();
}

void InspectorClientHl::highlight()
{
    notImplemented();
}

Page* InspectorClientHl::createPage()
{
    notImplemented();
    return 0;
}

String InspectorClientHl::localizedStringsURL()
{
    notImplemented();
    return String();
}

String InspectorClientHl::hiddenPanels()
{
    notImplemented();
    return String();
}

void InspectorClientHl::showWindow()
{
    notImplemented();
}
    
void InspectorClientHl::closeWindow()
{
    notImplemented();
}

void InspectorClientHl::attachWindow()
{
    notImplemented();
}

void InspectorClientHl::detachWindow()
{
    notImplemented();
}

void InspectorClientHl::setAttachedWindowHeight(unsigned height)
{
    notImplemented();
}

void InspectorClientHl::highlight(Node*)
{
    notImplemented();
}

void InspectorClientHl::hideHighlight()
{
    notImplemented();
}

void InspectorClientHl::inspectedURLChanged(const String& newURL)
{
    notImplemented();
}

void InspectorClientHl::populateSetting(const String& key, String* setting)
{
    notImplemented();
}

void InspectorClientHl::storeSetting(const String& key, const String& setting)
{
    notImplemented();
}

void InspectorClientHl::inspectorWindowObjectCleared()
{
    notImplemented();
}

bool InspectorClientHl::sendMessageToFrontend(const String&)
{
    notImplemented();
    return false;
}


};
