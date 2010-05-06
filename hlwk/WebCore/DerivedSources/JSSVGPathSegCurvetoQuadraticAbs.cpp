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

#include "JSSVGPathSegCurvetoQuadraticAbs.h"

#include "SVGPathSegCurvetoQuadratic.h"
#include <runtime/JSNumberCell.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGPathSegCurvetoQuadraticAbs);

/* Hash table */

static const HashTableValue JSSVGPathSegCurvetoQuadraticAbsTableValues[6] =
{
    { "x", DontDelete, (intptr_t)jsSVGPathSegCurvetoQuadraticAbsX, (intptr_t)setJSSVGPathSegCurvetoQuadraticAbsX },
    { "y", DontDelete, (intptr_t)jsSVGPathSegCurvetoQuadraticAbsY, (intptr_t)setJSSVGPathSegCurvetoQuadraticAbsY },
    { "x1", DontDelete, (intptr_t)jsSVGPathSegCurvetoQuadraticAbsX1, (intptr_t)setJSSVGPathSegCurvetoQuadraticAbsX1 },
    { "y1", DontDelete, (intptr_t)jsSVGPathSegCurvetoQuadraticAbsY1, (intptr_t)setJSSVGPathSegCurvetoQuadraticAbsY1 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsSVGPathSegCurvetoQuadraticAbsConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGPathSegCurvetoQuadraticAbsTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSSVGPathSegCurvetoQuadraticAbsTableValues, 0 };
#else
    { 16, 15, JSSVGPathSegCurvetoQuadraticAbsTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSSVGPathSegCurvetoQuadraticAbsConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGPathSegCurvetoQuadraticAbsConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGPathSegCurvetoQuadraticAbsConstructorTableValues, 0 };
#else
    { 1, 0, JSSVGPathSegCurvetoQuadraticAbsConstructorTableValues, 0 };
#endif

class JSSVGPathSegCurvetoQuadraticAbsConstructor : public DOMConstructorObject {
public:
    JSSVGPathSegCurvetoQuadraticAbsConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSSVGPathSegCurvetoQuadraticAbsConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSSVGPathSegCurvetoQuadraticAbsPrototype::self(exec, globalObject), None);
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

const ClassInfo JSSVGPathSegCurvetoQuadraticAbsConstructor::s_info = { "SVGPathSegCurvetoQuadraticAbsConstructor", 0, &JSSVGPathSegCurvetoQuadraticAbsConstructorTable, 0 };

bool JSSVGPathSegCurvetoQuadraticAbsConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPathSegCurvetoQuadraticAbsConstructor, DOMObject>(exec, &JSSVGPathSegCurvetoQuadraticAbsConstructorTable, this, propertyName, slot);
}

bool JSSVGPathSegCurvetoQuadraticAbsConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGPathSegCurvetoQuadraticAbsConstructor, DOMObject>(exec, &JSSVGPathSegCurvetoQuadraticAbsConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSSVGPathSegCurvetoQuadraticAbsPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGPathSegCurvetoQuadraticAbsPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGPathSegCurvetoQuadraticAbsPrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGPathSegCurvetoQuadraticAbsPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGPathSegCurvetoQuadraticAbsPrototype::s_info = { "SVGPathSegCurvetoQuadraticAbsPrototype", 0, &JSSVGPathSegCurvetoQuadraticAbsPrototypeTable, 0 };

JSObject* JSSVGPathSegCurvetoQuadraticAbsPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGPathSegCurvetoQuadraticAbs>(exec, globalObject);
}

const ClassInfo JSSVGPathSegCurvetoQuadraticAbs::s_info = { "SVGPathSegCurvetoQuadraticAbs", &JSSVGPathSeg::s_info, &JSSVGPathSegCurvetoQuadraticAbsTable, 0 };

JSSVGPathSegCurvetoQuadraticAbs::JSSVGPathSegCurvetoQuadraticAbs(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<SVGPathSegCurvetoQuadraticAbs> impl)
    : JSSVGPathSeg(structure, globalObject, impl)
{
}

JSObject* JSSVGPathSegCurvetoQuadraticAbs::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGPathSegCurvetoQuadraticAbsPrototype(JSSVGPathSegCurvetoQuadraticAbsPrototype::createStructure(JSSVGPathSegPrototype::self(exec, globalObject)));
}

bool JSSVGPathSegCurvetoQuadraticAbs::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPathSegCurvetoQuadraticAbs, Base>(exec, &JSSVGPathSegCurvetoQuadraticAbsTable, this, propertyName, slot);
}

bool JSSVGPathSegCurvetoQuadraticAbs::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGPathSegCurvetoQuadraticAbs, Base>(exec, &JSSVGPathSegCurvetoQuadraticAbsTable, this, propertyName, descriptor);
}

JSValue jsSVGPathSegCurvetoQuadraticAbsX(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGPathSegCurvetoQuadraticAbs* castedThis = static_cast<JSSVGPathSegCurvetoQuadraticAbs*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGPathSegCurvetoQuadraticAbs* imp = static_cast<SVGPathSegCurvetoQuadraticAbs*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->x());
    return result;
}

JSValue jsSVGPathSegCurvetoQuadraticAbsY(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGPathSegCurvetoQuadraticAbs* castedThis = static_cast<JSSVGPathSegCurvetoQuadraticAbs*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGPathSegCurvetoQuadraticAbs* imp = static_cast<SVGPathSegCurvetoQuadraticAbs*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->y());
    return result;
}

JSValue jsSVGPathSegCurvetoQuadraticAbsX1(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGPathSegCurvetoQuadraticAbs* castedThis = static_cast<JSSVGPathSegCurvetoQuadraticAbs*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGPathSegCurvetoQuadraticAbs* imp = static_cast<SVGPathSegCurvetoQuadraticAbs*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->x1());
    return result;
}

JSValue jsSVGPathSegCurvetoQuadraticAbsY1(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGPathSegCurvetoQuadraticAbs* castedThis = static_cast<JSSVGPathSegCurvetoQuadraticAbs*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGPathSegCurvetoQuadraticAbs* imp = static_cast<SVGPathSegCurvetoQuadraticAbs*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->y1());
    return result;
}

JSValue jsSVGPathSegCurvetoQuadraticAbsConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGPathSegCurvetoQuadraticAbs* domObject = static_cast<JSSVGPathSegCurvetoQuadraticAbs*>(asObject(slot.slotBase()));
    return JSSVGPathSegCurvetoQuadraticAbs::getConstructor(exec, domObject->globalObject());
}
void JSSVGPathSegCurvetoQuadraticAbs::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSSVGPathSegCurvetoQuadraticAbs, Base>(exec, propertyName, value, &JSSVGPathSegCurvetoQuadraticAbsTable, this, slot);
}

void setJSSVGPathSegCurvetoQuadraticAbsX(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGPathSegCurvetoQuadraticAbs* castedThisObj = static_cast<JSSVGPathSegCurvetoQuadraticAbs*>(thisObject);
    SVGPathSegCurvetoQuadraticAbs* imp = static_cast<SVGPathSegCurvetoQuadraticAbs*>(castedThisObj->impl());
    imp->setX(value.toFloat(exec));
    JSSVGContextCache::propagateSVGDOMChange(castedThisObj, imp->associatedAttributeName());
}

void setJSSVGPathSegCurvetoQuadraticAbsY(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGPathSegCurvetoQuadraticAbs* castedThisObj = static_cast<JSSVGPathSegCurvetoQuadraticAbs*>(thisObject);
    SVGPathSegCurvetoQuadraticAbs* imp = static_cast<SVGPathSegCurvetoQuadraticAbs*>(castedThisObj->impl());
    imp->setY(value.toFloat(exec));
    JSSVGContextCache::propagateSVGDOMChange(castedThisObj, imp->associatedAttributeName());
}

void setJSSVGPathSegCurvetoQuadraticAbsX1(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGPathSegCurvetoQuadraticAbs* castedThisObj = static_cast<JSSVGPathSegCurvetoQuadraticAbs*>(thisObject);
    SVGPathSegCurvetoQuadraticAbs* imp = static_cast<SVGPathSegCurvetoQuadraticAbs*>(castedThisObj->impl());
    imp->setX1(value.toFloat(exec));
    JSSVGContextCache::propagateSVGDOMChange(castedThisObj, imp->associatedAttributeName());
}

void setJSSVGPathSegCurvetoQuadraticAbsY1(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGPathSegCurvetoQuadraticAbs* castedThisObj = static_cast<JSSVGPathSegCurvetoQuadraticAbs*>(thisObject);
    SVGPathSegCurvetoQuadraticAbs* imp = static_cast<SVGPathSegCurvetoQuadraticAbs*>(castedThisObj->impl());
    imp->setY1(value.toFloat(exec));
    JSSVGContextCache::propagateSVGDOMChange(castedThisObj, imp->associatedAttributeName());
}

JSValue JSSVGPathSegCurvetoQuadraticAbs::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSSVGPathSegCurvetoQuadraticAbsConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}


}

#endif // ENABLE(SVG)
