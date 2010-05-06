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
#include "JSHTMLTableCaptionElement.h"

#include "HTMLTableCaptionElement.h"
#include "KURL.h"
#include <runtime/JSString.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSHTMLTableCaptionElement);

/* Hash table */

static const HashTableValue JSHTMLTableCaptionElementTableValues[3] =
{
    { "align", DontDelete, (intptr_t)jsHTMLTableCaptionElementAlign, (intptr_t)setJSHTMLTableCaptionElementAlign },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsHTMLTableCaptionElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSHTMLTableCaptionElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 7, JSHTMLTableCaptionElementTableValues, 0 };
#else
    { 5, 3, JSHTMLTableCaptionElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSHTMLTableCaptionElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSHTMLTableCaptionElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLTableCaptionElementConstructorTableValues, 0 };
#else
    { 1, 0, JSHTMLTableCaptionElementConstructorTableValues, 0 };
#endif

class JSHTMLTableCaptionElementConstructor : public DOMConstructorObject {
public:
    JSHTMLTableCaptionElementConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSHTMLTableCaptionElementConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSHTMLTableCaptionElementPrototype::self(exec, globalObject), None);
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

const ClassInfo JSHTMLTableCaptionElementConstructor::s_info = { "HTMLTableCaptionElementConstructor", 0, &JSHTMLTableCaptionElementConstructorTable, 0 };

bool JSHTMLTableCaptionElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLTableCaptionElementConstructor, DOMObject>(exec, &JSHTMLTableCaptionElementConstructorTable, this, propertyName, slot);
}

bool JSHTMLTableCaptionElementConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSHTMLTableCaptionElementConstructor, DOMObject>(exec, &JSHTMLTableCaptionElementConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSHTMLTableCaptionElementPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSHTMLTableCaptionElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLTableCaptionElementPrototypeTableValues, 0 };
#else
    { 1, 0, JSHTMLTableCaptionElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSHTMLTableCaptionElementPrototype::s_info = { "HTMLTableCaptionElementPrototype", 0, &JSHTMLTableCaptionElementPrototypeTable, 0 };

JSObject* JSHTMLTableCaptionElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSHTMLTableCaptionElement>(exec, globalObject);
}

const ClassInfo JSHTMLTableCaptionElement::s_info = { "HTMLTableCaptionElement", &JSHTMLElement::s_info, &JSHTMLTableCaptionElementTable, 0 };

JSHTMLTableCaptionElement::JSHTMLTableCaptionElement(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<HTMLTableCaptionElement> impl)
    : JSHTMLElement(structure, globalObject, impl)
{
}

JSObject* JSHTMLTableCaptionElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSHTMLTableCaptionElementPrototype(JSHTMLTableCaptionElementPrototype::createStructure(JSHTMLElementPrototype::self(exec, globalObject)));
}

bool JSHTMLTableCaptionElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLTableCaptionElement, Base>(exec, &JSHTMLTableCaptionElementTable, this, propertyName, slot);
}

bool JSHTMLTableCaptionElement::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSHTMLTableCaptionElement, Base>(exec, &JSHTMLTableCaptionElementTable, this, propertyName, descriptor);
}

JSValue jsHTMLTableCaptionElementAlign(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSHTMLTableCaptionElement* castedThis = static_cast<JSHTMLTableCaptionElement*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    HTMLTableCaptionElement* imp = static_cast<HTMLTableCaptionElement*>(castedThis->impl());
    JSValue result = jsString(exec, imp->align());
    return result;
}

JSValue jsHTMLTableCaptionElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSHTMLTableCaptionElement* domObject = static_cast<JSHTMLTableCaptionElement*>(asObject(slot.slotBase()));
    return JSHTMLTableCaptionElement::getConstructor(exec, domObject->globalObject());
}
void JSHTMLTableCaptionElement::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSHTMLTableCaptionElement, Base>(exec, propertyName, value, &JSHTMLTableCaptionElementTable, this, slot);
}

void setJSHTMLTableCaptionElementAlign(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSHTMLTableCaptionElement* castedThisObj = static_cast<JSHTMLTableCaptionElement*>(thisObject);
    HTMLTableCaptionElement* imp = static_cast<HTMLTableCaptionElement*>(castedThisObj->impl());
    imp->setAlign(valueToStringWithNullCheck(exec, value));
}

JSValue JSHTMLTableCaptionElement::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSHTMLTableCaptionElementConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

HTMLTableCaptionElement* toHTMLTableCaptionElement(JSC::JSValue value)
{
    return value.inherits(&JSHTMLTableCaptionElement::s_info) ? static_cast<JSHTMLTableCaptionElement*>(asObject(value))->impl() : 0;
}

}
