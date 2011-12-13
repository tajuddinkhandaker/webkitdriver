/*
 * Copyright (C) 2008 Apple Inc. All Rights Reserved.
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
#include "ScrollbarThemeHl.h"

#include "HostWindow.h"
#include "NotImplemented.h"
#include "PlatformMouseEvent.h"
#include "Scrollbar.h"
#include "ScrollbarThemeComposite.h"
#include "ScrollView.h"

const int cMacButtonOverlap = 4;

namespace WebCore {

ScrollbarTheme* ScrollbarTheme::nativeTheme()
{
    static ScrollbarThemeWx theme;
    return &theme;
}

ScrollbarThemeWx::~ScrollbarThemeWx()
{
}

int ScrollbarThemeWx::scrollbarThickness(ScrollbarControlSize size)
{
    return 20;
}

bool ScrollbarThemeWx::hasThumb(Scrollbar* scrollbar)
{
    // This method is just called as a paint-time optimization to see if
    // painting the thumb can be skipped.  We don't have to be exact here.
    return false;
}

int ScrollbarThemeWx::minimumThumbLength(Scrollbar* scrollbar)
{
    return 20;
}

IntSize ScrollbarThemeWx::buttonSize(Scrollbar*) 
{
    return IntSize(16,16);
}

void ScrollbarThemeWx::splitTrack(Scrollbar* scrollbar, const IntRect& unconstrainedTrackRect, IntRect& beforeThumbRect, IntRect& thumbRect, IntRect& afterThumbRect)
{
}

IntRect ScrollbarThemeWx::backButtonRect(Scrollbar* scrollbar, ScrollbarPart part, bool)
{
    return IntRect();
}

IntRect ScrollbarThemeWx::forwardButtonRect(Scrollbar* scrollbar, ScrollbarPart part, bool)
{
     return IntRect();
}

IntRect ScrollbarThemeWx::trackRect(Scrollbar* scrollbar, bool)
{
     return IntRect();
}

void ScrollbarThemeWx::paintScrollCorner(ScrollView* view, GraphicsContext* context, const IntRect& cornerRect)
{
}

bool ScrollbarThemeWx::paint(Scrollbar* scrollbar, GraphicsContext* context, const IntRect& rect)
{
    return true;
}

}

