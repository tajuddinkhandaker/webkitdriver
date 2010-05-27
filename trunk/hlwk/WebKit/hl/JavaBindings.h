#include <jni.h>

#ifndef _Included_com_example_mywebview_MyWebView
#define _Included_com_example_mywebview_MyWebView

extern "C" {
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_create(JNIEnv *env, jobject obj, jstring userAgent);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_destroy(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_get(JNIEnv *env, jobject obj, jlong ref, jstring url);
    JNIEXPORT jboolean JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setDatabaseEnabled(JNIEnv *env, jobject obj, jlong ref, jboolean enable);
    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getTitle(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getDOMDump(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getPageSource(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getUrl(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getDocument
    (JNIEnv *env, jobject obj, jlong ref);

    JNIEXPORT jboolean JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_isJavascriptEnabled(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT void JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setJavascriptEnabled(JNIEnv *env, jobject obj, jlong ref, jboolean enable);
    JNIEXPORT jobject JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_evaluateJS(JNIEnv *env, jobject obj, jobject driver, jlong ref, jobjectArray arguments);

    //Document
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getElementById
    (JNIEnv *env, jobject obj, jlong ref, jstring query);

    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setCookie(JNIEnv *env, jobject obj, jlong ref, jstring cookies);
    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_cookies(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getCookieJar(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setCookieJar(JNIEnv *env, jobject obj, jlong ref, jstring cookies);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_deleteCookie(JNIEnv *env, jobject obj, jlong ref, jstring cName);

    //Node
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getElementsByTagName
    (JNIEnv *env, jobject obj, jlong ref, jstring query);

    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getElementsByName
    (JNIEnv *env, jobject obj, jlong ref, jstring query);

    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getElementsByXpath
    (JNIEnv *env, jobject obj, jlong ref, jstring query);

    //NodeList
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_nodeListLength
    (JNIEnv *env, jobject obj, jlong ref);

    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_nodeListGet
    (JNIEnv *env, jobject obj, jlong ref,jint i);

    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_nodeListRelease(JNIEnv *env, jobject obj,jlong ref);


    //Element
    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getTagName
    (JNIEnv *env, jobject obj, jlong ref);

    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getAttribute
    (JNIEnv *env, jobject obj, jlong ref, jstring name);

    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getProperty(JNIEnv *env, jobject obj, jlong ref, jstring name);

    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getText
    (JNIEnv *env, jobject obj, jlong ref);

    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getValue
    (JNIEnv *env, jobject obj, jlong ref);

    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_sendKeys
    (JNIEnv *env, jobject obj, jlong ref, jstring val);

    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setValue
    (JNIEnv *env, jobject obj, jlong ref, jstring val);

    JNIEXPORT void JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_goBack(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT void JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_goForward(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_refresh(JNIEnv *env, jobject obj, jlong ref);

    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_submit(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_click(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_reset(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_toggle(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_focus(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_selected(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setSelected(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_optionIndex(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_stale(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_activeElement(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_selectFrameByName(JNIEnv *env, jobject obj, jlong ref, jstring name);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_selectFrameByIdx(JNIEnv *env, jobject obj, jlong ref, jlong idx);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_selectWindow(JNIEnv *env, jobject obj, jlong ref, jstring name);
    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getWindowHandle(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getAllWindowHandles(JNIEnv *env, jobject obj);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_defaultContent(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jboolean JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_isVisible(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_drag
    (JNIEnv *env, jobject obj, jlong ref, jint toX, jint toY, jint duration);
    JNIEXPORT jobject JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getRect(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getAlertText(JNIEnv *env, jobject obj, jlong ref, jboolean clr);

    // HTML 5
    JNIEXPORT jobject JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getPosition(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT void JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setPosition(JNIEnv *env, jobject obj, jlong ref, jobject geolocation);
    JNIEXPORT jboolean JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_online(JNIEnv *env, jobject obj);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_setOnline(JNIEnv *env, jobject obj, jboolean online);
    JNIEXPORT jboolean JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_canPlayType
        (JNIEnv *env, jobject obj, jlong ref, jstring contentTypeStr);
    JNIEXPORT void JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_mediaPlay
        (JNIEnv *env, jobject obj, jlong ref, jboolean doPlay);
    JNIEXPORT jint JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getAppCacheStatus(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jobject JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_getAppCache(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jobject JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_executeSQL(JNIEnv *env, jobject obj, jlong ref, jlong dbref, jstring query, jobjectArray argv);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_openDatabase(JNIEnv *env, jobject obj, jlong ref, jstring name, jstring version, jstring displayName, jlong size);
    JNIEXPORT void JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_closeDatabase(JNIEnv *env, jobject obj, jlong ref);
    JNIEXPORT jlong JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_storageLength(JNIEnv *env, jobject obj, jlong ref, jboolean session);
    JNIEXPORT jboolean JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_storageClear(JNIEnv *env, jobject obj, jlong ref, jboolean session);
    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_storageKey(JNIEnv *env, jobject obj, jlong ref, jboolean session, jlong idx);
    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_storageGetValue(JNIEnv *env, jobject obj, jlong ref, jboolean session, jstring key);
    JNIEXPORT jstring JNICALL Java_org_openqa_selenium_webkit_WebKitJNI_storageSetValue(JNIEnv *env, jobject obj, jlong ref, jboolean session, jstring key, jstring value);
}
#endif
