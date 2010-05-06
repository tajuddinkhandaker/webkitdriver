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
#include "JSAttr.h"

#include "Attr.h"
#include "CSSMutableStyleDeclaration.h"
#include "CSSStyleDeclaration.h"
#include "Element.h"
#include "JSCSSStyleDeclaration.h"
#include "JSElement.h"
#include "KURL.h"
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSAttr);

/* Hash table */

static const HashTableValue JSAttrTableValues[8] =
{
    { "name", DontDelete|ReadOnly, (intptr_t)jsAttrName, (intptr_t)0 },
    { "specified", DontDelete|ReadOnly, (intptr_t)jsAttrSpecified, (intptr_t)0 },
    { "value", DontDelete, (intptr_t)jsAttrValue, (intptr_t)setJSAttrValue },
    { "ownerElement", DontDelete|ReadOnly, (intptr_t)jsAttrOwnerElement, (intptr_t)0 },
    { "isId", DontDelete|ReadOnly, (intptr_t)jsAttrIsId, (intptr_t)0 },
    { "style", DontDelete|ReadOnly, (intptr_t)jsAttrStyle, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsAttrConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSAttrTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 127, JSAttrTableValues, 0 };
#else
    { 18, 15, JSAttrTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSAttrConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSAttrConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSAttrConstructorTableValues, 0 };
#else
    { 1, 0, JSAttrConstructorTableValues, 0 };
#endif

class JSAttrConstructor : public DOMConstructorObject {
public:
    JSAttrConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSAttrConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSAttrPrototype::self(exec, globalObject), None);
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

const ClassInfo JSAttrConstructor::s_info = { "AttrConstructor", 0, &JSAttrConstructorTable, 0 };

bool JSAttrConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSAttrConstructor, DOMObject>(exec, &JSAttrConstructorTable, this, propertyName, slot);
}

bool JSAttrConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSAttrConstructor, DOMObject>(exec, &JSAttrConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSAttrPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSAttrPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSAttrPrototypeTableValues, 0 };
#else
    { 1, 0, JSAttrPrototypeTableValues, 0 };
#endif

const ClassInfo JSAttrPrototype::s_info = { "AttrPrototype", 0, &JSAttrPrototypeTable, 0 };

JSObject* JSAttrPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSAttr>(exec, globalObject);
}

const ClassInfo JSAttr::s_info = { "Attr", &JSNode::s_info, &JSAttrTable, 0 };

JSAttr::JSAttr(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<Attr> impl)
    : JSNode(structure, globalObject, impl)
{
}

JSObject* JSAttr::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSAttrPrototype(JSAttrPrototype::createStructure(JSNodePrototype::self(exec, globalObject)));
}

bool JSAttr::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSAttr, Base>(exec, &JSAttrTable, this, propertyName, slot);
}

bool JSAttr::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSAttr, Base>(exec, &JSAttrTable, this, propertyName, descriptor);
}

JSValue jsAttrName(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSAttr* castedThis = static_cast<JSAttr*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    Attr* imp = static_cast<Attr*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, imp->name());
    return result;
}

JSValue jsAttrSpecified(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSAttr* castedThis = static_cast<JSAttr*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    Attr* imp = static_cast<Attr*>(castedThis->impl());
    JSValue result = jsBoolean(imp->specified());
    return result;
}

JSValue jsAttrValue(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSAttr* castedThis = static_cast<JSAttr*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    Attr* imp = static_cast<Attr*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, imp->value());
    return result;
}

JSValue jsAttrOwnerElement(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSAttr* castedThis = static_cast<JSAttr*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    Attr* imp = static_cast<Attr*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->ownerElement()));
    return result;
}

JSValue jsAttrIsId(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSAttr* castedThis = static_cast<JSAttr*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    Attr* imp = static_cast<Attr*>(castedThis->impl());
    JSValue result = jsBoolean(imp->isId());
    return result;
}

JSValue jsAttrStyle(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSAttr* castedThis = static_cast<JSAttr*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    Attr* imp = static_cast<Attr*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->style()));
    return result;
}

JSValue jsAttrConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSAttr* domObject = static_cast<JSAttr*>(asObject(slot.slotBase()));
    return JSAttr::getConstructor(exec, domObject->globalObject());
}
void JSAttr::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSAttr, Base>(exec, propertyName, value, &JSAttrTable, this, slot);
}

void setJSAttrValue(ExecState* exec, JSObject* thisObject, JSValue value)
{
    static_cast<JSAttr*>(thisObject)->setValue(exec, value);
}

JSValue JSAttr::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSAttrConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

Attr* toAttr(JSC::JSValue value)
{
    return value.inherits(&JSAttr::s_info) ? static_cast<JSAttr*>(asObject(value))->impl() : 0;
}

}
