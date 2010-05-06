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

#include "JSSVGFEPointLightElement.h"

#include "JSSVGAnimatedNumber.h"
#include "SVGFEPointLightElement.h"
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGFEPointLightElement);

/* Hash table */

static const HashTableValue JSSVGFEPointLightElementTableValues[5] =
{
    { "x", DontDelete|ReadOnly, (intptr_t)jsSVGFEPointLightElementX, (intptr_t)0 },
    { "y", DontDelete|ReadOnly, (intptr_t)jsSVGFEPointLightElementY, (intptr_t)0 },
    { "z", DontDelete|ReadOnly, (intptr_t)jsSVGFEPointLightElementZ, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsSVGFEPointLightElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGFEPointLightElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSSVGFEPointLightElementTableValues, 0 };
#else
    { 9, 7, JSSVGFEPointLightElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSSVGFEPointLightElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGFEPointLightElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGFEPointLightElementConstructorTableValues, 0 };
#else
    { 1, 0, JSSVGFEPointLightElementConstructorTableValues, 0 };
#endif

class JSSVGFEPointLightElementConstructor : public DOMConstructorObject {
public:
    JSSVGFEPointLightElementConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSSVGFEPointLightElementConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSSVGFEPointLightElementPrototype::self(exec, globalObject), None);
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

const ClassInfo JSSVGFEPointLightElementConstructor::s_info = { "SVGFEPointLightElementConstructor", 0, &JSSVGFEPointLightElementConstructorTable, 0 };

bool JSSVGFEPointLightElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGFEPointLightElementConstructor, DOMObject>(exec, &JSSVGFEPointLightElementConstructorTable, this, propertyName, slot);
}

bool JSSVGFEPointLightElementConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGFEPointLightElementConstructor, DOMObject>(exec, &JSSVGFEPointLightElementConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSSVGFEPointLightElementPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGFEPointLightElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGFEPointLightElementPrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGFEPointLightElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGFEPointLightElementPrototype::s_info = { "SVGFEPointLightElementPrototype", 0, &JSSVGFEPointLightElementPrototypeTable, 0 };

JSObject* JSSVGFEPointLightElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGFEPointLightElement>(exec, globalObject);
}

const ClassInfo JSSVGFEPointLightElement::s_info = { "SVGFEPointLightElement", &JSSVGElement::s_info, &JSSVGFEPointLightElementTable, 0 };

JSSVGFEPointLightElement::JSSVGFEPointLightElement(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<SVGFEPointLightElement> impl)
    : JSSVGElement(structure, globalObject, impl)
{
}

JSObject* JSSVGFEPointLightElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGFEPointLightElementPrototype(JSSVGFEPointLightElementPrototype::createStructure(JSSVGElementPrototype::self(exec, globalObject)));
}

bool JSSVGFEPointLightElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGFEPointLightElement, Base>(exec, &JSSVGFEPointLightElementTable, this, propertyName, slot);
}

bool JSSVGFEPointLightElement::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGFEPointLightElement, Base>(exec, &JSSVGFEPointLightElementTable, this, propertyName, descriptor);
}

JSValue jsSVGFEPointLightElementX(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGFEPointLightElement* castedThis = static_cast<JSSVGFEPointLightElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGFEPointLightElement* imp = static_cast<SVGFEPointLightElement*>(castedThis->impl());
    RefPtr<SVGAnimatedNumber> obj = imp->xAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFEPointLightElementY(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGFEPointLightElement* castedThis = static_cast<JSSVGFEPointLightElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGFEPointLightElement* imp = static_cast<SVGFEPointLightElement*>(castedThis->impl());
    RefPtr<SVGAnimatedNumber> obj = imp->yAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFEPointLightElementZ(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGFEPointLightElement* castedThis = static_cast<JSSVGFEPointLightElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGFEPointLightElement* imp = static_cast<SVGFEPointLightElement*>(castedThis->impl());
    RefPtr<SVGAnimatedNumber> obj = imp->zAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFEPointLightElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGFEPointLightElement* domObject = static_cast<JSSVGFEPointLightElement*>(asObject(slot.slotBase()));
    return JSSVGFEPointLightElement::getConstructor(exec, domObject->globalObject());
}
JSValue JSSVGFEPointLightElement::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSSVGFEPointLightElementConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}


}

#endif // ENABLE(SVG) && ENABLE(FILTERS)