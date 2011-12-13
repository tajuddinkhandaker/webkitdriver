/*
 *  Copyright (C) 2007 Kevin Ollivier <kevino@theolliviers.com>
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
#include "ClipboardHl.h"

#include "FileList.h"
#include "HashTable.h"
#include "IntPoint.h"
#include "NotImplemented.h"
#include "Pasteboard.h"
#include "PlatformString.h"
#include <wtf/text/StringHash.h>


namespace WebCore {
 
ClipboardHl::ClipboardHl(ClipboardAccessPolicy policy, ClipboardType type) 
    : Clipboard(policy, type)
{
}

void ClipboardHl::clearData(const String& type)
{
    notImplemented();
}

void ClipboardHl::clearAllData() 
{
    Pasteboard::generalPasteboard()->clear();
}

String ClipboardHl::getData(const String& type, bool& success) const 
{
    notImplemented();
    success = false;
    return ""; 
}

bool ClipboardHl::setData(const String& type, const String& data) 
{
    notImplemented();
    return false;
}

// extensions beyond IE's API
HashSet<String> ClipboardHl::types() const 
{
    notImplemented();
    HashSet<String> result;
    return result;
}

PassRefPtr<FileList> ClipboardHl::files() const
{
    notImplemented();
    return 0;
}

IntPoint ClipboardHl::dragLocation() const 
{ 
    notImplemented();
    return IntPoint(0,0);
}

CachedImage* ClipboardHl::dragImage() const 
{
    notImplemented();
    return 0; 
}

void ClipboardHl::setDragImage(CachedImage*, const IntPoint&) 
{
    notImplemented();
}

Node* ClipboardHl::dragImageElement() 
{
    notImplemented();
    return 0; 
}

void ClipboardHl::setDragImageElement(Node*, const IntPoint&)
{
    notImplemented();
}

DragImageRef ClipboardHl::createDragImage(IntPoint& dragLoc) const
{ 
    notImplemented();
    return 0;
}

void ClipboardHl::declareAndWriteDragImage(Element*, const KURL&, const String&, Frame*) 
{
    notImplemented();
}

void ClipboardHl::writeURL(const KURL& url, const String& string, Frame* frame) 
{
    Pasteboard::generalPasteboard()->writeURL(url, string, frame);
}

void ClipboardHl::writeRange(Range*, Frame*) 
{
    notImplemented();
}

bool ClipboardHl::hasData() 
{
    notImplemented();
    return false;
}

void ClipboardHl::writePlainText(const String& text)
{
    Pasteboard::generalPasteboard()->writePlainText(text);
}

}
