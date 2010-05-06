/*
 * Copyright (C) 2008 Apple Computer, Inc.  All rights reserved.
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

#include "ContextMenuItem.h"
#include "ContextMenu.h"
#include "NotImplemented.h"
#include "PlatformMenuDescription.h"

using namespace WebCore;

ContextMenuItem::ContextMenuItem(ContextMenu* subMenu)
{
	notImplemented();
}

ContextMenuItem::ContextMenuItem(ContextMenuItemType type, ContextMenuAction action,
                                 const String& title, ContextMenu* subMenu)
{
}

ContextMenuItem::~ContextMenuItem()
{
	notImplemented();
}

PlatformMenuItemDescription ContextMenuItem::releasePlatformDescription()
{
    return NULL;
}

ContextMenuItemType ContextMenuItem::type() const
{
    notImplemented();
    return ActionType;
}

void ContextMenuItem::setType(ContextMenuItemType type)
{
    notImplemented();
}

ContextMenuAction ContextMenuItem::action() const
{
    notImplemented();
    return ContextMenuItemTagNoAction;
}

void ContextMenuItem::setAction(ContextMenuAction action)
{
    notImplemented();
}

String ContextMenuItem::title() const
{
    notImplemented();
    return String();
}

void ContextMenuItem::setTitle(const String& title)
{
    notImplemented();
}

void ContextMenuItem::setSubMenu(ContextMenu* subMenu)
{
    notImplemented();
}

void ContextMenuItem::setChecked(bool shouldCheck)
{
    notImplemented();
}

void ContextMenuItem::setEnabled(bool shouldEnable)
{
    notImplemented();
}
