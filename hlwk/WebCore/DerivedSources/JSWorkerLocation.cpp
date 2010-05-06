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

#if ENABLE(WORKERS)

#include "JSWorkerLocation.h"

#include "KURL.h"
#include "WorkerLocation.h"
#include <runtime/Error.h>
#include <runtime/JSString.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSWorkerLocation);

/* Hash table */

static const HashTableValue JSWorkerLocationTableValues[10] =
{
    { "href", DontDelete|ReadOnly, (intptr_t)jsWorkerLocationHref, (intptr_t)0 },
    { "protocol", DontDelete|ReadOnly, (intptr_t)jsWorkerLocationProtocol, (intptr_t)0 },
    { "host", DontDelete|ReadOnly, (intptr_t)jsWorkerLocationHost, (intptr_t)0 },
    { "hostname", DontDelete|ReadOnly, (intptr_t)jsWorkerLocationHostname, (intptr_t)0 },
    { "port", DontDelete|ReadOnly, (intptr_t)jsWorkerLocationPort, (intptr_t)0 },
    { "pathname", DontDelete|ReadOnly, (intptr_t)jsWorkerLocationPathname, (intptr_t)0 },
    { "search", DontDelete|ReadOnly, (intptr_t)jsWorkerLocationSearch, (intptr_t)0 },
    { "hash", DontDelete|ReadOnly, (intptr_t)jsWorkerLocationHash, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsWorkerLocationConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSWorkerLocationTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 511, JSWorkerLocationTableValues, 0 };
#else
    { 35, 31, JSWorkerLocationTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSWorkerLocationConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSWorkerLocationConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSWorkerLocationConstructorTableValues, 0 };
#else
    { 1, 0, JSWorkerLocationConstructorTableValues, 0 };
#endif

class JSWorkerLocationConstructor : public DOMConstructorObject {
public:
    JSWorkerLocationConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSWorkerLocationConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSWorkerLocationPrototype::self(exec, globalObject), None);
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

const ClassInfo JSWorkerLocationConstructor::s_info = { "WorkerLocationConstructor", 0, &JSWorkerLocationConstructorTable, 0 };

bool JSWorkerLocationConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSWorkerLocationConstructor, DOMObject>(exec, &JSWorkerLocationConstructorTable, this, propertyName, slot);
}

bool JSWorkerLocationConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSWorkerLocationConstructor, DOMObject>(exec, &JSWorkerLocationConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSWorkerLocationPrototypeTableValues[2] =
{
    { "toString", DontDelete|DontEnum|Function, (intptr_t)jsWorkerLocationPrototypeFunctionToString, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSWorkerLocationPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSWorkerLocationPrototypeTableValues, 0 };
#else
    { 2, 1, JSWorkerLocationPrototypeTableValues, 0 };
#endif

static const HashTable* getJSWorkerLocationPrototypeTable(ExecState* exec)
{
    return getHashTableForGlobalData(exec->globalData(), &JSWorkerLocationPrototypeTable);
}
const ClassInfo JSWorkerLocationPrototype::s_info = { "WorkerLocationPrototype", 0, 0, getJSWorkerLocationPrototypeTable };

JSObject* JSWorkerLocationPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSWorkerLocation>(exec, globalObject);
}

bool JSWorkerLocationPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, getJSWorkerLocationPrototypeTable(exec), this, propertyName, slot);
}

bool JSWorkerLocationPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticFunctionDescriptor<JSObject>(exec, getJSWorkerLocationPrototypeTable(exec), this, propertyName, descriptor);
}

static const HashTable* getJSWorkerLocationTable(ExecState* exec)
{
    return getHashTableForGlobalData(exec->globalData(), &JSWorkerLocationTable);
}
const ClassInfo JSWorkerLocation::s_info = { "WorkerLocation", 0, 0, getJSWorkerLocationTable };

JSWorkerLocation::JSWorkerLocation(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<WorkerLocation> impl)
    : DOMObjectWithGlobalPointer(structure, globalObject)
    , m_impl(impl)
{
}

JSWorkerLocation::~JSWorkerLocation()
{
    forgetDOMObject(this, impl());
}

JSObject* JSWorkerLocation::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSWorkerLocationPrototype(JSWorkerLocationPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSWorkerLocation::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSWorkerLocation, Base>(exec, getJSWorkerLocationTable(exec), this, propertyName, slot);
}

bool JSWorkerLocation::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSWorkerLocation, Base>(exec, getJSWorkerLocationTable(exec), this, propertyName, descriptor);
}

JSValue jsWorkerLocationHref(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSWorkerLocation* castedThis = static_cast<JSWorkerLocation*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    WorkerLocation* imp = static_cast<WorkerLocation*>(castedThis->impl());
    JSValue result = jsString(exec, imp->href());
    return result;
}

JSValue jsWorkerLocationProtocol(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSWorkerLocation* castedThis = static_cast<JSWorkerLocation*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    WorkerLocation* imp = static_cast<WorkerLocation*>(castedThis->impl());
    JSValue result = jsString(exec, imp->protocol());
    return result;
}

JSValue jsWorkerLocationHost(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSWorkerLocation* castedThis = static_cast<JSWorkerLocation*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    WorkerLocation* imp = static_cast<WorkerLocation*>(castedThis->impl());
    JSValue result = jsString(exec, imp->host());
    return result;
}

JSValue jsWorkerLocationHostname(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSWorkerLocation* castedThis = static_cast<JSWorkerLocation*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    WorkerLocation* imp = static_cast<WorkerLocation*>(castedThis->impl());
    JSValue result = jsString(exec, imp->hostname());
    return result;
}

JSValue jsWorkerLocationPort(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSWorkerLocation* castedThis = static_cast<JSWorkerLocation*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    WorkerLocation* imp = static_cast<WorkerLocation*>(castedThis->impl());
    JSValue result = jsString(exec, imp->port());
    return result;
}

JSValue jsWorkerLocationPathname(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSWorkerLocation* castedThis = static_cast<JSWorkerLocation*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    WorkerLocation* imp = static_cast<WorkerLocation*>(castedThis->impl());
    JSValue result = jsString(exec, imp->pathname());
    return result;
}

JSValue jsWorkerLocationSearch(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSWorkerLocation* castedThis = static_cast<JSWorkerLocation*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    WorkerLocation* imp = static_cast<WorkerLocation*>(castedThis->impl());
    JSValue result = jsString(exec, imp->search());
    return result;
}

JSValue jsWorkerLocationHash(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSWorkerLocation* castedThis = static_cast<JSWorkerLocation*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    WorkerLocation* imp = static_cast<WorkerLocation*>(castedThis->impl());
    JSValue result = jsString(exec, imp->hash());
    return result;
}

JSValue jsWorkerLocationConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSWorkerLocation* domObject = static_cast<JSWorkerLocation*>(asObject(slot.slotBase()));
    return JSWorkerLocation::getConstructor(exec, domObject->globalObject());
}
JSValue JSWorkerLocation::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSWorkerLocationConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSValue JSC_HOST_CALL jsWorkerLocationPrototypeFunctionToString(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSWorkerLocation::s_info))
        return throwError(exec, TypeError);
    JSWorkerLocation* castedThisObj = static_cast<JSWorkerLocation*>(asObject(thisValue));
    WorkerLocation* imp = static_cast<WorkerLocation*>(castedThisObj->impl());


    JSC::JSValue result = jsString(exec, imp->toString());
    return result;
}

JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, WorkerLocation* object)
{
    return getDOMObjectWrapper<JSWorkerLocation>(exec, globalObject, object);
}
WorkerLocation* toWorkerLocation(JSC::JSValue value)
{
    return value.inherits(&JSWorkerLocation::s_info) ? static_cast<JSWorkerLocation*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(WORKERS)
