/*
 * Copyright (C) 2007 Apple Computer, Kevin Ollivier.  All rights reserved.
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
#include "Image.h"

#include "AffineTransform.h"
#include "BitmapImage.h"
#include "FloatConversion.h"
#include "FloatRect.h"
#include "GraphicsContext.h"
#include "ImageObserver.h"
#include "NotImplemented.h"

#include <math.h>
#include <stdio.h>

namespace WebCore {

// this is in GraphicsContextWx.cpp
int getWxCompositingOperation(CompositeOperator op, bool hasAlpha);

bool FrameData::clear(bool clearMetadata)
{
    return true;
}

// ================================================
// Image Class
// ================================================

PassRefPtr<Image> Image::loadPlatformResource(const char *name)
{
    // FIXME: We need to have some 'placeholder' graphics for things like missing
    // plugins or broken images.
    Vector<char> arr;
    RefPtr<Image> img = BitmapImage::create();
    RefPtr<SharedBuffer> buffer = SharedBuffer::create(arr.data(), arr.size());
    img->setData(buffer, true);
    return img.release();
}

void BitmapImage::initPlatformData()
{
    // FIXME: NYI
}

// Drawing Routines

void BitmapImage::draw(GraphicsContext* ctxt, const FloatRect& dst, const FloatRect& src, ColorSpace styleColorSpace, CompositeOperator op)
{
	notImplemented();
}

void Image::drawPattern(GraphicsContext* ctxt, const FloatRect& srcRect, const AffineTransform& patternTransform, const FloatPoint& phase, ColorSpace, CompositeOperator, const FloatRect& dstRect)
{
	notImplemented();
}

void BitmapImage::checkForSolidColor()
{
    m_checkedForSolidColor = true;
}

void BitmapImage::invalidatePlatformData()
{

}

}
