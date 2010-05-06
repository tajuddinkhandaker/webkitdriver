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

#include "JSSVGAngle.h"

#include "KURL.h"
#include "SVGAngle.h"
#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGAngle);

/* Hash table */

static const HashTableValue JSSVGAngleTableValues[6] =
{
    { "unitType", DontDelete|ReadOnly, (intptr_t)jsSVGAngleUnitType, (intptr_t)0 },
    { "value", DontDelete, (intptr_t)jsSVGAngleValue, (intptr_t)setJSSVGAngleValue },
    { "valueInSpecifiedUnits", DontDelete, (intptr_t)jsSVGAngleValueInSpecifiedUnits, (intptr_t)setJSSVGAngleValueInSpecifiedUnits },
    { "valueAsString", DontDelete, (intptr_t)jsSVGAngleValueAsString, (intptr_t)setJSSVGAngleValueAsString },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsSVGAngleConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGAngleTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 255, JSSVGAngleTableValues, 0 };
#else
    { 17, 15, JSSVGAngleTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSSVGAngleConstructorTableValues[6] =
{
    { "SVG_ANGLETYPE_UNKNOWN", DontDelete|ReadOnly, (intptr_t)jsSVGAngleSVG_ANGLETYPE_UNKNOWN, (intptr_t)0 },
    { "SVG_ANGLETYPE_UNSPECIFIED", DontDelete|ReadOnly, (intptr_t)jsSVGAngleSVG_ANGLETYPE_UNSPECIFIED, (intptr_t)0 },
    { "SVG_ANGLETYPE_DEG", DontDelete|ReadOnly, (intptr_t)jsSVGAngleSVG_ANGLETYPE_DEG, (intptr_t)0 },
    { "SVG_ANGLETYPE_RAD", DontDelete|ReadOnly, (intptr_t)jsSVGAngleSVG_ANGLETYPE_RAD, (intptr_t)0 },
    { "SVG_ANGLETYPE_GRAD", DontDelete|ReadOnly, (intptr_t)jsSVGAngleSVG_ANGLETYPE_GRAD, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGAngleConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 255, JSSVGAngleConstructorTableValues, 0 };
#else
    { 18, 15, JSSVGAngleConstructorTableValues, 0 };
#endif

class JSSVGAngleConstructor : public DOMConstructorObject {
public:
    JSSVGAngleConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSSVGAngleConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSSVGAnglePrototype::self(exec, globalObject), None);
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

const ClassInfo JSSVGAngleConstructor::s_info = { "SVGAngleConstructor", 0, &JSSVGAngleConstructorTable, 0 };

bool JSSVGAngleConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGAngleConstructor, DOMObject>(exec, &JSSVGAngleConstructorTable, this, propertyName, slot);
}

bool JSSVGAngleConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGAngleConstructor, DOMObject>(exec, &JSSVGAngleConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSSVGAnglePrototypeTableValues[8] =
{
    { "SVG_ANGLETYPE_UNKNOWN", DontDelete|ReadOnly, (intptr_t)jsSVGAngleSVG_ANGLETYPE_UNKNOWN, (intptr_t)0 },
    { "SVG_ANGLETYPE_UNSPECIFIED", DontDelete|ReadOnly, (intptr_t)jsSVGAngleSVG_ANGLETYPE_UNSPECIFIED, (intptr_t)0 },
    { "SVG_ANGLETYPE_DEG", DontDelete|ReadOnly, (intptr_t)jsSVGAngleSVG_ANGLETYPE_DEG, (intptr_t)0 },
    { "SVG_ANGLETYPE_RAD", DontDelete|ReadOnly, (intptr_t)jsSVGAngleSVG_ANGLETYPE_RAD, (intptr_t)0 },
    { "SVG_ANGLETYPE_GRAD", DontDelete|ReadOnly, (intptr_t)jsSVGAngleSVG_ANGLETYPE_GRAD, (intptr_t)0 },
    { "newValueSpecifiedUnits", DontDelete|Function, (intptr_t)jsSVGAnglePrototypeFunctionNewValueSpecifiedUnits, (intptr_t)2 },
    { "convertToSpecifiedUnits", DontDelete|Function, (intptr_t)jsSVGAnglePrototypeFunctionConvertToSpecifiedUnits, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGAnglePrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 255, JSSVGAnglePrototypeTableValues, 0 };
#else
    { 18, 15, JSSVGAnglePrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGAnglePrototype::s_info = { "SVGAnglePrototype", 0, &JSSVGAnglePrototypeTable, 0 };

JSObject* JSSVGAnglePrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGAngle>(exec, globalObject);
}

bool JSSVGAnglePrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticPropertySlot<JSSVGAnglePrototype, JSObject>(exec, &JSSVGAnglePrototypeTable, this, propertyName, slot);
}

bool JSSVGAnglePrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticPropertyDescriptor<JSSVGAnglePrototype, JSObject>(exec, &JSSVGAnglePrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSSVGAngle::s_info = { "SVGAngle", 0, &JSSVGAngleTable, 0 };

JSSVGAngle::JSSVGAngle(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<JSSVGPODTypeWrapper<SVGAngle> > impl)
    : DOMObjectWithGlobalPointer(structure, globalObject)
    , m_impl(impl)
{
}

JSSVGAngle::~JSSVGAngle()
{
    forgetDOMObject(this, impl());
    JSSVGContextCache::forgetWrapper(this);
}

JSObject* JSSVGAngle::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGAnglePrototype(JSSVGAnglePrototype::createStructure(globalObject->objectPrototype()));
}

bool JSSVGAngle::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGAngle, Base>(exec, &JSSVGAngleTable, this, propertyName, slot);
}

bool JSSVGAngle::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGAngle, Base>(exec, &JSSVGAngleTable, this, propertyName, descriptor);
}

JSValue jsSVGAngleUnitType(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGAngle* castedThis = static_cast<JSSVGAngle*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGAngle imp(*castedThis->impl());
    JSValue result =  jsNumber(exec, imp.unitType());
    return result;
}

JSValue jsSVGAngleValue(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGAngle* castedThis = static_cast<JSSVGAngle*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGAngle imp(*castedThis->impl());
    JSValue result =  jsNumber(exec, imp.value());
    return result;
}

JSValue jsSVGAngleValueInSpecifiedUnits(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGAngle* castedThis = static_cast<JSSVGAngle*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGAngle imp(*castedThis->impl());
    JSValue result =  jsNumber(exec, imp.valueInSpecifiedUnits());
    return result;
}

JSValue jsSVGAngleValueAsString(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGAngle* castedThis = static_cast<JSSVGAngle*>(asObject(slot.slotBase()));
    UNUSED_PARAM(exec);
    SVGAngle imp(*castedThis->impl());
    JSValue result =  jsString(exec, imp.valueAsString());
    return result;
}

JSValue jsSVGAngleConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSSVGAngle* domObject = static_cast<JSSVGAngle*>(asObject(slot.slotBase()));
    return JSSVGAngle::getConstructor(exec, domObject->globalObject());
}
void JSSVGAngle::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSSVGAngle, Base>(exec, propertyName, value, &JSSVGAngleTable, this, slot);
}

void setJSSVGAngleValue(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGAngle* castedThisObj = static_cast<JSSVGAngle*>(thisObject);
    JSSVGPODTypeWrapper<SVGAngle> * imp = static_cast<JSSVGPODTypeWrapper<SVGAngle> *>(castedThisObj->impl());
    SVGAngle podImp(*imp);
    podImp.setValue(value.toFloat(exec));
    imp->commitChange(podImp, castedThisObj);
}

void setJSSVGAngleValueInSpecifiedUnits(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGAngle* castedThisObj = static_cast<JSSVGAngle*>(thisObject);
    JSSVGPODTypeWrapper<SVGAngle> * imp = static_cast<JSSVGPODTypeWrapper<SVGAngle> *>(castedThisObj->impl());
    SVGAngle podImp(*imp);
    podImp.setValueInSpecifiedUnits(value.toFloat(exec));
    imp->commitChange(podImp, castedThisObj);
}

void setJSSVGAngleValueAsString(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSSVGAngle* castedThisObj = static_cast<JSSVGAngle*>(thisObject);
    JSSVGPODTypeWrapper<SVGAngle> * imp = static_cast<JSSVGPODTypeWrapper<SVGAngle> *>(castedThisObj->impl());
    SVGAngle podImp(*imp);
    podImp.setValueAsString(valueToStringWithNullCheck(exec, value));
    imp->commitChange(podImp, castedThisObj);
}

JSValue JSSVGAngle::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSSVGAngleConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSValue JSC_HOST_CALL jsSVGAnglePrototypeFunctionNewValueSpecifiedUnits(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGAngle::s_info))
        return throwError(exec, TypeError);
    JSSVGAngle* castedThisObj = static_cast<JSSVGAngle*>(asObject(thisValue));
    JSSVGPODTypeWrapper<SVGAngle> * imp = static_cast<JSSVGPODTypeWrapper<SVGAngle> *>(castedThisObj->impl());
    SVGAngle podImp(*imp);
    unsigned short unitType = args.at(0).toInt32(exec);
    float valueInSpecifiedUnits = args.at(1).toFloat(exec);

    podImp.newValueSpecifiedUnits(unitType, valueInSpecifiedUnits);
    imp->commitChange(podImp, castedThisObj);
    return jsUndefined();
}

JSValue JSC_HOST_CALL jsSVGAnglePrototypeFunctionConvertToSpecifiedUnits(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGAngle::s_info))
        return throwError(exec, TypeError);
    JSSVGAngle* castedThisObj = static_cast<JSSVGAngle*>(asObject(thisValue));
    JSSVGPODTypeWrapper<SVGAngle> * imp = static_cast<JSSVGPODTypeWrapper<SVGAngle> *>(castedThisObj->impl());
    SVGAngle podImp(*imp);
    unsigned short unitType = args.at(0).toInt32(exec);

    podImp.convertToSpecifiedUnits(unitType);
    imp->commitChange(podImp, castedThisObj);
    return jsUndefined();
}

// Constant getters

JSValue jsSVGAngleSVG_ANGLETYPE_UNKNOWN(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(0));
}

JSValue jsSVGAngleSVG_ANGLETYPE_UNSPECIFIED(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(1));
}

JSValue jsSVGAngleSVG_ANGLETYPE_DEG(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(2));
}

JSValue jsSVGAngleSVG_ANGLETYPE_RAD(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(3));
}

JSValue jsSVGAngleSVG_ANGLETYPE_GRAD(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(4));
}

JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, JSSVGPODTypeWrapper<SVGAngle>* object, SVGElement* context)
{
    return getDOMObjectWrapper<JSSVGAngle, JSSVGPODTypeWrapper<SVGAngle> >(exec, globalObject, object, context);
}
SVGAngle toSVGAngle(JSC::JSValue value)
{
    return value.inherits(&JSSVGAngle::s_info) ? (SVGAngle) *static_cast<JSSVGAngle*>(asObject(value))->impl() : SVGAngle();
}

}

#endif // ENABLE(SVG)
