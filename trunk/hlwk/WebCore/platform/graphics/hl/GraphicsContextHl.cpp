/*
 * Copyright (C) 2007 Kevin Ollivier <kevino@theolliviers.com>
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
#include "GraphicsContext.h"

#include "AffineTransform.h"
#include "FloatRect.h"
#include "Font.h"
#include "IntRect.h"
#include "NotImplemented.h"
#include "Pen.h"
#include <wtf/MathExtras.h>

#include <math.h>
#include <stdio.h>

#if __WXMAC__
#include <Carbon/Carbon.h>
#elif __WXMSW__
#include <windows.h>
#endif

namespace WebCore {

int getHlCompositingOperation(CompositeOperator op, bool hasAlpha)
{
    notImplemented();
    return 0;
}

static int strokeStyleToHlPenStyle(int p)
{
    notImplemented();
    return 0;
}

class GraphicsContextPlatformPrivate {
public:
    GraphicsContextPlatformPrivate();
    ~GraphicsContextPlatformPrivate();
};

GraphicsContextPlatformPrivate::GraphicsContextPlatformPrivate()
{
}

GraphicsContextPlatformPrivate::~GraphicsContextPlatformPrivate()
{
}


GraphicsContext::GraphicsContext(PlatformGraphicsContext* context)
    : m_common(createGraphicsContextPrivate())
    , m_data(new GraphicsContextPlatformPrivate)
{    
}

GraphicsContext::~GraphicsContext()
{
    destroyGraphicsContextPrivate(m_common);
    delete m_data;
}

PlatformGraphicsContext* GraphicsContext::platformContext() const
{
    return NULL;
}

void GraphicsContext::savePlatformState()
{
	notImplemented();
}

void GraphicsContext::restorePlatformState()
{
	notImplemented();
}

// Draws a filled rectangle with a stroked border.
void GraphicsContext::drawRect(const IntRect& rect)
{
	notImplemented();
}

// This is only used to draw borders.
void GraphicsContext::drawLine(const IntPoint& point1, const IntPoint& point2)
{
	notImplemented();
}

// This method is only used to draw the little circles used in lists.
void GraphicsContext::drawEllipse(const IntRect& rect)
{
	notImplemented();
}

void GraphicsContext::strokeArc(const IntRect& rect, int startAngle, int angleSpan)
{
	notImplemented();
}

void GraphicsContext::drawConvexPolygon(size_t npoints, const FloatPoint* points, bool shouldAntialias)
{
	notImplemented();
}

void GraphicsContext::fillRect(const FloatRect& rect, const Color& color, ColorSpace colorSpace)
{
	notImplemented();
}

void GraphicsContext::fillRoundedRect(const IntRect& rect, const IntSize& topLeft, const IntSize& topRight, const IntSize& bottomLeft, const IntSize& bottomRight, const Color& color, ColorSpace colorSpace)
{
    notImplemented();
}

void GraphicsContext::drawFocusRing(const Vector<Path>& paths, int width, int offset, const Color& color)
{
    notImplemented();
}

void GraphicsContext::drawFocusRing(const Vector<IntRect>& rects, int width, int offset, const Color& color)
{
    notImplemented();
}

void GraphicsContext::clip(const FloatRect& r)
{
    notImplemented();
}

void GraphicsContext::clipOut(const Path&)
{
    notImplemented();
}

void GraphicsContext::clipOut(const IntRect&)
{
    notImplemented();
}

void GraphicsContext::clipOutEllipseInRect(const IntRect&)
{
    notImplemented();
}

void GraphicsContext::drawLineForText(const IntPoint& origin, int width, bool printing)
{
    notImplemented();
}


void GraphicsContext::drawLineForMisspellingOrBadGrammar(const IntPoint& origin, int width, bool grammar)
{
    notImplemented();
}

void GraphicsContext::clip(const Path&) 
{ 
    notImplemented();
}

void GraphicsContext::canvasClip(const Path& path)
{
    notImplemented();
}

void GraphicsContext::clipToImageBuffer(const FloatRect&, const ImageBuffer*)
{
    notImplemented();
}

AffineTransform GraphicsContext::getCTM() const
{ 
    notImplemented();
    return AffineTransform();
}

void GraphicsContext::translate(float tx, float ty) 
{ 
    notImplemented();
}

void GraphicsContext::rotate(float angle) 
{ 
    notImplemented();
}

void GraphicsContext::scale(const FloatSize& scale) 
{ 
    notImplemented();
}


FloatRect GraphicsContext::roundToDevicePixels(const FloatRect& frect)
{
    notImplemented();
    return frect; 
}

void GraphicsContext::setURLForRect(const KURL&, const IntRect&)
{
    notImplemented();
}

void GraphicsContext::setCompositeOperation(CompositeOperator op)
{
    notImplemented();
}

void GraphicsContext::beginPath()
{
    notImplemented();
}

void GraphicsContext::addPath(const Path& path)
{
    notImplemented();
}

void GraphicsContext::setPlatformStrokeColor(const Color& color, ColorSpace colorSpace)
{
    notImplemented();
}

void GraphicsContext::setPlatformStrokeThickness(float thickness)
{
    notImplemented();
}

void GraphicsContext::setPlatformFillColor(const Color& color, ColorSpace colorSpace)
{
    notImplemented();
}

void GraphicsContext::concatCTM(const AffineTransform& transform)
{
    notImplemented();
    return;
}

void GraphicsContext::setPlatformShouldAntialias(bool enable)
{
    notImplemented();
}

void GraphicsContext::setImageInterpolationQuality(InterpolationQuality)
{
}

InterpolationQuality GraphicsContext::imageInterpolationQuality() const
{
    return InterpolationDefault;
}

void GraphicsContext::fillPath()
{
}

void GraphicsContext::strokePath()
{
}

void GraphicsContext::drawPath()
{
    fillPath();
    strokePath();
}

void GraphicsContext::fillRect(const FloatRect& rect)
{
    if (paintingDisabled())
        return;
}

void GraphicsContext::setPlatformShadow(IntSize const&,int,Color const&, ColorSpace) 
{ 
    notImplemented(); 
}

void GraphicsContext::clearPlatformShadow() 
{ 
    notImplemented(); 
}

void GraphicsContext::beginTransparencyLayer(float) 
{ 
    notImplemented(); 
}

void GraphicsContext::endTransparencyLayer() 
{ 
    notImplemented(); 
}

void GraphicsContext::clearRect(const FloatRect&) 
{ 
    notImplemented(); 
}

void GraphicsContext::strokeRect(const FloatRect&, float)
{ 
    notImplemented(); 
}

void GraphicsContext::setLineCap(LineCap) 
{
    notImplemented(); 
}

void GraphicsContext::setLineJoin(LineJoin)
{
    notImplemented();
}

void GraphicsContext::setMiterLimit(float)
{
    notImplemented();
}

void GraphicsContext::setAlpha(float)
{
    notImplemented();
}

void GraphicsContext::addInnerRoundedRectClip(const IntRect& rect, int thickness)
{
    notImplemented();
}

void GraphicsContext::clipPath(WindRule)
{
    notImplemented();
}

void GraphicsContext::setLineDash(const DashArray&, float dashOffset)
{
    notImplemented();
}

#if OS(WINDOWS)
HDC GraphicsContext::getWindowsContext(const IntRect& dstRect, bool supportAlphaBlend, bool mayCreateBitmap)
{
        return 0;
}

void GraphicsContext::releaseWindowsContext(HDC hdc, const IntRect& dstRect, bool supportAlphaBlend, bool mayCreateBitmap)
{
}
#endif

}
