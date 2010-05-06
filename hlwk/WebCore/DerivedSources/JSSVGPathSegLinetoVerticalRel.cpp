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

#include "JSSVGPathSegLinetoVerticalRel.h"

#include "SVGPathSegLinetoVertical.h"
#include <runtime/JSNumberCell.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGPathSegLinetoVerticalRel);

/* Hash table */

static const HashTableValue JSSVGPathSegLinetoVerticalRelTableValues[3] =
{
    { "y", DontDelete, (intptr_t)jsSVGPathSegLinetoVerticalRelY, (intptr_t)setJSSVGPathSegLinetoVerticalRelY },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsSVGPathSegLinetoVerticalRelConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGPathSegLinetoVerticalRelTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 1, JSSVGPathSegLinetoVerticalRelTableValues, 0 };
#else
    { 4, 3, JSSVGPathSegLinetoVerticalRelTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSSVGPathSegLinetoVerticalRelConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGPathSegLinetoVerticalRelConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGPathSegLinetoVerticalRelConstructorTableValues, 0 };
#else
    { 1, 0, JSSVGPathSegLinetoVerticalRelConstructorTableValues, 0 };
#endif

class JSSVGPathSegLinetoVerticalRelConstructor : public DOMConstructorObject {
public:
    JSSVGPathSegLinetoVerticalRelConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSSVGPathSegLinetoVerticalRelConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSSVGPathSegLinetoVerticalRelPrototype::self(exec, globalObject), None);
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

const ClassInfo JSSVGPathSegLinetoVerticalRelConstructor::s_info = { "SVGPathSegLinetoVerticalRelConstructor", 0, &JSSVGPathSegLinetoVerticalRelConstructorTable, 0 };

bool JSSVGPathSegLinetoVerticalRelConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPathSegLinetoVerticalRelConstructor, DOMObject>(exec, &JSSVGPathSegLinetoVerticalRelConstructorTable, this, propertyName, slot);
}

bool JSSVGPathSegLinetoVerticalRelConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGPathSegLinetoVerticalRelConstructor, DOMObject>(exec, &JSSVGPathSegLinetoVerticalRelConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSSVGPathSegLinetoVerticalRelPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGPathSegLinetoVerticalRelPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGPathSegLinetoVerticalRelPrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGPathSegLinetoVerticalRelPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGPathSegLinetoVerticalRelPrototype::s_info = { "SVGPathSegLinetoVerticalRelPrototype", 0, &JSSVGPathSegLinetoVerticalRelPrototypeTable, 0 };

JSObject* JSSVGPathSegLinetoVerticalRelPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGPathSegLinetoVerticalRel>(exec, globalObject);
}

const ClassInfo JSSVGPathSegLinetoVerticalRel::s_info = { "SVGPathSegLinetoVerticalRel", &JSSVGPathSeg::s_info, &JSSVGPathSegLinetoVerticalRelTable, 0 };

JSSVGPathSegLinetoVerticalRel::JSSVGPathSegLinetoVerticalRel(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<SVGPathSegLinetoVerticalRel> impl)
    : JSSVGPathSeg(structure, globalObject, impl)
{
}

JSObject* JSSVGPathSegLinetoVerticalRel::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGPathSegLinetoVerticalRelPrototype(JSSVGPathSegLinetoVerticalRelPrototype::createStructure(JSSVGPathSegPrototype::self(exec, globalObject)));
}

bool JSSVGPathSegLinetoVerticalRel::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPathSegLinetoVerticalRel, Base>(exec, &JSSVGPathSegLinetoVerticalRelTable, this, propertyName, slot);
}

bool JSSVGPathSegLinetoVerticalRel::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGPathSegLinetoVerticalRel, Base>(exec, &JSSVGPathSegLinetoVerticalRelTable, this, propertyName, descriptor);
}

JSValue jsSVGPathSegLinetoVerticalRelY(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGPathSegLinetoVerticalRel* castedThis = static_cast<JSSVGPathSegLinetoVerticalRel*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGPathSegLinetoVerticalRel* imp = static_cast<SVGPathSegLinetoVerticalRel*>(castedThis->impl());
    JSValue result = jsNumber(exec, imp->y());
    return result;
}

JSValue jsSVGPathSegLinetoVerticalRelConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGPathSegLinetoVerticalRel* domObject = static_cast<JSSVGPathSegLinetoVerticalRel*>(asObject(slot.slotBase()));
    return JSSVGPathSegLinetoVerticalRel::getConstructor(exec, domObject->globalObject());
}
void JSSVGPathSegLinetoVerticalRel::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSSVGPathSegLinetoVerticalRel, Base>(exec, propertyName, value, &JSSVGPathSegLinetoVerticalRelTable, this, slot);
}

void setJSSVGPathSegLinetoVerticalRelY(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGPathSegLinetoVerticalRel* castedThisObj = static_cast<JSSVGPathSegLinetoVerticalRel*>(thisObject);
    SVGPathSegLinetoVerticalRel* imp = static_cast<SVGPathSegLinetoVerticalRel*>(castedThisObj->impl());
    imp->setY(value.toFloat(exec));
    JSSVGContextCache::propagateSVGDOMChange(castedThisObj, imp->associatedAttributeName());
}

JSValue JSSVGPathSegLinetoVerticalRel::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSSVGPathSegLinetoVerticalRelConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}


}

#endif // ENABLE(SVG)
