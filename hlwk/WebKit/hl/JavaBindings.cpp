#include "config.h"
#include "ApplicationCache.h"
#include "ApplicationCacheGroup.h"
#include "ApplicationCacheResource.h"
#include "ClientRect.h"
#include "ContentType.h"
#include "CString.h"
#include "CSSComputedStyleDeclaration.h"
#include "CSSParser.h"
#include "Document.h"
#include "Editor.h"
#include "Element.h"
#include "EventNames.h"
#include "EventHandler.h"
#include "ExtraKeyCodes.h"
#include "FileList.h"
#include "Frame.h"
#include "FrameLoader.h"
#include "FocusController.h"
#include "DocumentLoader.h"
#include "FrameView.h"
#include "HitTestResult.h"
#include "HTMLFrameOwnerElement.h"
#include "HTMLElement.h"
#include "HTMLMediaElement.h"
#include "HTMLFormElement.h"
#include "HTMLInputElement.h"
#include "HTMLOptionElement.h"
#include "HTMLSelectElement.h"
#include "HTMLTextAreaElement.h"
#include "InputElement.h"
#include "Logging.h"
#include "KeyboardEvent.h"
#include "markup.h"
#include "MouseEvent.h"
#include "Node.h"
#include "NetworkStateNotifier.h"
#include "NodeList.h"
#include "OptionElement.h"
#include "PlatformKeyboardEvent.h"
#include "Settings.h"
#include "StaticNodeList.h"
#include "TextIterator.h"
#include "Page.h"
#include "PageGroup.h"
#include "PlatformString.h"
#include "RenderTreeAsText.h"
#include "RenderObject.h"
#include "RenderView.h"
#include "ScriptController.h"
#include "ScriptObject.h"
#include "ScriptFunctionCall.h"
#include "ScriptSourceCode.h"
#include "ScriptString.h"
#include "ScriptValue.h"
#include "Storage.h"
#include "SubstituteData.h"
#include "TextEncoding.h"
#include "XPathResult.h"

#include "runtime_array.h"
#include "runtime_object.h"
#include "runtime/DateInstance.h"
#include "JSByteArray.h"
#include "JSDOMBinding.h"
#include "ExceptionBase.h"
#include "JSExceptionBase.h"
#include <runtime/Executable.h>
#include <runtime/JSFunction.h>
#include <runtime/FunctionConstructor.h>
#include "runtime/JSLock.h"
#include <runtime/JSValue.h>
#include <runtime/UString.h>

#include "JSNode.h"
#include "JSNodeList.h"

#include "EditorClientHl.h"
#include "DragClientHl.h"
#include "InspectorClientHl.h"
#include "ContextMenuClientHl.h"
#include "FrameLoaderClientHl.h"
#include "Chrome.h"
#include "ChromeClientHl.h"

#include "Database.h"
#include "DatabaseHl.h"
#include "DatabaseTask.h"
#include "DatabaseThread.h"
#include "DatabaseTrackerClientHl.h"
#include "SQLTransactionCoordinator.h"
#include "GeolocationControllerClientHl.h"
#include "GeolocationPosition.h"
#include "GeolocationController.h"

#include "CookieJar.h"
#include "CookieJarHl.h"
#include "rendering/RenderObject.h"
#include "rendering/RenderBoxModelObject.h"
#include "rendering/RenderInline.h"

#include "WebKitDriver.h"

#include "JavaBindings.h"

#include <stdio.h>
#include <stdlib.h>

static jfieldID g_nativeClass;
using namespace WebCore;

#define to_string(env, str) (env->GetStringChars(str, NULL))
#define to_window_handle(drv) (String::number((jlong)(drv)))


static bool frameIsLoading(Frame *frame)
{
    if (frame->loader()->isLoading()) {
        return true;
    }
    FrameLoaderClientHl *client = (FrameLoaderClientHl*)(frame->loader()->client());
    if (client->inRedirect()) {
        return true;
    }
    int count = frame->tree()->childCount();
    for (int i = 0; i < count; i++) {
        if (frameIsLoading(frame->tree()->child(i))) {
            return true;
        }
    }
    return false;
}


static bool waitSingleFrame(Frame *frame)
{
    while (Headless::processTimer() && frameIsLoading(frame)) {
        WTFLog(&LogLoading, "Wait for loaded frame\n");
    };
    // TODO: return frame loading result - true if loaded successfully, false otherwise
    return true;
}


static void waitAllFrames(Page *skipPage)
{
    const HashSet<Page*>& pages = PageGroup::pageGroup("headless")->pages();
    HashSet<Page*>::const_iterator end = pages.end();
    for (HashSet<Page*>::const_iterator it = pages.begin(); it != end; ++it) {
        Page* p = *it;
        if (p != skipPage) {
            waitSingleFrame(p->mainFrame());
        }
    }
}


static bool waitFrameLoaded(Frame *frame)
{
    if (!frame) {
        return true;
    }
    frame = frame->tree()->top();
    bool res = waitSingleFrame(frame);
    waitAllFrames(frame->page());

    return res;
}


static void mouseEvent(AtomicString& eventType, Element* element, int x = 0, int y = 0)
{
    PassRefPtr<AbstractView> view = element->document()->defaultView();
    PassRefPtr<Element> target(element);
    PassRefPtr<MouseEvent> evt = MouseEvent::create();
    evt.get()->initMouseEvent(eventType, true, true, view,
        1, 0, 0, x, y, false, false, false, false, 0, target);
    element->dispatchEvent(evt);
    Headless::processExpiredTimers();
}


static bool keyEvent(PlatformKeyboardEvent::Type eventType, UChar key, int modifiers, Element* element, bool preventDefault=0)
{
    PlatformKeyboardEvent evt(eventType, key, modifiers);
    RefPtr<KeyboardEvent> keyboardEvent = KeyboardEvent::create(evt, element->document()->defaultView());
    if (preventDefault) {
        keyboardEvent->preventDefault();
    }
    return element->dispatchEvent(keyboardEvent);
}


WebCore::String getProperty(Element* element, WebCore::String name)
{
    if (element == NULL || !element->isStyledElement()) {
        return String("");
    }
    Headless::processExpiredTimers();
    RefPtr<CSSComputedStyleDeclaration> style = computedStyle(element);
    String str = "";
    if (style) {
        str = style->getPropertyValue(cssPropertyID(name));
    }
    return str;
}


static IntRect getBoundingBoxSize(Node* node)
{
    if (node->renderer()) {
#if ENABLE(SVG)
        if (node->isSVGElement()) {
            IntRect res = IntRect(node->renderer()->objectBoundingBox());
            // FIXME there is a missing initialization of some variable in
            // SVG so during the first call it returns 0. Later it works OK
            // We can leave it for now since SVG is not crucial.
            if (!res.width() && !res.height()) {
                return IntRect(1, 1, 1, 1);
            }
            return res;
        }
#endif
        return node->getRect();
    }
    return IntRect(0, 0, 0, 0);
}


static bool isVisible(Node* node, bool zeroSizeInvisible = true, bool start = true, bool childVisibility = false)
{
    if (!node) {
        return childVisibility;
    }
    bool started = start;
    bool visible = childVisibility;
    bool isNone = false;

    Element *element = (Element*)node;
    // Probably it's better to use renderer to check visibility, but currently
    // we have an issue with selectors they does not have renderer
    if (node->isElementNode()) {
        started = false;
        IntRect rect = getBoundingBoxSize(node);
        // magic Title tag which is expected to be visible despite display=none
        if (node->nodeName() == "TITLE") {
            return true;
        }
        else if (getProperty((Element*)node, String("display")) == "none") {
            visible =  false;
            isNone = true;
        }
        else if (zeroSizeInvisible && node->renderer() && !(rect.height() && rect.width())) {
            RenderBoxModelObject* render = (RenderBoxModelObject*)node->renderer();
            visible = false;
        }
        else if (getProperty((Element*)node, String("visibility")) == "visible") {
            visible = true;
        }
        else if (getProperty((Element*)node, String("visibility")) == "hidden") {
            visible = false;
        }
    }
    if (!start && !isNone) {
        visible = childVisibility;
    }
    return isVisible(node->parentNode(), zeroSizeInvisible, started, visible);
}


jobject createWebDriverException(JNIEnv* env, const String& errorMessage)
{
    jclass objClass = env->FindClass("org/openqa/selenium/WebDriverException");
    jmethodID cid = env->GetMethodID(objClass, "<init>", "(Ljava/lang/String;)V");
    jstring message = env->NewString(errorMessage.characters(), errorMessage.length());
    jobject result = env->NewObject(objClass, cid, message);
    env->DeleteLocalRef(objClass);
    return result;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_create(JNIEnv *env, jobject obj, jstring userAgent)
{
    jlong jresult = 0;
    String userAgentStr;
    if (userAgent) {
        userAgentStr = to_string(env, userAgent);
    }
    WebKitDriver *driver = new WebKitDriver(userAgentStr);
    jresult = (jlong)driver;
    return jresult;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_destroy(JNIEnv *env, jobject obj, jlong ref)
{
    jlong jresult = 0;
    WebKitDriver *drv = (WebKitDriver*)ref;
    if (drv) {
        delete drv;
        jresult = 1;
    }
    return jresult;
}


JNIEXPORT jboolean JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setDatabaseEnabled(JNIEnv *env, jobject obj, jlong ref, jboolean enable)
{
    WebKitDriver *drv = (WebKitDriver*)ref;
    return drv->setDatabaseEnabled(enable);
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_get(JNIEnv *env, jobject obj, jlong ref, jstring url)
{
    WebKitDriver *drv = (WebKitDriver*)ref;
    String urlString = to_string(env, url);
    KURL kurl = KURL(KURL(), urlString, WebCore::UTF8Encoding());
    // 'Get' logics implies main frame
    drv->SetFrame(drv->GetMainFrame());
    drv->GetMainFrame()->loader()->load(kurl, false);
    return waitFrameLoaded(drv->GetMainFrame());
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getDocument(JNIEnv *env, jobject obj, jlong ref)
{
    jlong jresult = 0;
    WebKitDriver *drv = (WebKitDriver*)ref;
    jresult = (jlong)(drv->GetFrame()->document()->documentElement());
    return jresult;
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getTitle(JNIEnv *env, jobject obj, jlong ref)
{
    WebKitDriver *drv = (WebKitDriver*)ref;
    WebCore::String str = drv->GetFrame()->document()->title();
    return env->NewString(str.characters(), str.length());
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getDOMDump(JNIEnv *env, jobject obj, jlong ref)
{
    WebKitDriver *drv = (WebKitDriver*)ref;

    Element *element = drv->GetFrame()->document()->documentElement();
    WebCore::String str;
    if (element && element->isHTMLElement()) {
        str = ((HTMLElement*)element)->innerHTML();
    }
    return env->NewString(str.characters(), str.length());
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getPageSource(JNIEnv *env, jobject obj, jlong ref)
{
    WebKitDriver *drv = (WebKitDriver*)ref;

    Element *element = drv->GetFrame()->document()->documentElement();
    WebCore::String str;
    if (element && element->isHTMLElement()) {
        if (drv->GetFrame()->loader()->responseMIMEType() == "text/plain") {
            str = ((HTMLElement*)element)->outerText();
        }
        else {
            str = ((HTMLElement*)element)->outerHTML();
        }
    }
    return env->NewString(str.characters(), str.length());
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getUrl(JNIEnv *env, jobject obj, jlong ref)
{
    WebKitDriver *drv = (WebKitDriver*)ref;
    WebCore::String str;
    KURL url = drv->GetFrame()->loader()->url();
    if (!url.isNull()) {
        str = url.string();
    }
    return env->NewString(str.characters(), str.length());
}


JNIEXPORT jboolean JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_isJavascriptEnabled(JNIEnv *env, jobject obj, jlong ref)
{
    WebKitDriver *drv = (WebKitDriver*)ref;
    return drv->GetFrame()->page()->settings()->isJavaScriptEnabled();
}


JNIEXPORT void JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setJavascriptEnabled(JNIEnv *env, jobject obj, jlong ref, jboolean enable)
{
    WebKitDriver *drv = (WebKitDriver*)ref;
    drv->GetFrame()->page()->settings()->setJavaScriptEnabled(enable);
}


typedef WTF::HashSet<JSC::JSObject*> ObjectSet;

// Creating Java Object from JSValue, Nodes are converted to WebElements
// this function is called recursively in case of complicated object structures
jobject getObjectFromValue (JNIEnv *env, jobject driver, ScriptState *state, JSC::JSValue value, ObjectSet set, JSC::JSObject **cycle)
{
    jclass objClass;
    jmethodID cid;
    jobject result = NULL;
    using namespace JSC;

    JSLock lock(SilenceAssertionsOnly);
    if (*cycle) {
        return NULL;
    }
    if (value.isNull()) {
        objClass = env->FindClass("java/lang/Exception");
        cid = env->GetMethodID(objClass, "<init>", "()V");
        result = env->NewObject(objClass, cid);
    }
    else if (value.isUndefined()) {
    }
    else if (value.isNumber()) {
        if (!value.isDouble()) {
            objClass = env->FindClass("java/lang/Long");
            cid = env->GetMethodID(objClass, "<init>", "(J)V");
            jlong longResult = value.asInt32();
            result = env->NewObject(objClass, cid, longResult);
        }
        else {
            objClass = env->FindClass("java/lang/Double");
            cid = env->GetMethodID(objClass, "<init>", "(D)V");
            jdouble doubleResult = value.asDouble();
            result = env->NewObject(objClass, cid, doubleResult);
        }
        env->DeleteLocalRef(objClass);
    }
    else if (value.isBoolean()) {
        objClass = env->FindClass("java/lang/Boolean");
        cid = env->GetMethodID(objClass, "<init>", "(Z)V");
        result = env->NewObject(objClass, cid, value.isTrue());
        env->DeleteLocalRef(objClass);
    }
    else if (value.isString()) {
        WebCore::String strResult = value.getString(state);
        result = env->NewString(strResult.characters(), strResult.length());
    }
    else if (isJSByteArray(&state->globalData(), value)) {
        WTF::ByteArray* arr = asByteArray(value)->storage();
        jbyteArray byteArray = env->NewByteArray(arr->length());
        env->SetByteArrayRegion(byteArray, 0, arr->length(), (jbyte*)arr->data());
        result = (jobject)byteArray;
    }
    else if (value.isObject()) {
        JSObject *object = value.getObject();
        if (set.contains(object)) {
            *cycle = object;
            return NULL;
        }
        set.add(object);
        if (object->inherits(&JSArray::info)) {
            jobject arrayObj;
            objClass = env->FindClass("java/util/ArrayList");
            cid = env->GetMethodID(objClass, "<init>", "()V");
            result = env->NewObject(objClass, cid);
            jmethodID adding = env->GetMethodID(objClass, "add", "(Ljava/lang/Object;)Z");
            JSArray *array = static_cast<JSArray *>(object);
            for (int i = 0; i < array->length(); i++) {
                arrayObj = getObjectFromValue(env, driver, state, array->getIndex(i), set, cycle);
                if (result && adding && arrayObj)
                    env->CallBooleanMethod(result, adding, arrayObj);
            }
            env->DeleteLocalRef(objClass);
        }
        else if (object->inherits(&JSNodeList::s_info)) {
            objClass = env->FindClass("org/openqa/selenium/webkit/WebKitWebElement");
            cid = env->GetStaticMethodID(objClass, "createNodeList", "(Lorg/openqa/selenium/webkit/WebKitDriver;J)Ljava/util/List;");
            if (!objClass || !cid) {
                return NULL;
            }
            NodeList* nList = toNodeList(object);
            nList->ref();
            result = env->CallStaticObjectMethod(objClass, cid, driver, nList);
            env->DeleteLocalRef(objClass);
        }
        else if (object->inherits(&JSNode::s_info)) {
            objClass = env->FindClass("org/openqa/selenium/webkit/WebKitWebElement");
            cid = env->GetMethodID(objClass, "<init>", "(Lorg/openqa/selenium/webkit/WebKitDriver;J)V");
            WebCore::Node *node = toNode(object);
            node->ref();
            result = env->NewObject(objClass, cid, driver, node);
            env->DeleteLocalRef(objClass);
        }
        else if (object->inherits(&DateInstance::info)) {
            // TODO: Date processing
        }
        else {
            PropertyNameArray properties(state);
            object->getPropertyNames(state, properties);
            if (!properties.size()) {
                return NULL;
            }
            objClass = env->FindClass("java/util/HashMap");
            if (!objClass) {
                return NULL;
            }
            cid = env->GetMethodID(objClass, "<init>", "()V");
            if (!cid) {
                return NULL;
            }
            result = env->NewObject(objClass, cid);
            if (!result) {
                return NULL;
            }
            jmethodID adding = env->GetMethodID(objClass, "put",
                    "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
            if (!adding) {
                return NULL;
            }
            int size = properties.size();
            for (int i = 0; i < size; i++) {
                Identifier it = properties[i];
                if (object->propertyIsEnumerable(state, it)) {
                    jobject mapObject = getObjectFromValue(env, driver, state, object->get(state, it), set, cycle);
                    if (*cycle == object) {
                        *cycle = NULL;
                    }
                    if (!mapObject) {
                        break;
                    }
                    jobject key = env->NewString((it).data(), (it).size());
                    env->CallObjectMethod(result, adding, key, mapObject);
                }
            }
            env->DeleteLocalRef(objClass);
        }
    }
    else if (value.isGetterSetter()) {
    }
    else {
        printf ("Unknown return type\n");
    }
    return result;
}


// process raised JS exception, and return WebDriver exception after JS exec
jobject processException(JNIEnv* env, JSC::ExecState* exec, JSC::JSValue exception, bool report = false)
{
    if (!exec->hadException()) {
        return NULL;
    }
    JSC::UString errorMessage = exception.toString(exec);
    exec->clearException();
    WebCore::ExceptionBase* exceptionBase;
    if (exceptionBase = WebCore::toExceptionBase(exception)) {
        errorMessage = exceptionBase->message() + ":" + exceptionBase->description();
    }
    if (report) {
        printf ("Error message --%s\n", errorMessage.UTF8String().c_str());
    }
    jclass objClass = env->FindClass("java/lang/Exception");
    jmethodID cid = env->GetMethodID(objClass, "<init>", "()V");
    jobject result = env->NewObject(objClass, cid);
    env->DeleteLocalRef(objClass);

    return result;
}


// converting java objects to relevant JSValue's
JSC::JSValue parseArgument(JNIEnv* env, WebKitDriver* drv, jobject argument)
{
    using namespace JSC;
    JSValue result;

    ScriptState *state = drv->GetFrame()->script()->globalObject(mainThreadNormalWorld())->globalExec();
    jclass jstrClass = env->FindClass("java/lang/String");
    jclass webElementClass = env->FindClass("org/openqa/selenium/webkit/WebKitWebElement");
    jclass jboolClass = env->FindClass("java/lang/Boolean");
    jclass jintClass = env->FindClass("java/lang/Integer");
    jclass jlongClass = env->FindClass("java/lang/Long");
    jclass jdoubleClass = env->FindClass("java/lang/Double");
    if (!jstrClass || !webElementClass || !jboolClass || !jintClass ||
            !jlongClass || !jdoubleClass) {
        return JSValue();
    }
    jmethodID cid = env->GetMethodID(webElementClass, "getReference", "()J");
    jmethodID iid = env->GetMethodID(jintClass, "longValue", "()J");
    jmethodID lid = env->GetMethodID(jlongClass, "longValue", "()J");
    jmethodID did = env->GetMethodID(jdoubleClass, "doubleValue", "()D");
    jmethodID bid = env->GetMethodID(jboolClass, "booleanValue", "()Z");
    JSDOMGlobalObject* globalObject = toJSDOMGlobalObject(drv->GetFrame()->document(), mainThreadNormalWorld());

    if (env->IsInstanceOf(argument, jstrClass)) {
        const char *str = env->GetStringUTFChars(*(jstring*)&argument, NULL);
        result = jsString(state, WebCore::String(str));
    }
    else if (env->IsInstanceOf(argument, webElementClass)) {
        WebCore::Node* node = (WebCore::Node*)env->CallLongMethod(argument, cid);
        result = toJS(state, globalObject, node);
    }
    else if (env->IsInstanceOf(argument, jlongClass)) {
        long arg = env->CallLongMethod(argument, lid);
        result = jsNumber(state, arg);
    }
    else if (env->IsInstanceOf(argument, jintClass)) {
        long arg = env->CallLongMethod(argument, iid);
        result = jsNumber(state, arg);
    }
    else if (env->IsInstanceOf(argument, jboolClass)) {
        bool arg = env->CallBooleanMethod(argument, bid);
        result = jsBoolean(arg);
    }
    else if (env->IsInstanceOf(argument, jdoubleClass)) {
        double arg = env->CallDoubleMethod(argument, did);
        result = jsNumber(state, arg);
    }
    else {
        // TODO: we assuming type checking is going through WebDriver so only correct types are present. Probably should move it here.
        jobjectArray jarrayArg = (jobjectArray)argument;
        JSArray *resArray=constructEmptyArray(state);
        for (int i=0; i<env->GetArrayLength(jarrayArg); i++) {
            JSValue jsArg = parseArgument(env, drv, env->GetObjectArrayElement(jarrayArg, i));
            resArray->push(state, jsArg);
        }
        result = JSValue(resArray);
    }

    env->DeleteLocalRef(jstrClass);
    env->DeleteLocalRef(webElementClass);
    env->DeleteLocalRef(jboolClass);
    env->DeleteLocalRef(jintClass);
    env->DeleteLocalRef(jlongClass);
    env->DeleteLocalRef(jdoubleClass);

    return result;
}


JNIEXPORT jobject JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_evaluateJS(JNIEnv *env, jobject obj, jobject driver, jlong ref, jobjectArray argv)
{
    using namespace JSC;
    WebKitDriver *drv = (WebKitDriver*)ref;
    ScriptController *proxy;
    if ((drv != NULL) && (drv->GetFrame() != NULL)) {
        proxy = drv->GetFrame()->script();
    }
    else {
        return NULL;
    }
    int lineNumber = 3;

    Headless::processExpiredTimers();
    // creating Argument buffer to pass it to function creation function farther
    ScriptState *state = proxy->globalObject(mainThreadNormalWorld())->globalExec();
    MarkedArgumentBuffer args;
    MarkedArgumentBuffer funcArgs;
    int i;
    for (i=0; i<env->GetArrayLength(argv)-1; i++) {
        jobject argument = env->GetObjectArrayElement(argv, i);
        args.append(parseArgument(env, drv, env->GetObjectArrayElement(argv, i)));
    }
    funcArgs.append(parseArgument(env, drv, env->GetObjectArrayElement(argv, i)));

    // creating 'f' function it's wrapper around our Java script code
    WebCore::String functionName("f");
    JSC::JSObject* jsFunctionObj = JSC::constructFunction(
            state, funcArgs, Identifier(state, functionName), UString(""), lineNumber);
    if (state->hadException() || !jsFunctionObj) {
        return processException(env, state, state->exception());
    }
    JSFunction *jsFunction = static_cast<JSFunction*>(jsFunctionObj);

    // calling f function, we are getting result of its execution as well
    // as error state (exception)
    JSC::JSValue jsValue = jsFunction->call(state, state->globalThisValue(), args);
    if (state->hadException() || !jsValue) {
        return processException(env, state, state->exception());
    }

    // waiting for unfinished tasks (including geolocation)
    waitFrameLoaded(drv->GetFrame());
#if ENABLE(CLIENT_BASED_GEOLOCATION)
    while (drv->GetGeolocationClient()->isBusy() && Headless::processTimer())
        // waiting for Geolocation
        ;
#endif
    ObjectSet set;
    // cycle is used for cycle detection, currently it doesn't do much since
    // we don't have such structures, but we could meet them in future
    JSC::JSObject* cycle = NULL;
    return getObjectFromValue(env, driver, state, jsValue, set, &cycle);
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getElementById(JNIEnv *env, jobject obj, jlong ref, jstring query )
{
    WebKitDriver *drv = (WebKitDriver*)ref;
    WebCore::Document *doc = drv->GetFrame()->document();

    jlong jresult = 0 ;
    if(doc == NULL) {
        return jresult;
    }
    WebCore::String  strQuery = env->GetStringUTFChars(query, NULL);
    Headless::processExpiredTimers();
    Element* elem = doc->getElementById(strQuery);
    jresult = (jlong)elem;
    return jresult;
}

bool isBlockLevel(Node* element)
{
    if (element->isHTMLElement() && (
            element->hasTagName(HTMLNames::pTag) ||
            element->hasTagName(HTMLNames::h1Tag) ||
            element->hasTagName(HTMLNames::h2Tag) ||
            element->hasTagName(HTMLNames::h3Tag) ||
            element->hasTagName(HTMLNames::h4Tag) ||
            element->hasTagName(HTMLNames::h5Tag) ||
            element->hasTagName(HTMLNames::h6Tag) ||
            element->hasTagName(HTMLNames::dlTag) ||
            element->hasTagName(HTMLNames::divTag) ||
            element->hasTagName(HTMLNames::noscriptTag) ||
            element->hasTagName(HTMLNames::blockquoteTag) ||
            element->hasTagName(HTMLNames::formTag) ||
            element->hasTagName(HTMLNames::hrTag) ||
            element->hasTagName(HTMLNames::tableTag) ||
            element->hasTagName(HTMLNames::fieldsetTag) ||
            element->hasTagName(HTMLNames::addressTag) ||
            element->hasTagName(HTMLNames::ulTag) ||
            element->hasTagName(HTMLNames::olTag) ||
            element->hasTagName(HTMLNames::preTag) ||
            element->hasTagName(HTMLNames::brTag)
            )) {
        return true;
    }
    return false;
}


// This function collapses multiply whitespaces/nbrb/tabs/newlines in to a single whitespace.
WebCore::String collapseWhiteSpace(WebCore::String str)
{
    //TODO speed up the function, append arrays
    int len = 0;
    int i = 0;
    String buf;
    while (i < str.length()) {
        if (isSpaceOrNewline(str[i]) || str[i] == 160 || str[i] == '\t') {
            len++;
        }
        else {
            if (len) {
                if (len > 1) {
                    buf.append(" ");
                }
                else {
                    buf.append(str[i - 1]);
                }
                len = 0;
            }
            buf.append(str[i]);
        }
        i++;
    }
    return buf;
}


// input - input steam, temporary storage for text from inner elements
// outptut - stream with the final text after postprocessing
void getTextFromNode(Node* node, WebCore::String& input, WebCore::String& output)
{
    // TODO: preformatted text, helper functions
    if (!node || node->hasTagName(HTMLNames::scriptTag)) {
        return;
    }
    if (node->isTextNode() && isVisible(node, false)) {
        input += node->textContent();
    }
    // block level node is a /n in resulting text
    if (isBlockLevel(node)) {
        output += collapseWhiteSpace(input);
        input = "";
        if (output.length() && (output.right(1) != String("\n"))) {
            if (output.right(1) == " ") {
                output.remove(output.length() - 1);
            }
            output += "\n";
        }
    }

    // in order to comply with webdiriver requirements regarding inner text
    // we have to go through all child nodes and construct the string ourselves
    for (Node* child = node->firstChild(); child; child = child->nextSibling())
        getTextFromNode(child, input, output);

    // block level node is a /n in resulting text
    // we have to do it before and after child iteration since we may have a broken tag
    if (isBlockLevel(node)) {
        output += collapseWhiteSpace(input);
        input = "";
        if (output.length() && (output.right(1) != String("\n"))) {
            if (output.right(1) == " ") {
                output.remove(output.length() - 1);
            }
            output += "\n";
        }
    }
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getText(JNIEnv *env, jobject obj, jlong ref)
{
    WebCore::Element *element = (WebCore::Element*)ref;
    if (element == NULL) {
        return env->NewStringUTF("Element was not found. TODO thrown Exception");
    }
    Headless::processExpiredTimers();
    String str = "";
    String result = "";
    getTextFromNode(element, str, result);
    if (str.length() > 0) {
        result += collapseWhiteSpace(str);
    }
    return env->NewString((unsigned short *)result.characters(), result.length());
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setCookie(JNIEnv *env, jobject obj, jlong ref, jstring cookies)
{
    WebKitDriver *drv = (WebKitDriver*)ref;
    Frame *frame      = drv->GetFrame();
    Document *doc     = frame->document();

    if (!doc)
        return 0;

    if (frame->loader()->responseMIMEType() != "text/html")
        return 0;

    const String cookieStr(env->GetStringUTFChars(cookies, NULL));
    ExceptionCode ec = 0;

    doc->setCookie(cookieStr, ec);

    return ec ? 0 : 1;
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_cookies(JNIEnv *env, jobject obj, jlong ref)
{
    WebKitDriver *drv = (WebKitDriver*)ref;
    Frame *frame      = drv->GetFrame();
    Document *doc     = frame->document();
    jstring emptyStr  = env->NewStringUTF("");

    if (!doc) {
        return emptyStr;
    }
    ExceptionCode ec = 0;

    String cookieStr = doc->cookie(ec);

    if (ec) {
        return emptyStr;
    }
    return env->NewString((unsigned short *)cookieStr.characters(), cookieStr.length());
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getCookieJar(JNIEnv *env, jobject obj, jlong ref)
{
    KURL url;

    if (ref)
    {
        WebKitDriver *drv = (WebKitDriver*)ref;
        Frame *frame      = drv->GetFrame();
        Document *doc     = frame->document();
        jstring emptyStr  = env->NewStringUTF("");

        if (!doc) {
            return emptyStr;
        }
        // --- Do nothing if url should be but is empty ---
        url = doc->cookieURL();

        if (url.isEmpty()) {
            return emptyStr;
        }
    }

    String cookieStr = getCookieJar(url);

    return env->NewString((unsigned short *)cookieStr.characters(), cookieStr.length());
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setCookieJar(JNIEnv *env, jobject obj, jlong ref, jstring cookies)
{
    if (!ref) {
        return 0;
    }
    WebKitDriver *drv = (WebKitDriver*)ref;
    Frame *frame      = drv->GetFrame();
    Document *doc     = frame->document();

    if (!doc) {
        return 0;
    }
    // --- Do nothing if url should be but is empty ---
    const KURL url = doc->cookieURL();
    if (url.isEmpty()) {
        return 0;
    }
    const String rawCookie(env->GetStringUTFChars(cookies, NULL));

    setCookieJar(url, rawCookie);

    return 1;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_deleteCookie(JNIEnv *env, jobject obj, jlong ref, jstring cName)
{
    KURL url;
    String name;

    // --- Clear all cookies for all documents ---
    if (!ref)
    {
        deleteCookie(NULL, url, name);
        return 1;
    }

    // --- Delete cookies for given document ---
    WebKitDriver *drv = (WebKitDriver*)ref;
    Frame *frame      = drv->GetFrame();
    Document *doc     = frame->document();

    if (!doc) {
        return 0;
    }
    // --- Do nothing if url should be but is empty ---
    url = doc->cookieURL();
    if (url.isEmpty()) {
        return 0;
    }
    // --- For "all names" cName may be null or empty ---
    if (cName) {
        name = env->GetStringUTFChars(cName, NULL);
    }
    deleteCookie(NULL, url, name);

    return 1;
}


//element
JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getTagName(JNIEnv *env, jobject obj, jlong ref)
{
    WebCore::Element *element = (WebCore::Element*)ref;
    if (element == NULL) {
        return env->NewStringUTF("Element was not found. TODO thrown Exception");
    }
    Headless::processExpiredTimers();
    String str = element->tagName();
    return env->NewString((unsigned short *)str.characters(), str.length());
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getAttribute(JNIEnv *env, jobject obj, jlong ref, jstring name)
{
    WebCore::Element *element = (WebCore::Element*)ref;
    if (element == NULL)
        return env->NewStringUTF("Element was not found. TODO thrown Exception");

    WebCore::String  strQuery = to_string(env, name);
    Headless::processExpiredTimers();
    if (!element->hasAttribute(strQuery)) {
        return NULL;
    }
    String str = element->getAttribute(strQuery);
    return env->NewString((unsigned short *)str.characters(), str.length());
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getProperty(JNIEnv *env, jobject obj, jlong ref, jstring name)
{
    Element *element = (Element*)ref;
    String str = getProperty(element, to_string(env, name));
    if (!str.length()) {
        return NULL;
    }
    return env->NewString((unsigned short *)str.characters(), str.length());
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getValue(JNIEnv *env, jobject obj, jlong ref)
{
    WebCore::Element *element = (WebCore::Element*)ref;
    if (!element) {
        return 0;
    }
    String str;
    Headless::processExpiredTimers();
    HTMLInputElement *inputElement = (HTMLInputElement*)toInputElement(element);
    if (!inputElement) {
        if (element->nodeName() == "TEXTAREA") {
            str = ((HTMLTextAreaElement*)element)->value();
        }
        else {
            return 0;
        }
    }
    else {
        // Special handling of FILE elements - return full file path
        if (inputElement->inputType() == HTMLInputElement::FILE) {
            FileList *fl = inputElement->files();
            if (!fl->isEmpty()) {
                str = fl->item(0)->path();
            }
        }
        else {
            str = inputElement->value();
        }
    }
    return env->NewString((unsigned short *)str.characters(), str.length());
}


static void releaseModifiers(Element* element, int modifiers)
{
    if (modifiers & PlatformKeyboardEvent::ShiftKey) {
        keyEvent(PlatformKeyboardEvent::KeyUp, UNICODE_SHIFT, 0, element);
    }
    if (modifiers & PlatformKeyboardEvent::CtrlKey) {
        keyEvent(PlatformKeyboardEvent::KeyUp, UNICODE_CONTROL, 0, element);
    }
    if (modifiers & PlatformKeyboardEvent::AltKey) {
        keyEvent(PlatformKeyboardEvent::KeyUp, UNICODE_ALT, 0, element);
    }
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_sendKeys(JNIEnv *env, jobject obj, jlong ref, jstring val)
{
    static String upperNumerics = "~!@#$%^&*()_+{}:\"<>?|~";
    WebCore::Element *element = (WebCore::Element*)ref;
    if (element == NULL) {
        return 0;
    }
    element->focus();
    String s = to_string(env, val);
    HTMLInputElement *inputElement = (HTMLInputElement*)toInputElement(element);
    if (inputElement) {
        // Filename value can not be changes with sendKeys, because of platform-specific
        // file selection dialog. Treat it separately.
        if (inputElement->inputType() == HTMLInputElement::FILE) {
            // Only single file selection for now.
            // TODO: sendKeys semantics for selecting multiple files TBD
            Vector<String> v(1);
            v[0]=s;
            inputElement->setFileListFromRenderer(v);
            element->dispatchEvent(Event::create(eventNames().changeEvent, true, false));
            Headless::processExpiredTimers();
            return 1;
        }
    }

    if (element->nodeName() == "TEXTAREA") {
        element->document()->frame()->selection()->modify(SelectionController::MOVE, SelectionController::FORWARD, DocumentBoundary, true);
    }

    int modifiers = 0;
    bool local_shift;
    for (int i = 0; i < s.length(); i++) {
        UChar c = s[i];
        // Handle modifier keys here, as they act for the whole key sequence
        switch(c) {
            case UNICODE_SHIFT:
                keyEvent(PlatformKeyboardEvent::RawKeyDown, c, modifiers, element);
                modifiers |= PlatformKeyboardEvent::ShiftKey;
                break;
            case WebCore::UNICODE_CONTROL:
                keyEvent(PlatformKeyboardEvent::RawKeyDown, c, modifiers, element);
                modifiers |= PlatformKeyboardEvent::CtrlKey;
                break;
            case WebCore::UNICODE_ALT:
                keyEvent(PlatformKeyboardEvent::RawKeyDown, c, modifiers, element);
                modifiers |= PlatformKeyboardEvent::AltKey;
                break;
            case UNICODE_NULL:
                releaseModifiers(element, modifiers);
                modifiers = 0;
                break;
            default:
                String lowerChar;
                lowerChar.append(c);
                local_shift = false;
                if (lowerChar.lower()[0] != c || upperNumerics.contains(c)) {
                    local_shift = (modifiers & PlatformKeyboardEvent::ShiftKey) == 0;
                }
                if (local_shift) {
                    keyEvent(PlatformKeyboardEvent::RawKeyDown, UNICODE_SHIFT, modifiers, element);
                    modifiers |= PlatformKeyboardEvent::ShiftKey;
                }
                bool ok = keyEvent(PlatformKeyboardEvent::RawKeyDown, c, modifiers, element);
                keyEvent(PlatformKeyboardEvent::Char, c, modifiers, element, !ok);
                keyEvent(PlatformKeyboardEvent::KeyUp, c, modifiers, element);

                if (local_shift) {
                    modifiers ^= PlatformKeyboardEvent::ShiftKey;
                    keyEvent(PlatformKeyboardEvent::KeyUp, UNICODE_SHIFT, modifiers, element);
                }
        }
    }
    releaseModifiers(element, modifiers);

    Headless::processExpiredTimers();
    waitFrameLoaded(element->document()->frame());
    return 1;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setValue(JNIEnv *env, jobject obj, jlong ref, jstring val)
{
    WebCore::Element *element = (WebCore::Element*)ref;
    if (element == NULL) {
        return 0;
    }
    element->focus();

    WebCore::InputElement *inputElement = toInputElement(element);
    if (!inputElement) {
        if (element->nodeName() == "TEXTAREA") {
            ((HTMLTextAreaElement*)element)->setValue(to_string(env, val));
            element->dispatchEvent(Event::create(eventNames().changeEvent, true, false));
            Headless::processExpiredTimers();
            return 1;
        }
    }
    else {
        inputElement->setValue(to_string(env, val), true);
        element->dispatchEvent(Event::create(eventNames().changeEvent, true, false));
        Headless::processExpiredTimers();
        return 1;
    }

    element->dispatchEvent(Event::create(eventNames().changeEvent, true, false));
    Headless::processExpiredTimers();
    return 0;
}


//node
JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getElementsByTagName(JNIEnv *env, jobject obj, jlong ref, jstring query)
{
    WebCore::Node *doc = (WebCore::Node*)ref;
    jlong jresult = 0 ;
    if (doc == NULL) {
        return jresult;
    }
    String strResult;
    WebCore::String  strQuery = to_string(env, query);
    Headless::processExpiredTimers();
    RefPtr<WebCore::NodeList> elements = doc->getElementsByTagName(strQuery);
    jresult = (jlong)elements.get();
    // Increase reference counter, so NodeList is alive after leaving the function
    elements.get()->ref();
    return jresult;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getElementsByName(JNIEnv *env, jobject obj, jlong ref, jstring query)
{
    WebCore::Node *doc = (WebCore::Node*)ref;
    jlong jresult = 0 ;
    if (doc == NULL) {
        return jresult;
    }
    WebCore::String  strQuery = to_string(env, query);
    Headless::processExpiredTimers();
    RefPtr<WebCore::NodeList> elements = doc->getElementsByName(strQuery);
    jresult = (jlong)elements.get();
    // Increase reference counter, so NodeList is alive after leaving the function
    elements.get()->ref();
    return jresult;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getElementsByXpath(JNIEnv *env, jobject obj, jlong ref, jstring query)
{
    Node *context = (Node*)ref ;
    jlong jresult = 0 ;
    if (context == NULL) {
        return jresult;
    }
    RefPtr<NodeList> nodes;
    Vector<RefPtr<Node> > nodevector;

    ExceptionCode ec = 0;

    const String xpath = to_string(env, query);

    Headless::processExpiredTimers();
    PassRefPtr<XPathResult> xpathResult =
        context->document()->evaluate(xpath,
        context,
        0, // namespace
        XPathResult::ORDERED_NODE_ITERATOR_TYPE,
        0, // XPathResult object
        ec);
    if (!xpathResult.get()) {
        return 0;
    }
    Node* node;
    while (0 != (node = xpathResult->iterateNext(ec))) {
        nodevector.append(node);
    }
    nodes = StaticNodeList::adopt(nodevector);
    jresult = (jlong)nodes.get();
    // Increase reference counter, so NodeList is alive after leaving the function
    nodes.get()->ref();
    return jresult;
}


//NodeList
JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_nodeListLength(JNIEnv *env, jobject obj, jlong ref)
{
    NodeList *list = (NodeList*)ref;
    return list ? list->length() : -1;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_nodeListGet(JNIEnv *env, jobject obj, jlong ref, jint i)
{
    jlong jresult = 0 ;
    NodeList *list = (NodeList*)ref;
    if (!list) {
        return 0;
    }
    Node* elem = list->item(i);
    jresult = (jlong)elem;
    return jresult;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_nodeListRelease(JNIEnv *env, jobject obj, jlong ref)
{
    NodeList* list = (NodeList*)ref;
    if (list) {
        list->deref();
    }
    return 1;
}


JNIEXPORT void JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_goBack(JNIEnv *env, jobject obj, jlong ref)
{
    WebKitDriver *drv = (WebKitDriver*)ref;
    drv->GoBack();
}


JNIEXPORT void JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_goForward(JNIEnv *env, jobject obj, jlong ref)
{
    WebKitDriver *drv = (WebKitDriver*)ref;
    drv->GoForward();
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_refresh(JNIEnv *env, jobject obj, jlong ref)
{
    WebKitDriver *drv = (WebKitDriver*)ref;
    drv->Reload();
    return waitFrameLoaded(drv->GetFrame());
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_submit(JNIEnv *env, jobject obj, jlong ref)
{
    jlong jresult = 0;
    Element *element = (Element*)ref;
    if (!element || !element->isHTMLElement()) {
        return jresult;
    }
    HTMLFormElement *form = 0;
    // Weird, but form() method implementation looks for form starting from parent node.
    // Thus, need to check for form element manually.
    if (element->nodeName() == "FORM") {
        form = (HTMLFormElement*)element;
    }
    else {
        form = ((HTMLElement*)element)->form();
        if (!form) {
            return jresult;
        }
    }
    form->prepareSubmit(0);
    Headless::processExpiredTimers();
    waitFrameLoaded(element->document()->frame());
    jresult = 1;
    return jresult;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_click(JNIEnv *env, jobject obj, jlong ref)
{
    jlong jresult = 0;
    Element *element = (Element*)ref;
    if (!element) {
        return jresult;
    }
    mouseEvent(eventNames().mouseoverEvent, element);
    mouseEvent(eventNames().mousemoveEvent, element);
    mouseEvent(eventNames().mousedownEvent, element);
    if (element->isFocusable()) {
        element->focus();
    }
    else {
        // If we click on an element which can not be focused, remve
        // focus from currently focused element.
        Element *focused = (Element*)element->document()->focusedNode();
        if (focused && element != focused)
            focused->blur();
    }
    mouseEvent(eventNames().mouseupEvent, element);
    mouseEvent(eventNames().clickEvent, element);
    waitFrameLoaded(element->document()->frame());
    jresult = 1;
    return jresult;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_reset(JNIEnv *env, jobject obj, jlong ref)
{
    jlong jresult = 0;
    Element *element = (Element*)ref;
    if (!element || !element->isHTMLElement() || ! toInputElement(element)) {
        return jresult;
    }
    ((HTMLInputElement*)element)->reset();
        element->dispatchEvent(Event::create(eventNames().changeEvent, true, false));
        Headless::processExpiredTimers();
    jresult = 1;
    return jresult;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_toggle(JNIEnv *env, jobject obj, jlong ref)
{
    jlong jresult = -1;
    Element *element = (Element*)ref;
    if (!element || !element->isHTMLElement()) {
        return jresult;
    }
    if (toInputElement(element)) {
        HTMLInputElement *input = static_cast<HTMLInputElement*>(element);
        if (input->inputType() == HTMLInputElement::CHECKBOX) {
            input->setChecked( ! input->checked() );
            element->dispatchEvent(Event::create(eventNames().changeEvent, true, false));
            jresult = input->checked();
        }
    }
    else if (toOptionElement(element)) {
        HTMLOptionElement *option = static_cast<HTMLOptionElement*>(element);
        HTMLSelectElement *select = option->ownerSelectElement();
        if (select->multiple()) {
            option->setSelected( ! option->selected() );
            option->dispatchEvent(Event::create(eventNames().changeEvent, true, false));
            jresult = option->selected();
        }
    }
    else {
        return -1;
    }
    waitFrameLoaded(element->document()->frame());

    return jresult;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_focus(JNIEnv *env, jobject obj, jlong ref)
{
    Element *element = (Element*)ref;
    if (!element || !element->isHTMLElement()) {
        return 0;
    }
    element->focus();
    Headless::processExpiredTimers();
    return 1;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_selected(JNIEnv *env, jobject obj, jlong ref)
{
    jlong jresult = -1;
    Element *element = (Element*)ref;
    Headless::processExpiredTimers();
    if (toInputElement(element)) {
        HTMLInputElement *input = static_cast<HTMLInputElement*>(element);
        jresult = input->checked();
    }
    else if (toOptionElement(element)) {
        HTMLOptionElement *option = static_cast<HTMLOptionElement*>(element);
        jresult = option->selected();
    }

    return jresult;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setSelected(JNIEnv *env, jobject obj, jlong ref)
{
    Element *element = (Element*)ref;
    bool changed = false;
    if (toInputElement(element)) {
        HTMLInputElement *input = static_cast<HTMLInputElement*>(element);
        if (!input->checked()) {
            input->setChecked(true);
            changed = true;
        }
    }
    else if (toOptionElement(element)) {
        HTMLOptionElement *option = static_cast<HTMLOptionElement*>(element);
        if (!option->selected()) {
            option->setSelected(true);
            changed = true;
        }
    }
    else {
        return -1;
    }

    if (changed) {
        element->dispatchEvent(Event::create(eventNames().changeEvent, true, false));
        waitFrameLoaded(element->document()->frame());
    }

    return 0;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_optionIndex(JNIEnv *env, jobject obj, jlong ref)
{
    Element *element = (Element*)ref;
    if (!element || !isOptionElement(element)) {
        return -1;
    }
    return ((HTMLOptionElement*)element)->index();
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_stale(JNIEnv *env, jobject obj, jlong ref)
{
    Element *element = (Element*)ref;
    if (!element) {
        return -1;
    }
    if (!element->inDocument()) {
        return 1;
    }
    if (!element->attached()) {
        return 1;
    }
    // TODO: add more checks here
    return 0;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_activeElement(JNIEnv *env, jobject obj, jlong ref)
{
    jlong jresult = 0 ;
    WebKitDriver *drv = (WebKitDriver*)ref;
    if (!drv) {
        return jresult;
    }
    Headless::processExpiredTimers();
    Document *doc = drv->GetFrame()->document();
    Node *node = doc->focusedNode();
    if (!node) {
        RefPtr<WebCore::NodeList> list = doc->getElementsByTagName("body");
        if (list->length() > 0) {
            node = list->item(0);
        }
    }
    jresult = (jlong)node;
    return jresult;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_selectWindow(JNIEnv *env, jobject obj, jlong ref, jstring name)
{
    jlong jresult = 0;
    bool ok = false;
    WebKitDriver *drv = (WebKitDriver*)ref;
    String  windowName = to_string(env, name);
    WebKitDriver* ptr = (WebKitDriver*)(long)(windowName.toInt64(&ok));

    const HashSet<Page*>& pages = PageGroup::pageGroup("headless")->pages();
    HashSet<Page*>::const_iterator end = pages.end();
    Page *found = 0;
    for (HashSet<Page*>::const_iterator it = pages.begin(); it != end; ++it) {
        Page* p = *it;
        if (ok) {
            FrameLoaderClientHl *client = (FrameLoaderClientHl*)(p->mainFrame()->loader()->client());
            if (ptr == client->getDriver()) {
                found = p;
                break;
            }
        }
        if (windowName == p->mainFrame()->tree()->name().string()) {
            found = p;
            break;
        }
    }
    if (found) {
        FrameLoaderClientHl *client = (FrameLoaderClientHl*)(found->mainFrame()->loader()->client());
        WebKitDriver *drv = client->getDriver();
        if (drv) {
            jresult = (jlong)drv;
        }
    }
    else {
    }

    return jresult;
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getWindowHandle(JNIEnv *env, jobject obj, jlong ref)
{
    WebKitDriver *drv = (WebKitDriver*)ref;
    WebCore::String str = to_window_handle(drv);
    return env->NewString(str.characters(), str.length());
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getAllWindowHandles(JNIEnv *env, jobject obj){
    const HashSet<Page*>& pages = PageGroup::pageGroup("headless")->pages();
    HashSet<Page*>::const_iterator end = pages.end();
    WebCore::String str;
    int i = 0;
    for (HashSet<Page*>::const_iterator it = pages.begin(); it != end; ++it, i++) {
        Page* p = *it;
        FrameLoaderClientHl *client = (FrameLoaderClientHl*)p->mainFrame()->loader()->client();
        WebKitDriver *next = client->getDriver();
        if (next) {
            if (i) {
                str.append(',');
            }
            str.append(to_window_handle(next));
        }
    }
    return env->NewString(str.characters(), str.length());
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_selectFrameByName(JNIEnv *env, jobject obj, jlong ref, jstring name)
{
    jlong jresult = 0;
    WebKitDriver *drv = (WebKitDriver*)ref;
    String  frameName = to_string(env, name);

    Vector<String> list;
    frameName.split(".", list);
    int count = list.size();
    bool ok = false;
    Frame *frame = drv->GetMainFrame();
    for (int i = 0; i < count; i++) {
        int idx = list[i].toUInt(&ok);
        if (ok) {
            frame = frame->tree()->child(idx);
        }
        else {
            frame = frame->tree()->child(list[i]);
        }
        if (!frame) {
            return jresult;
        }
    }
    drv->SetFrame(frame);
    jresult = 1;

    return jresult;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_selectFrameByIdx(JNIEnv *env, jobject obj, jlong ref, jlong idx)
{
    jlong jresult = 0;
    WebKitDriver *drv = (WebKitDriver*)ref;
    Frame *frame = drv->GetMainFrame()->tree()->child(idx);
    if (!frame) {
        return jresult;
    }
    drv->SetFrame(frame);
    jresult = 1;
    return jresult;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_defaultContent(JNIEnv *env, jobject obj, jlong ref)
{
    jlong jresult = 0;
    WebKitDriver *drv = (WebKitDriver*)ref;
    drv->SetFrame(drv->GetMainFrame());
    jresult = 1;
    return jresult;
}


JNIEXPORT jboolean JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_isVisible(JNIEnv *env, jobject obj, jlong ref)
{
    WebCore::Element *element = (WebCore::Element*)ref;
    return isVisible(element);
}


JNIEXPORT jobject JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getRect(JNIEnv *env, jobject obj, jlong ref)
{
    WebCore::Element *node = (WebCore::Element*)ref;
    IntRect r = node->getRect();
    /* Calculate coordinates relative to body coordinates */
    IntRect pr = node->document()->body()->getRect();
    jclass objClass = env->FindClass("java/awt/Rectangle");
    jmethodID cid = env->GetMethodID(objClass, "<init>", "(IIII)V");
    jobject result = env->NewObject(objClass, cid, r.x()-pr.x(), r.y()-pr.y(), r.width(), r.height());
    env->DeleteLocalRef(objClass);
    return result;
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_drag(JNIEnv *env,
    jobject obj, jlong ref, jint toX, jint toY, jint duration)
{
    jlong jresult = 0;
    Element *element = (Element*)ref;
    HTMLElement *htmlElement = (HTMLElement*)element;

    if (!element || !element->isHTMLElement() || !htmlElement->draggable()) {
        return jresult;
    }
    mouseEvent(eventNames().mousemoveEvent, element);
    mouseEvent(eventNames().mousedownEvent, element);
    mouseEvent(eventNames().dragEvent, element);

    // --- Delay ---
    const struct timespec delay = {duration / 1000, (duration % 1000) * 1000000};
    nanosleep(&delay, NULL);

    mouseEvent(eventNames().mousemoveEvent, element, toX, toY);
    mouseEvent(eventNames().mouseupEvent, element);
    mouseEvent(eventNames().dropEvent, element);

    jresult = 1;
    return jresult;
}


JNIEXPORT void JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setPosition(JNIEnv *env, jobject obj, jlong ref, jobject geolocation)
{
#if ENABLE(CLIENT_BASED_GEOLOCATION)
    WebKitDriver *drv = (WebKitDriver*)ref;

    jclass objClass = env->FindClass("org/openqa/selenium/html5/Location");
    jmethodID alid = env->GetMethodID(objClass, "getAltitude", "()D");
    jmethodID laid = env->GetMethodID(objClass, "getLatitude", "()D");
    jmethodID loid = env->GetMethodID(objClass, "getLongitude", "()D");
    double altitude = env->CallDoubleMethod(geolocation, alid);
    double latitude = env->CallDoubleMethod(geolocation, laid);
    double longitude = env->CallDoubleMethod(geolocation, loid);
    // we don't use timestamps, accuracy currently
    double timestamp = 0;
    double accuracy = 0;

    drv->GetGeolocationClient()->setPosition(GeolocationPosition::create(timestamp, latitude, longitude, accuracy, 
            true, altitude, false, 0, false, 0, false, 0));
    env->DeleteLocalRef(objClass);
#endif
}


JNIEXPORT jobject JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getPosition(JNIEnv *env, jobject obj, jlong ref)
{
    WebKitDriver *drv = (WebKitDriver*)ref;
    jobject result = 0;
#if ENABLE(CLIENT_BASED_GEOLOCATION)
    GeolocationPosition* geoPosition = drv->GetFrame()->page()->geolocationController()->lastPosition();

    jclass objClass = env->FindClass("org/openqa/selenium/html5/Location");
    jmethodID cid = env->GetMethodID(objClass, "<init>", "(DDD)V");
    result = env->NewObject(objClass, cid, geoPosition->latitude(), geoPosition->longitude(), geoPosition->altitude());
    env->DeleteLocalRef(objClass);
#endif
    return result;
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getAlertText(JNIEnv *env, jobject obj, jlong ref, jboolean clr)
{
    WebKitDriver *drv = (WebKitDriver*)ref;
    Frame *frame = drv->GetMainFrame();

    if (!frame) {
        return NULL;
    }
    Page *page = frame->page();
    if (!page) {
        return NULL;
    }
    if (frame != page->mainFrame()) {
        return NULL;
    }
    ChromeClientHl *client = static_cast<ChromeClientHl*>(page->chrome()->client());
    String &str = client->accessAlertText();

    if (str.isNull()) {
        return NULL;
    }
    String resStr = str;

    if (clr) {
        str = String();
    }
    return env->NewString((unsigned short *)resStr.characters(), resStr.length());
}


JNIEXPORT jboolean JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_online(JNIEnv *env, jobject obj)
{
    return networkStateNotifier().onLine();
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setOnline(JNIEnv *env, jobject obj, jboolean online)
{
    networkStateNotifier().networkStateChange(online);
    return 0;
}


#if ENABLE(DATABASE)
JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_openDatabase(JNIEnv *env, jobject obj, jlong ref, jstring name, jstring version, jstring displayName, jlong size)
{
    WebKitDriver* drv = (WebKitDriver*)ref;

    ExceptionCode code;
    PassRefPtr<Database> database = Database::openDatabase(drv->GetFrame()->document(), 
            to_string(env, name), to_string(env, version), to_string(env, displayName), size, code);
    Headless::processTimer();
    database->ref();
    return (jlong)database.get();
}


JNIEXPORT void JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_closeDatabase(JNIEnv *env, jobject obj, jlong ref)
{
    Database* database = (Database*)ref;
    if (!database) {
        database->close();
        Headless::processTimer();
        database->deref();
    }
}


// Parsing SQL arguments to SQLValues, every Number is converted to double
// since JS has only Number/String distinction
bool parseSQLArgument(JNIEnv *env, jobject obj, SQLValue &result)
{
    jclass jstrClass = env->FindClass("java/lang/String");
    jclass jintClass = env->FindClass("java/lang/Integer");
    jclass jlongClass = env->FindClass("java/lang/Long");
    jclass jdoubleClass = env->FindClass("java/lang/Double");
    
    jmethodID iid = env->GetMethodID(jintClass, "longValue", "()J");
    jmethodID lid = env->GetMethodID(jlongClass, "longValue", "()J");
    jmethodID did = env->GetMethodID(jdoubleClass, "doubleValue", "()D");

    bool parsingOK = true;
    if (env->IsInstanceOf(obj, jstrClass)) {
        result = SQLValue(to_string(env, *(jstring*)&obj));
    }
    else if (env->IsInstanceOf(obj, jintClass)) {
        result = SQLValue(env->CallIntMethod(obj, iid));
    }
    else if (env->IsInstanceOf(obj, jlongClass)) {
        result = SQLValue(env->CallLongMethod(obj, lid));
    }
    else if (env->IsInstanceOf(obj, jdoubleClass)) {
        result = SQLValue(env->CallDoubleMethod(obj, did));
    }
    else {
        parsingOK = false;
    }
    env->DeleteLocalRef(jstrClass);
    env->DeleteLocalRef(jintClass);
    env->DeleteLocalRef(jlongClass);
    env->DeleteLocalRef(jdoubleClass);
    return parsingOK;
}


jobject getObjectFromSQLValue(JNIEnv *env, const SQLValue &value)
{
    jclass jdoubleClass = 0;
    jmethodID cid = 0;
    jobject result = 0;
    switch (value.type()) {
        case SQLValue::NumberValue:
            jdoubleClass = env->FindClass("java/lang/Double");
            cid = env->GetMethodID(jdoubleClass, "<init>", "(D)V");
            result = env->NewObject(jdoubleClass, cid, value.number());
            env->DeleteLocalRef(jdoubleClass);
            return result;
        case SQLValue::StringValue:
            return env->NewString(value.string().characters(), value.string().length());
        case SQLValue::NullValue:
        default:
            return 0;
    }
}


// creating Java object from set of SQLValues, we have only 2 data tpyes Numeric and String
// This is limitation inherited from JS
jobject getObjectFromSQLSetRowList(JNIEnv *env, SQLResultSetRowList* set)
{
    jclass listClass = env->FindClass("java/util/ArrayList");
    jclass rowsClass = env->FindClass("org/openqa/selenium/html5/ResultSetRows");
    jmethodID lcid = env->GetMethodID(listClass, "<init>", "()V");
    jmethodID rcid = env->GetMethodID(rowsClass, "<init>", "(Ljava/util/List;)V");
    jmethodID adding = env->GetMethodID(listClass, "add", "(Ljava/lang/Object;)Z");
    jobject result = env->NewObject(listClass, lcid);
    jclass hashClass = env->FindClass("java/util/HashMap");
    jmethodID hcid = env->GetMethodID(hashClass, "<init>", "()V");
    jmethodID putting = env->GetMethodID(hashClass, "put",
            "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    if (result) {
        for (int i = 0; i < set->length(); i++) {
            jobject hash = env->NewObject(hashClass, hcid);
            for (int j = 0; j < set->columnNames().size(); j++) {
                jstring key = env->NewString(set->columnNames()[j].characters(), set->columnNames()[j].length());
                jobject mapObject = getObjectFromSQLValue(env, set->values()[i*set->columnNames().size() + j]);
                env->CallObjectMethod(hash, putting, key, mapObject);
            }
            env->CallBooleanMethod(result, adding, hash);
        }
    }
    jobject resultRows = env->NewObject(rowsClass, rcid, result);
    env->DeleteLocalRef(listClass);
    env->DeleteLocalRef(hashClass);
    env->DeleteLocalRef(rowsClass);
    return resultRows;
} 


JNIEXPORT jobject JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_executeSQL(JNIEnv *env, jobject obj, jlong ref, jlong dbref, jstring query, jobjectArray argv)
{
    WebKitDriver* drv = (WebKitDriver*)ref;
    Database* database = (Database*)dbref;
    
    Vector<SQLValue> argVector;
    for (int i = 0; i < env->GetArrayLength(argv); i++) {
        jobject argument = env->GetObjectArrayElement(argv, i);
        SQLValue value;
        if (parseSQLArgument(env, env->GetObjectArrayElement(argv, i), value)) {
            argVector.append(value);
        }
        else {
            return createWebDriverException(env, "Argument parse error");
        }
    }

    // Java Script transaction is created and passed to a database handler class
    // actuall SQL statement code is passed lately during callback on transaction initiation
    DatabaseTrackerClientHl* client = drv->GetSQLClient();
    PassRefPtr<SQLTransactionCallbackHl> transactionCallback = adoptRef(new SQLTransactionCallbackHl(client, to_string(env, query), argVector));
    PassRefPtr<SQLTransactionErrorCallbackHl> transactionErrorCallback = adoptRef(new SQLTransactionErrorCallbackHl(client));
    PassRefPtr<SQLSuccessCallback> successCallback = adoptRef(new SQLSuccessCallback(client));

    drv->SetBusyState(true, WebKitDriver::DATABASE);
    database->transaction(transactionCallback, transactionErrorCallback, successCallback, false);

    // waiting for success or error callback
    while (drv->IsBusy(WebKitDriver::DATABASE)) {
        Headless::processTimer();
    }

    if (drv->GetSQLClient()->isResultOK()) {
        // we are getting Result set data from interface here. It's basically an
        // atomic operation but since we work in a single thread here it's OK 
        WTFLog(&WebCore::LogStorageAPI, "Creating Result Set");
        jobject rowList =  getObjectFromSQLSetRowList(env, drv->GetSQLClient()->getResult());
        int rowsAffected = drv->GetSQLClient()->rowsAffected();
        int insertID = drv->GetSQLClient()->insertID();
        jclass objClass = env->FindClass("org/openqa/selenium/html5/ResultSet");
        jmethodID cid = env->GetMethodID(objClass, "<init>", "(IILorg/openqa/selenium/html5/ResultSetRows;)V");
        jobject result = env->NewObject(objClass, cid, insertID, rowsAffected, rowList);
        env->DeleteLocalRef(objClass);
        return result;
    }
    return createWebDriverException(env, drv->GetSQLClient()->getError()->message());
}
#endif //ENABLE(DATABASE)


JNIEXPORT jboolean JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_canPlayType
    (JNIEnv *env, jobject obj, jlong ref, jstring contentTypeStr)
{
    HTMLMediaElement *htmlMediaElement = (HTMLMediaElement*)ref;

    String cTypeStr = to_string(env, contentTypeStr);
    ContentType contentType(cTypeStr);

    return htmlMediaElement->player()->supportsType(contentType);
}


JNIEXPORT void JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_mediaPlay
    (JNIEnv *env, jobject obj, jlong ref, jboolean doPlay)
{
    HTMLMediaElement *htmlMediaElement = (HTMLMediaElement*)ref;

    if (doPlay) {
        htmlMediaElement->play(false);
    }
    else {
        htmlMediaElement->pause(false);
    }
}


JNIEXPORT jint JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getAppCacheStatus(JNIEnv *env, jobject obj, jlong ref)
{
    WebKitDriver *drv = (WebKitDriver*)ref;
#if ENABLE(OFFLINE_WEB_APPLICATIONS)
    DOMApplicationCache *cache = drv->GetMainFrame()->document()->domWindow()->applicationCache();
    if (cache) {
        return cache->status();
    }
#endif
    return -1;
}


JNIEXPORT jobject JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getAppCache(JNIEnv *env, jobject obj, jlong ref)
{
    WebKitDriver *drv = (WebKitDriver*)ref;

    // Create empty ArrayList
    jclass objClass = env->FindClass("java/util/ArrayList");
    jmethodID cid = env->GetMethodID(objClass, "<init>", "()V");
    jobject result = env->NewObject(objClass, cid);

#if ENABLE(OFFLINE_WEB_APPLICATIONS)
    DocumentLoader *loader = drv->GetMainFrame()->loader()->activeDocumentLoader();
    ApplicationCache *cache = ApplicationCacheGroup::cacheForMainRequest(loader->request(), loader);
    if (cache) {
        jobject entry;
        jclass entryClass = env->FindClass("org/openqa/selenium/html5/AppCacheEntry");
        jclass typeClass = env->FindClass("org/openqa/selenium/html5/AppCacheType");
        jmethodID typeMethod = env->GetStaticMethodID(typeClass, "valueOf", "(Ljava/lang/String;)Lorg/openqa/selenium/html5/AppCacheType;");
        jmethodID entryConstructor = env->GetMethodID(entryClass, "<init>", "(Lorg/openqa/selenium/html5/AppCacheType;Ljava/lang/String;Ljava/lang/String;)V");
        cid = env->GetMethodID(objClass, "add", "(Ljava/lang/Object;)Z");
        for(ApplicationCache::ResourceMap::const_iterator it = cache->begin(); it != cache->end(); ++it) {
            // Map WebKit ApplicationCacheResource type into WebDriver AppCacheType names
            const char *typeName = 0;
            switch (it->second->type()) {
                case ApplicationCacheResource::Master:
                    typeName = "MASTER";
                    break;
                case ApplicationCacheResource::Manifest:
                    typeName = "MANIFEST";
                    break;
                case ApplicationCacheResource::Explicit:
                    typeName = "EXPLICIT";
                    break;
                case ApplicationCacheResource::Fallback:
                    typeName = "FALLBACK";
                    break;
            }
        
            // If resource type can not be mapped to AppCacheType enum, just skip it
            if (!typeName) {
                continue;
            }
            // Get AppCacheType object, it will be passed to AppCacheEntry constructor
            jobject cacheType = env->CallStaticObjectMethod(typeClass, typeMethod, 
                    env->NewStringUTF(typeName));

            // Create AppCacheEntry object ...
            String url = it->second->url().string();
            String mimeType = it->second->response().mimeType();

            entry = env->NewObject(entryClass, entryConstructor, 
                    cacheType,
                    env->NewString(url.characters(), url.length()),
                    env->NewString(mimeType.characters(), mimeType.length())
            );

            // ... and put it to resulting list
            env->CallBooleanMethod(result, cid, entry);
        }
        env->DeleteLocalRef(entryClass);
        env->DeleteLocalRef(typeClass);
    }
#endif
    env->DeleteLocalRef(objClass);
    // Return ArrayList populated with CacheEntry objects
    return result;
}


static Storage *getStorage(WebKitDriver *drv, bool session)
{
    if (!drv) {
        return 0;
    }
    DOMWindow *win = drv->GetFrame()->domWindow();
    return (session ? win->sessionStorage() : win->localStorage());
}


JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_storageLength(JNIEnv *env, jobject obj, jlong ref, jboolean session)
{
    Storage *storage = getStorage((WebKitDriver*)ref, session);
    return storage ? (jlong)storage->length() : -1;
}


JNIEXPORT jboolean JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_storageClear(JNIEnv *env, jobject obj, jlong ref, jboolean session)
{
    Storage *storage = getStorage((WebKitDriver*)ref, session);
    if (storage) {
        storage->clear();
        return true;
    }
    return false;
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_storageKey(JNIEnv *env, jobject obj, jlong ref, jboolean session, jlong idx)
{
    Storage *storage = getStorage((WebKitDriver*)ref, session);
    if (storage) {
        String key = storage->key(idx);
        return env->NewString(key.characters(), key.length());
    }
    return 0;
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_storageGetValue(JNIEnv *env, jobject obj, jlong ref, jboolean session, jstring key)
{
    Storage *storage = getStorage((WebKitDriver*)ref, session);
    if (storage) {
        String keyStr = to_string(env, key);
        String val = storage->getItem(keyStr);
        return env->NewString(val.characters(), val.length());
    }
    return 0;
}


JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_storageSetValue(JNIEnv *env, jobject obj, jlong ref, jboolean session, jstring key, jstring value)
{
    Storage *storage = getStorage((WebKitDriver*)ref, session);
    if (storage) {
        String keyStr = to_string(env, key);
        String currentValue = storage->getItem(keyStr);
        ExceptionCode ec = 0;
        if (value) {
            String valueStr = to_string(env, value);
            storage->setItem(keyStr, valueStr, ec);
        }
        else {
            storage->removeItem(keyStr);
        }
        if (currentValue.isNull()) {
            return 0;
        }
        else {
            return env->NewString(currentValue.characters(), currentValue.length());
        }
    }
    return 0;
}
