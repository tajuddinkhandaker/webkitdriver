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

#if ENABLE(SVG)

#include "JSSVGGElement.h"

#include "CSSMutableStyleDeclaration.h"
#include "CSSStyleDeclaration.h"
#include "CSSValue.h"
#include "JSCSSStyleDeclaration.h"
#include "JSCSSValue.h"
#include "JSSVGAnimatedBoolean.h"
#include "JSSVGAnimatedString.h"
#include "JSSVGAnimatedTransformList.h"
#include "JSSVGElement.h"
#include "JSSVGMatrix.h"
#include "JSSVGRect.h"
#include "JSSVGStringList.h"
#include "KURL.h"
#include "SVGElement.h"
#include "SVGGElement.h"
#include "SVGStringList.h"
#include <runtime/Error.h>
#include <runtime/JSString.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGGElement);

/* Hash table */

static const HashTableValue JSSVGGElementTableValues[13] =
{
    { "requiredFeatures", DontDelete|ReadOnly, (intptr_t)jsSVGGElementRequiredFeatures, (intptr_t)0 },
    { "requiredExtensions", DontDelete|ReadOnly, (intptr_t)jsSVGGElementRequiredExtensions, (intptr_t)0 },
    { "systemLanguage", DontDelete|ReadOnly, (intptr_t)jsSVGGElementSystemLanguage, (intptr_t)0 },
    { "xmllang", DontDelete, (intptr_t)jsSVGGElementXmllang, (intptr_t)setJSSVGGElementXmllang },
    { "xmlspace", DontDelete, (intptr_t)jsSVGGElementXmlspace, (intptr_t)setJSSVGGElementXmlspace },
    { "externalResourcesRequired", DontDelete|ReadOnly, (intptr_t)jsSVGGElementExternalResourcesRequired, (intptr_t)0 },
    { "className", DontDelete|ReadOnly, (intptr_t)jsSVGGElementClassName, (intptr_t)0 },
    { "style", DontDelete|ReadOnly, (intptr_t)jsSVGGElementStyle, (intptr_t)0 },
    { "transform", DontDelete|ReadOnly, (intptr_t)jsSVGGElementTransform, (intptr_t)0 },
    { "nearestViewportElement", DontDelete|ReadOnly, (intptr_t)jsSVGGElementNearestViewportElement, (intptr_t)0 },
    { "farthestViewportElement", DontDelete|ReadOnly, (intptr_t)jsSVGGElementFarthestViewportElement, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsSVGGElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGGElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 127, JSSVGGElementTableValues, 0 };
#else
    { 34, 31, JSSVGGElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSSVGGElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGGElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGGElementConstructorTableValues, 0 };
#else
    { 1, 0, JSSVGGElementConstructorTableValues, 0 };
#endif

class JSSVGGElementConstructor : public DOMConstructorObject {
public:
    JSSVGGElementConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSSVGGElementConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSSVGGElementPrototype::self(exec, globalObject), None);
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

const ClassInfo JSSVGGElementConstructor::s_info = { "SVGGElementConstructor", 0, &JSSVGGElementConstructorTable, 0 };

bool JSSVGGElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGGElementConstructor, DOMObject>(exec, &JSSVGGElementConstructorTable, this, propertyName, slot);
}

bool JSSVGGElementConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGGElementConstructor, DOMObject>(exec, &JSSVGGElementConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSSVGGElementPrototypeTableValues[7] =
{
    { "hasExtension", DontDelete|Function, (intptr_t)jsSVGGElementPrototypeFunctionHasExtension, (intptr_t)1 },
    { "getPresentationAttribute", DontDelete|Function, (intptr_t)jsSVGGElementPrototypeFunctionGetPresentationAttribute, (intptr_t)1 },
    { "getBBox", DontDelete|Function, (intptr_t)jsSVGGElementPrototypeFunctionGetBBox, (intptr_t)0 },
    { "getCTM", DontDelete|Function, (intptr_t)jsSVGGElementPrototypeFunctionGetCTM, (intptr_t)0 },
    { "getScreenCTM", DontDelete|Function, (intptr_t)jsSVGGElementPrototypeFunctionGetScreenCTM, (intptr_t)0 },
    { "getTransformToElement", DontDelete|Function, (intptr_t)jsSVGGElementPrototypeFunctionGetTransformToElement, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGGElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 2047, JSSVGGElementPrototypeTableValues, 0 };
#else
    { 17, 15, JSSVGGElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGGElementPrototype::s_info = { "SVGGElementPrototype", 0, &JSSVGGElementPrototypeTable, 0 };

JSObject* JSSVGGElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGGElement>(exec, globalObject);
}

bool JSSVGGElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSSVGGElementPrototypeTable, this, propertyName, slot);
}

bool JSSVGGElementPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticFunctionDescriptor<JSObject>(exec, &JSSVGGElementPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSSVGGElement::s_info = { "SVGGElement", &JSSVGElement::s_info, &JSSVGGElementTable, 0 };

JSSVGGElement::JSSVGGElement(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<SVGGElement> impl)
    : JSSVGElement(structure, globalObject, impl)
{
}

JSObject* JSSVGGElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGGElementPrototype(JSSVGGElementPrototype::createStructure(JSSVGElementPrototype::self(exec, globalObject)));
}

bool JSSVGGElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGGElement, Base>(exec, &JSSVGGElementTable, this, propertyName, slot);
}

bool JSSVGGElement::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGGElement, Base>(exec, &JSSVGGElementTable, this, propertyName, descriptor);
}

JSValue jsSVGGElementRequiredFeatures(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGGElement* castedThis = static_cast<JSSVGGElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGGElement* imp = static_cast<SVGGElement*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->requiredFeatures()), imp);
    return result;
}

JSValue jsSVGGElementRequiredExtensions(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGGElement* castedThis = static_cast<JSSVGGElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGGElement* imp = static_cast<SVGGElement*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->requiredExtensions()), imp);
    return result;
}

JSValue jsSVGGElementSystemLanguage(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGGElement* castedThis = static_cast<JSSVGGElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGGElement* imp = static_cast<SVGGElement*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->systemLanguage()), imp);
    return result;
}

JSValue jsSVGGElementXmllang(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGGElement* castedThis = static_cast<JSSVGGElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGGElement* imp = static_cast<SVGGElement*>(castedThis->impl());
    JSValue result = jsString(exec, imp->xmllang());
    return result;
}

JSValue jsSVGGElementXmlspace(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGGElement* castedThis = static_cast<JSSVGGElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGGElement* imp = static_cast<SVGGElement*>(castedThis->impl());
    JSValue result = jsString(exec, imp->xmlspace());
    return result;
}

JSValue jsSVGGElementExternalResourcesRequired(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGGElement* castedThis = static_cast<JSSVGGElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGGElement* imp = static_cast<SVGGElement*>(castedThis->impl());
    RefPtr<SVGAnimatedBoolean> obj = imp->externalResourcesRequiredAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGGElementClassName(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGGElement* castedThis = static_cast<JSSVGGElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGGElement* imp = static_cast<SVGGElement*>(castedThis->impl());
    RefPtr<SVGAnimatedString> obj = imp->classNameAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGGElementStyle(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGGElement* castedThis = static_cast<JSSVGGElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGGElement* imp = static_cast<SVGGElement*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->style()));
    return result;
}

JSValue jsSVGGElementTransform(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGGElement* castedThis = static_cast<JSSVGGElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGGElement* imp = static_cast<SVGGElement*>(castedThis->impl());
    RefPtr<SVGAnimatedTransformList> obj = imp->transformAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGGElementNearestViewportElement(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGGElement* castedThis = static_cast<JSSVGGElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGGElement* imp = static_cast<SVGGElement*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->nearestViewportElement()));
    return result;
}

JSValue jsSVGGElementFarthestViewportElement(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGGElement* castedThis = static_cast<JSSVGGElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGGElement* imp = static_cast<SVGGElement*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->farthestViewportElement()));
    return result;
}

JSValue jsSVGGElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGGElement* domObject = static_cast<JSSVGGElement*>(asObject(slot.slotBase()));
    return JSSVGGElement::getConstructor(exec, domObject->globalObject());
}
void JSSVGGElement::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSSVGGElement, Base>(exec, propertyName, value, &JSSVGGElementTable, this, slot);
}

void setJSSVGGElementXmllang(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGGElement* castedThisObj = static_cast<JSSVGGElement*>(thisObject);
    SVGGElement* imp = static_cast<SVGGElement*>(castedThisObj->impl());
    imp->setXmllang(value.toString(exec));
}

void setJSSVGGElementXmlspace(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGGElement* castedThisObj = static_cast<JSSVGGElement*>(thisObject);
    SVGGElement* imp = static_cast<SVGGElement*>(castedThisObj->impl());
    imp->setXmlspace(value.toString(exec));
}

JSValue JSSVGGElement::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSSVGGElementConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSValue JSC_HOST_CALL jsSVGGElementPrototypeFunctionHasExtension(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGGElement::s_info))
        return throwError(exec, TypeError);
    JSSVGGElement* castedThisObj = static_cast<JSSVGGElement*>(asObject(thisValue));
    SVGGElement* imp = static_cast<SVGGElement*>(castedThisObj->impl());
    const UString& extension = args.at(0).toString(exec);


    JSC::JSValue result = jsBoolean(imp->hasExtension(extension));
    return result;
}

JSValue JSC_HOST_CALL jsSVGGElementPrototypeFunctionGetPresentationAttribute(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGGElement::s_info))
        return throwError(exec, TypeError);
    JSSVGGElement* castedThisObj = static_cast<JSSVGGElement*>(asObject(thisValue));
    SVGGElement* imp = static_cast<SVGGElement*>(castedThisObj->impl());
    const UString& name = args.at(0).toString(exec);


    JSC::JSValue result = toJS(exec, castedThisObj->globalObject(), WTF::getPtr(imp->getPresentationAttribute(name)));
    return result;
}

JSValue JSC_HOST_CALL jsSVGGElementPrototypeFunctionGetBBox(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGGElement::s_info))
        return throwError(exec, TypeError);
    JSSVGGElement* castedThisObj = static_cast<JSSVGGElement*>(asObject(thisValue));
    SVGGElement* imp = static_cast<SVGGElement*>(castedThisObj->impl());


    JSC::JSValue result = toJS(exec, castedThisObj->globalObject(), JSSVGStaticPODTypeWrapper<FloatRect>::create(imp->getBBox()).get(), 0 /* no context on purpose */);
    return result;
}

JSValue JSC_HOST_CALL jsSVGGElementPrototypeFunctionGetCTM(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGGElement::s_info))
        return throwError(exec, TypeError);
    JSSVGGElement* castedThisObj = static_cast<JSSVGGElement*>(asObject(thisValue));
    SVGGElement* imp = static_cast<SVGGElement*>(castedThisObj->impl());


    JSC::JSValue result = toJS(exec, castedThisObj->globalObject(), JSSVGStaticPODTypeWrapper<AffineTransform>::create(imp->getCTM()).get(), 0 /* no context on purpose */);
    return result;
}

JSValue JSC_HOST_CALL jsSVGGElementPrototypeFunctionGetScreenCTM(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGGElement::s_info))
        return throwError(exec, TypeError);
    JSSVGGElement* castedThisObj = static_cast<JSSVGGElement*>(asObject(thisValue));
    SVGGElement* imp = static_cast<SVGGElement*>(castedThisObj->impl());


    JSC::JSValue result = toJS(exec, castedThisObj->globalObject(), JSSVGStaticPODTypeWrapper<AffineTransform>::create(imp->getScreenCTM()).get(), 0 /* no context on purpose */);
    return result;
}

JSValue JSC_HOST_CALL jsSVGGElementPrototypeFunctionGetTransformToElement(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGGElement::s_info))
        return throwError(exec, TypeError);
    JSSVGGElement* castedThisObj = static_cast<JSSVGGElement*>(asObject(thisValue));
    SVGGElement* imp = static_cast<SVGGElement*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    SVGElement* element = toSVGElement(args.at(0));


    JSC::JSValue result = toJS(exec, castedThisObj->globalObject(), JSSVGStaticPODTypeWrapper<AffineTransform>::create(imp->getTransformToElement(element, ec)).get(), 0 /* no context on purpose */);
    setDOMException(exec, ec);
    return result;
}


}

#endif // ENABLE(SVG)
