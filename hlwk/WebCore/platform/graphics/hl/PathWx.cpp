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
#include "Path.h"

#include "AffineTransform.h"
#include "FloatPoint.h"
#include "FloatRect.h"
#include "NotImplemented.h"
#include "StrokeStyleApplier.h" 
#include "GraphicsPathHL.h"

#include <stdio.h>

namespace WebCore {

int getWxWindRuleForWindRule(WindRule rule)
{
    return 0;
}

Path::Path() 
{ 
    m_path = new hlGraphicsPath();
}

Path::~Path()
{
    clear();
}

Path::Path(const Path& path)
{ 
    m_path = new hlGraphicsPath();
}

bool Path::contains(const FloatPoint& point, const WindRule rule) const
{
   return false; 
}

void Path::translate(const FloatSize&)
{ 
    notImplemented();
}

FloatRect Path::boundingRect() const 
{ 
    notImplemented();
    return FloatRect();
}

FloatRect Path::strokeBoundingRect(StrokeStyleApplier* applier)
{
    notImplemented();
    return FloatRect();
}

Path& Path::operator=(const Path&)
{ 
    notImplemented(); 
    return*this; 
}

void Path::clear() 
{ 
    if (m_path)
        delete m_path;
}

void Path::moveTo(const FloatPoint& point) 
{
    notImplemented(); 
}

void Path::addLineTo(const FloatPoint& point) 
{
    notImplemented(); 
}

void Path::addQuadCurveTo(const FloatPoint& control, const FloatPoint& end) 
{
    notImplemented(); 
}

void Path::addBezierCurveTo(const FloatPoint& control1, const FloatPoint& control2, const FloatPoint& end) 
{
    notImplemented(); 
}

void Path::addArcTo(const FloatPoint& point1, const FloatPoint& point2, float radius) 
{
    notImplemented(); 
}

void Path::closeSubpath() 
{
    notImplemented(); 
}

void Path::addArc(const FloatPoint& point, float radius, float startAngle, float endAngle, bool clockwise) 
{
    notImplemented(); 
}

void Path::addRect(const FloatRect& rect) 
{
    notImplemented(); 
}

void Path::addEllipse(const FloatRect& rect) 
{
    notImplemented(); 
}

void Path::transform(const AffineTransform& transform) 
{
    notImplemented(); 
}

void Path::apply(void* info, PathApplierFunction function) const 
{
    notImplemented(); 
}

bool Path::isEmpty() const
{
    return true;
}

bool Path::hasCurrentPoint() const
{
    return !isEmpty();
}

}
