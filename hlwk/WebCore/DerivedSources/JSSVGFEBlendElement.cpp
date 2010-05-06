/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"

#if ENABLE(SVG) && ENABLE(FILTERS)

#include "JSSVGFEBlendElement.h"

#include "CSSMutableStyleDeclaration.h"
#include "CSSStyleDeclaration.h"
#include "CSSValue.h"
#include "JSCSSStyleDeclaration.h"
#include "JSCSSValue.h"
#include "JSSVGAnimatedEnumeration.h"
#include "JSSVGAnimatedLength.h"
#include "JSSVGAnimatedString.h"
#include "SVGFEBlendElement.h"
#include <runtime/Error.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGFEBlendElement);

/* Hash table */

static const HashTableValue JSSVGFEBlendElementTableValues[12] =
{
    { "in1", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementIn1, (intptr_t)0 },
    { "in2", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementIn2, (intptr_t)0 },
    { "mode", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementMode, (intptr_t)0 },
    { "x", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementX, (intptr_t)0 },
    { "y", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementY, (intptr_t)0 },
    { "width", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementWidth, (intptr_t)0 },
    { "height", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementHeight, (intptr_t)0 },
    { "result", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementResult, (intptr_t)0 },
    { "className", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementClassName, (intptr_t)0 },
    { "style", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementStyle, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsSVGFEBlendElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGFEBlendElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 255, JSSVGFEBlendElementTableValues, 0 };
#else
    { 35, 31, JSSVGFEBlendElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSSVGFEBlendElementConstructorTableValues[7] =
{
    { "SVG_FEBLEND_MODE_UNKNOWN", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementSVG_FEBLEND_MODE_UNKNOWN, (intptr_t)0 },
    { "SVG_FEBLEND_MODE_NORMAL", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementSVG_FEBLEND_MODE_NORMAL, (intptr_t)0 },
    { "SVG_FEBLEND_MODE_MULTIPLY", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementSVG_FEBLEND_MODE_MULTIPLY, (intptr_t)0 },
    { "SVG_FEBLEND_MODE_SCREEN", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementSVG_FEBLEND_MODE_SCREEN, (intptr_t)0 },
    { "SVG_FEBLEND_MODE_DARKEN", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementSVG_FEBLEND_MODE_DARKEN, (intptr_t)0 },
    { "SVG_FEBLEND_MODE_LIGHTEN", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementSVG_FEBLEND_MODE_LIGHTEN, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGFEBlendElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSSVGFEBlendElementConstructorTableValues, 0 };
#else
    { 16, 15, JSSVGFEBlendElementConstructorTableValues, 0 };
#endif

class JSSVGFEBlendElementConstructor : public DOMConstructorObject {
public:
    JSSVGFEBlendElementConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSSVGFEBlendElementConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSSVGFEBlendElementPrototype::self(exec, globalObject), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual bool getOwnPropertyDescriptor(ExecState*, const Identifier&, PropertyDescriptor&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, StructureFlags), AnonymousSlotCount); 
    }
    
protected:
    static const unsigned StructureFlags = OverridesGetOwnPropertySlot | ImplementsHasInstance | DOMConstructorObject::StructureFlags;
};

const ClassInfo JSSVGFEBlendElementConstructor::s_info = { "SVGFEBlendElementConstructor", 0, &JSSVGFEBlendElementConstructorTable, 0 };

bool JSSVGFEBlendElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGFEBlendElementConstructor, DOMObject>(exec, &JSSVGFEBlendElementConstructorTable, this, propertyName, slot);
}

bool JSSVGFEBlendElementConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGFEBlendElementConstructor, DOMObject>(exec, &JSSVGFEBlendElementConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSSVGFEBlendElementPrototypeTableValues[8] =
{
    { "SVG_FEBLEND_MODE_UNKNOWN", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementSVG_FEBLEND_MODE_UNKNOWN, (intptr_t)0 },
    { "SVG_FEBLEND_MODE_NORMAL", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementSVG_FEBLEND_MODE_NORMAL, (intptr_t)0 },
    { "SVG_FEBLEND_MODE_MULTIPLY", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementSVG_FEBLEND_MODE_MULTIPLY, (intptr_t)0 },
    { "SVG_FEBLEND_MODE_SCREEN", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementSVG_FEBLEND_MODE_SCREEN, (intptr_t)0 },
    { "SVG_FEBLEND_MODE_DARKEN", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementSVG_FEBLEND_MODE_DARKEN, (intptr_t)0 },
    { "SVG_FEBLEND_MODE_LIGHTEN", DontDelete|ReadOnly, (intptr_t)jsSVGFEBlendElementSVG_FEBLEND_MODE_LIGHTEN, (intptr_t)0 },
    { "getPresentationAttribute", DontDelete|Function, (intptr_t)jsSVGFEBlendElementPrototypeFunctionGetPresentationAttribute, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGFEBlendElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSSVGFEBlendElementPrototypeTableValues, 0 };
#else
    { 16, 15, JSSVGFEBlendElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGFEBlendElementPrototype::s_info = { "SVGFEBlendElementPrototype", 0, &JSSVGFEBlendElementPrototypeTable, 0 };

JSObject* JSSVGFEBlendElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGFEBlendElement>(exec, globalObject);
}

bool JSSVGFEBlendElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticPropertySlot<JSSVGFEBlendElementPrototype, JSObject>(exec, &JSSVGFEBlendElementPrototypeTable, this, propertyName, slot);
}

bool JSSVGFEBlendElementPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticPropertyDescriptor<JSSVGFEBlendElementPrototype, JSObject>(exec, &JSSVGFEBlendElementPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSSVGFEBlendElement::s_info = { "SVGFEBlendElement", &JSSVGElement::s_info, &JSSVGFEBlendElementTable, 0 };

JSSVGFEBlendElement::JSSVGFEBlendElement(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<SVGFEBlendElement> impl)
    : JSSVGElement(structure, globalObject, impl)
{
}

JSObject* JSSVGFEBlendElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGFEBlendElementPrototype(JSSVGFEBlendElementPrototype::createStructure(JSSVGElementPrototype::self(exec, globalObject)));
}

bool JSSVGFEBlendElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGFEBlendElement, Base>(exec, &JSSVGFEBlendElementTable, this, propertyName, slot);
}

bool JSSVGFEBlendElement::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGFEBlendElement, Base>(exec, &JSSVGFEBlendElementTable, this, propertyName, descriptor);
}

JSValue jsSVGFEBlendElementIn1(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGFEBlendElement* castedThis = static_cast<JSSVGFEBlendElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGFEBlendElement* imp = static_cast<SVGFEBlendElement*>(castedThis->impl());
    RefPtr<SVGAnimatedString> obj = imp->in1Animated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFEBlendElementIn2(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGFEBlendElement* castedThis = static_cast<JSSVGFEBlendElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGFEBlendElement* imp = static_cast<SVGFEBlendElement*>(castedThis->impl());
    RefPtr<SVGAnimatedString> obj = imp->in2Animated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFEBlendElementMode(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGFEBlendElement* castedThis = static_cast<JSSVGFEBlendElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGFEBlendElement* imp = static_cast<SVGFEBlendElement*>(castedThis->impl());
    RefPtr<SVGAnimatedEnumeration> obj = imp->modeAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFEBlendElementX(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGFEBlendElement* castedThis = static_cast<JSSVGFEBlendElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGFEBlendElement* imp = static_cast<SVGFEBlendElement*>(castedThis->impl());
    RefPtr<SVGAnimatedLength> obj = imp->xAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFEBlendElementY(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGFEBlendElement* castedThis = static_cast<JSSVGFEBlendElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGFEBlendElement* imp = static_cast<SVGFEBlendElement*>(castedThis->impl());
    RefPtr<SVGAnimatedLength> obj = imp->yAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFEBlendElementWidth(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGFEBlendElement* castedThis = static_cast<JSSVGFEBlendElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGFEBlendElement* imp = static_cast<SVGFEBlendElement*>(castedThis->impl());
    RefPtr<SVGAnimatedLength> obj = imp->widthAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFEBlendElementHeight(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGFEBlendElement* castedThis = static_cast<JSSVGFEBlendElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGFEBlendElement* imp = static_cast<SVGFEBlendElement*>(castedThis->impl());
    RefPtr<SVGAnimatedLength> obj = imp->heightAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFEBlendElementResult(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGFEBlendElement* castedThis = static_cast<JSSVGFEBlendElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGFEBlendElement* imp = static_cast<SVGFEBlendElement*>(castedThis->impl());
    RefPtr<SVGAnimatedString> obj = imp->resultAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFEBlendElementClassName(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGFEBlendElement* castedThis = static_cast<JSSVGFEBlendElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGFEBlendElement* imp = static_cast<SVGFEBlendElement*>(castedThis->impl());
    RefPtr<SVGAnimatedString> obj = imp->classNameAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFEBlendElementStyle(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGFEBlendElement* castedThis = static_cast<JSSVGFEBlendElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGFEBlendElement* imp = static_cast<SVGFEBlendElement*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->style()));
    return result;
}

JSValue jsSVGFEBlendElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGFEBlendElement* domObject = static_cast<JSSVGFEBlendElement*>(asObject(slot.slotBase()));
    return JSSVGFEBlendElement::getConstructor(exec, domObject->globalObject());
}
JSValue JSSVGFEBlendElement::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSSVGFEBlendElementConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSValue JSC_HOST_CALL jsSVGFEBlendElementPrototypeFunctionGetPresentationAttribute(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGFEBlendElement::s_info))
        return throwError(exec, TypeError);
    JSSVGFEBlendElement* castedThisObj = static_cast<JSSVGFEBlendElement*>(asObject(thisValue));
    SVGFEBlendElement* imp = static_cast<SVGFEBlendElement*>(castedThisObj->impl());
    const UString& name = args.at(0).toString(exec);


    JSC::JSValue result = toJS(exec, castedThisObj->globalObject(), WTF::getPtr(imp->getPresentationAttribute(name)));
    return result;
}

// Constant getters

JSValue jsSVGFEBlendElementSVG_FEBLEND_MODE_UNKNOWN(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(0));
}

JSValue jsSVGFEBlendElementSVG_FEBLEND_MODE_NORMAL(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(1));
}

JSValue jsSVGFEBlendElementSVG_FEBLEND_MODE_MULTIPLY(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(2));
}

JSValue jsSVGFEBlendElementSVG_FEBLEND_MODE_SCREEN(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(3));
}

JSValue jsSVGFEBlendElementSVG_FEBLEND_MODE_DARKEN(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(4));
}

JSValue jsSVGFEBlendElementSVG_FEBLEND_MODE_LIGHTEN(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(5));
}


}

#endif // ENABLE(SVG) && ENABLE(FILTERS)
