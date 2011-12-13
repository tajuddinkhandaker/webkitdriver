/*
 * This file is part of the popup menu implementation for <select> elements in WebCore.
 *
 * Copyright (C) 2008 Apple Computer, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#include "config.h"
#include "PopupMenu.h"

#include "Frame.h"
#include "FrameView.h"
#include "PopupMenuClient.h"
#include "PlatformString.h"
#include "NotImplemented.h"


namespace WebCore {

void PopupMenu::show(const IntRect& r, FrameView* v, int index)
{
	notImplemented();
}

void PopupMenu::hide()
{
    // we don't need to do anything here, the native control only exists during the time
    // show is called
}

void PopupMenu::updateFromElement()
{
	notImplemented();
}

}
