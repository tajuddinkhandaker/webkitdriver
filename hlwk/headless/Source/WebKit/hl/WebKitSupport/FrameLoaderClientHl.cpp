/*
 * Copyright (C) 2007 Kevin Ollivier <kevino@theolliviers.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
#include "config.h"
#include "FrameLoaderClientHl.h"
#include "FrameNetworkingContextHl.h"

#include <JavaScriptCore/JavaScript.h>
#include <JavaScriptCore/APICast.h>

#include "DocumentLoader.h"
#include "FocusController.h"
#include "FormState.h"
#include "Frame.h"
#include "FrameLoaderTypes.h"
#include "FrameView.h"
#include "FrameTree.h"
#include "PluginView.h"
#include "HTMLNames.h"
#include "HTMLFormElement.h"
#include "HTMLFrameOwnerElement.h"
#include "NetworkStateNotifier.h"
#include "NotImplemented.h"
#include "Page.h"
#include "PluginView.h"
#include "ProgressTracker.h"
#include "RenderPart.h"
#include "ResourceError.h"
#include "ResourceResponse.h"
#include "ScriptController.h"
#include "WindowFeatures.h"
#include "Chrome.h"
#include <wtf/PassRefPtr.h>
#include <wtf/RefPtr.h>

#include <stdio.h>

#include "WebKitDriver.h"
#include "WebKitDriverPrivate.h"

#include <semaphore.h>
#include <stdio.h>

// copied from WebKit/mac/Misc/WebKitErrors[Private].h
enum {
    WebKitErrorCannotShowMIMEType =                             100,
    WebKitErrorCannotShowURL =                                  101,
    WebKitErrorFrameLoadInterruptedByPolicyChange =             102,
    WebKitErrorCannotUseRestrictedPort = 103,
    WebKitErrorCannotFindPlugIn =                               200,
    WebKitErrorCannotLoadPlugIn =                               201,
    WebKitErrorJavaUnavailable =                                202,
};

enum wxProxyType {
    HTTP,
    Socks4,
    Socks4A,
    Socks5,
    Socks5Hostname
};

namespace WebCore {


FrameLoaderClientHl::FrameLoaderClientHl()
    : m_frame(0)
    , m_pluginView(0)
    , m_hasSentResponseToPlugin(false)
    , m_webFrame(0)
    , m_loading(false)
    , m_inRedirect(false)
    , m_userAgent("Mozilla/5.0 (Macintosh; U; Intel Mac OS X; en) AppleWebKit/418.9.1 (KHTML, like Gecko) Safari/419.3")
{
}


FrameLoaderClientHl::~FrameLoaderClientHl()
{
}

void FrameLoaderClientHl::setFrame(WebKitDriver *wframe, Frame *frame)
{
    m_webFrame = wframe;
    if (frame)
        m_frame = frame;
    else
        m_frame = wframe->priv->frame;
}

bool FrameLoaderClientHl::hasWebView() const
{
    notImplemented();
    return m_webFrame != NULL;
}

bool FrameLoaderClientHl::hasBackForwardList() const
{
    notImplemented();
    return true;
}


void FrameLoaderClientHl::resetBackForwardList()
{
    notImplemented();
}


bool FrameLoaderClientHl::provisionalItemIsTarget() const
{
    notImplemented();
    return false;
}

void FrameLoaderClientHl::makeRepresentation(DocumentLoader*)
{
    notImplemented();
}


void FrameLoaderClientHl::forceLayout()
{
    notImplemented();
}


void FrameLoaderClientHl::forceLayoutForNonHTML()
{
    notImplemented();
}


void FrameLoaderClientHl::updateHistoryForCommit()
{
    notImplemented();
}


void FrameLoaderClientHl::updateHistoryForBackForwardNavigation()
{
    notImplemented();
}


void FrameLoaderClientHl::updateHistoryForReload()
{
    notImplemented();
}


void FrameLoaderClientHl::updateHistoryForStandardLoad()
{
    notImplemented();
}


void FrameLoaderClientHl::updateHistoryForInternalLoad()
{
    notImplemented();
}


void FrameLoaderClientHl::updateHistoryAfterClientRedirect()
{
    notImplemented();
}


void FrameLoaderClientHl::setCopiesOnScroll()
{
    // apparently mac specific
    notImplemented();
}


LoadErrorResetToken* FrameLoaderClientHl::tokenForLoadErrorReset()
{
    notImplemented();
    return 0;
}


void FrameLoaderClientHl::resetAfterLoadError(LoadErrorResetToken*)
{
    notImplemented();
}


void FrameLoaderClientHl::doNotResetAfterLoadError(LoadErrorResetToken*)
{
    notImplemented();
}


void FrameLoaderClientHl::willCloseDocument()
{
    notImplemented();
}


void FrameLoaderClientHl::detachedFromParent2()
{
    notImplemented();
}


void FrameLoaderClientHl::detachedFromParent3()
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidHandleOnloadEvents()
{
    notImplemented();
}


void FrameLoaderClientHl::dispatchDidReceiveServerRedirectForProvisionalLoad()
{
    notImplemented();
}


void FrameLoaderClientHl::dispatchDidCancelClientRedirect()
{
    m_inRedirect = false;
}


void FrameLoaderClientHl::dispatchWillPerformClientRedirect(const KURL& url,
                                                            double interval,
                                                            double fireDate)
{
    // If redirect sheduled and it occur within a second - wait till it finishes
    if (interval < 1.0) {
        m_inRedirect = true;
    }
}


void FrameLoaderClientHl::dispatchDidChangeLocationWithinPage()
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidPushStateWithinPage()
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidReplaceStateWithinPage()
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidPopStateWithinPage()
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchWillClose()
{
    notImplemented();
}


void FrameLoaderClientHl::dispatchDidStartProvisionalLoad()
{
    notImplemented();
}


void FrameLoaderClientHl::dispatchDidReceiveTitle(const StringWithDirection& title)
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidChangeIcons(IconType)
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidCommitLoad()
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidFinishDocumentLoad()
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidFinishLoad()
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidFirstLayout()
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidFirstVisuallyNonEmptyLayout()
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchShow()
{
    notImplemented();
}


void FrameLoaderClientHl::cancelPolicyCheck()
{
    notImplemented();
}


void FrameLoaderClientHl::dispatchWillSubmitForm(FramePolicyFunction function,
                                                 PassRefPtr<FormState>)
{
    (m_frame->loader()->policyChecker()->*function)(PolicyUse);
}


void FrameLoaderClientHl::dispatchDidLoadMainResource(DocumentLoader*)
{
    notImplemented();
}


void FrameLoaderClientHl::revertToProvisionalState(DocumentLoader*)
{
    notImplemented();
}

void FrameLoaderClientHl::postProgressStartedNotification()
{
    notImplemented();
}

void FrameLoaderClientHl::postProgressEstimateChangedNotification()
{
    notImplemented();
}

void FrameLoaderClientHl::postProgressFinishedNotification()
{
    notImplemented();
}

void FrameLoaderClientHl::progressStarted()
{
    notImplemented();
}


void FrameLoaderClientHl::progressCompleted()
{
    notImplemented();
}


void FrameLoaderClientHl::setMainFrameDocumentReady(bool b)
{
    notImplemented();
    // this is only interesting once we provide an external API for the DOM
}


void FrameLoaderClientHl::willChangeTitle(DocumentLoader*)
{
    notImplemented();
}


void FrameLoaderClientHl::didChangeTitle(DocumentLoader *l)
{
    setTitle(l->title(), l->url());
}


void FrameLoaderClientHl::finishedLoading(DocumentLoader*)
{
    notImplemented();
}


bool FrameLoaderClientHl::canShowMIMEType(const String& MIMEType) const
{
    notImplemented();
    return true;
}

bool FrameLoaderClientHl::canShowMIMETypeAsHTML(const String& MIMEType) const
{
    notImplemented();
    return false;
}

bool FrameLoaderClientHl::representationExistsForURLScheme(const String& URLScheme) const
{
    notImplemented();
    return false;
}


String FrameLoaderClientHl::generatedMIMETypeForURLScheme(const String& URLScheme) const
{
    notImplemented();
    return String();
}


void FrameLoaderClientHl::frameLoadCompleted()
{
    notImplemented();
}

void FrameLoaderClientHl::saveViewStateToItem(HistoryItem*)
{
    notImplemented();
}

void FrameLoaderClientHl::restoreViewState()
{
    notImplemented();
}
        
void FrameLoaderClientHl::restoreScrollPositionAndViewState()
{
    notImplemented();
}


void FrameLoaderClientHl::provisionalLoadStarted()
{
    notImplemented();
}


bool FrameLoaderClientHl::shouldTreatURLAsSameAsCurrent(const KURL&) const
{
    notImplemented();
    return false;
}


void FrameLoaderClientHl::addHistoryItemForFragmentScroll()
{
    notImplemented();
}


void FrameLoaderClientHl::didFinishLoad()
{
    notImplemented();
}


void FrameLoaderClientHl::prepareForDataSourceReplacement()
{
    notImplemented();
}

void FrameLoaderClientHl::didDetectXSS(const KURL&, bool)
{
    notImplemented();
}

void FrameLoaderClientHl::setTitle(const StringWithDirection& title, const KURL&)
{
    notImplemented();
}


String FrameLoaderClientHl::userAgent(const KURL&)
{
    return m_userAgent;
}

void FrameLoaderClientHl::dispatchDidReceiveIcon()
{
    notImplemented();
}

void FrameLoaderClientHl::frameLoaderDestroyed()
{
    m_webFrame = 0;
    m_frame = 0;
    delete this;
}

bool FrameLoaderClientHl::canHandleRequest(const WebCore::ResourceRequest&) const
{
    notImplemented();
    return true;
}

void FrameLoaderClientHl::partClearedInBegin()
{
    notImplemented();
}

void FrameLoaderClientHl::updateGlobalHistory()
{
    notImplemented();
}

void FrameLoaderClientHl::updateGlobalHistoryRedirectLinks()
{
    notImplemented();
}

bool FrameLoaderClientHl::shouldGoToHistoryItem(WebCore::HistoryItem*) const
{
    notImplemented();
    return true;
}

bool FrameLoaderClientHl::shouldStopLoadingForHistoryItem(WebCore::HistoryItem*) const
{
    return true;
}

void FrameLoaderClientHl::dispatchDidAddBackForwardItem(WebCore::HistoryItem*) const
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidRemoveBackForwardItem(WebCore::HistoryItem*) const
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidChangeBackForwardIndex() const
{
    notImplemented();
}

void FrameLoaderClientHl::didDisplayInsecureContent()
{
    notImplemented();
}

void FrameLoaderClientHl::didRunInsecureContent(WebCore::SecurityOrigin*, const KURL&)
{
    notImplemented();
}

void FrameLoaderClientHl::saveScrollPositionAndViewStateToItem(WebCore::HistoryItem*)
{
    notImplemented();
}

bool FrameLoaderClientHl::canCachePage() const
{
    return false;
}

void FrameLoaderClientHl::setMainDocumentError(WebCore::DocumentLoader*, const WebCore::ResourceError&)
{
    notImplemented();
}

void FrameLoaderClientHl::committedLoad(WebCore::DocumentLoader* loader, const char* data, int length)
{
        FrameLoader* fl = loader->frameLoader();
        loader->writer()->setEncoding(m_response.textEncodingName(), false);
        loader->commitData(data, length);
}

WebCore::ResourceError FrameLoaderClientHl::cancelledError(const WebCore::ResourceRequest& request)
{
    notImplemented();
    return ResourceError(String(), WebKitErrorCannotShowURL, request.url().string(), String());
}

WebCore::ResourceError FrameLoaderClientHl::blockedError(const ResourceRequest& request)
{
    notImplemented();
    return ResourceError(String(), WebKitErrorCannotShowURL, request.url().string(), String());
}

WebCore::ResourceError FrameLoaderClientHl::cannotShowURLError(const WebCore::ResourceRequest& request)
{
    return ResourceError(String(), WebKitErrorCannotShowURL, request.url().string(), String());
}


WebCore::ResourceError FrameLoaderClientHl::cannotShowMIMETypeError(const WebCore::ResourceResponse& response)
{
    notImplemented();
    return ResourceError(String(), WebKitErrorCannotShowMIMEType, response.url().string(), String());
}

WebCore::ResourceError FrameLoaderClientHl::fileDoesNotExistError(const WebCore::ResourceResponse& response)
{
    notImplemented();
    return ResourceError(String(), WebKitErrorCannotShowURL, response.url().string(), String());
}

ResourceError FrameLoaderClientHl::interruptedForPolicyChangeError(const ResourceRequest& request)
{
    return ResourceError("Error", WebKitErrorFrameLoadInterruptedByPolicyChange,
                         request.url().string(), "Frame load interrupted by policy change");
}

bool FrameLoaderClientHl::shouldFallBack(const WebCore::ResourceError& error)
{
    notImplemented();
    return false;
}

WTF::PassRefPtr<DocumentLoader> FrameLoaderClientHl::createDocumentLoader(const ResourceRequest& request, const SubstituteData& substituteData)
{
    return DocumentLoader::create(request, substituteData);
}

void FrameLoaderClientHl::download(ResourceHandle*, const ResourceRequest&,  const ResourceResponse&)
{
    notImplemented();
}

void FrameLoaderClientHl::assignIdentifierToInitialRequest(unsigned long identifier, DocumentLoader*, const ResourceRequest&)
{
    notImplemented();   
}

void FrameLoaderClientHl::dispatchWillSendRequest(DocumentLoader*, unsigned long, ResourceRequest& request, const ResourceResponse& response)
{
    notImplemented();
}

bool FrameLoaderClientHl::shouldUseCredentialStorage(DocumentLoader*, unsigned long)
{
    notImplemented();
    return false;
}

void FrameLoaderClientHl::dispatchDidReceiveAuthenticationChallenge(DocumentLoader*, unsigned long, const AuthenticationChallenge&)
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidCancelAuthenticationChallenge(DocumentLoader*, unsigned long, const AuthenticationChallenge&)
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidReceiveResponse(DocumentLoader* loader, unsigned long id, const ResourceResponse& response)
{
    notImplemented();
    m_response = response;
}

void FrameLoaderClientHl::dispatchDidReceiveContentLength(DocumentLoader* loader, unsigned long id, int length)
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidFinishLoading(DocumentLoader* loader, unsigned long)
{
    notImplemented();
}

void FrameLoaderClientHl::dispatchDidFailLoading(DocumentLoader*, unsigned long, const ResourceError& error)
{
    notImplemented();
}

bool FrameLoaderClientHl::dispatchDidLoadResourceFromMemoryCache(DocumentLoader*, const ResourceRequest&, const ResourceResponse&, int)
{
    notImplemented();
    return false;
}

void FrameLoaderClientHl::dispatchDidFailProvisionalLoad(const ResourceError& error)
{
}

void FrameLoaderClientHl::dispatchDidFailLoad(const ResourceError& error)
{
    notImplemented();
}

Frame* FrameLoaderClientHl::dispatchCreatePage(const NavigationAction& action)
{
    struct WindowFeatures features;
    Page* page = m_webFrame->GetFrame()->page()->chrome()->createWindow(
        m_webFrame->GetFrame(),FrameLoadRequest(m_webFrame->GetFrame()->document()->securityOrigin()), features, action);
    return page->mainFrame();
}

void FrameLoaderClientHl::dispatchDecidePolicyForResponse(FramePolicyFunction function, const ResourceResponse& response, const ResourceRequest& request)
{
    if (!m_webFrame)
        return;
    
    notImplemented();
    (m_frame->loader()->policyChecker()->*function)(PolicyUse);
}

void FrameLoaderClientHl::dispatchDecidePolicyForMIMEType(FramePolicyFunction function, const String& mimetype, const ResourceRequest& request)
{
    if (!m_webFrame)
        return;

    PolicyAction action = networkStateNotifier().onLine()? PolicyUse : PolicyIgnore;
    (m_frame->loader()->policyChecker()->*function)(action);
}

void FrameLoaderClientHl::dispatchDecidePolicyForNewWindowAction(FramePolicyFunction function, const NavigationAction&, const ResourceRequest& request, PassRefPtr<FormState>, const String& targetName)
{
    if (!m_webFrame)
        return;
    
    (m_frame->loader()->policyChecker()->*function)(PolicyUse);
}

void FrameLoaderClientHl::dispatchDecidePolicyForNavigationAction(FramePolicyFunction function, const NavigationAction& action, const ResourceRequest& request, PassRefPtr<FormState>)
{
    if (!m_webFrame)
        return;
    
    (m_frame->loader()->policyChecker()->*function)(PolicyUse);
}

void FrameLoaderClientHl::dispatchUnableToImplementPolicy(const ResourceError&)
{
    notImplemented();
}

void FrameLoaderClientHl::startDownload(const ResourceRequest&)
{
    notImplemented();
}

PassRefPtr<Frame> FrameLoaderClientHl::createFrame(const KURL& url, const String& name, HTMLFrameOwnerElement* ownerElement,
                                   const String& referrer, bool allowsScrolling, int marginWidth, int marginHeight)
{
    // Create separate frame loader for a new frame
    FrameLoaderClientHl* newLoaderClient = new FrameLoaderClientHl();
    newLoaderClient->setUserAgent(m_userAgent);
    // And a new frame, inheriting current page
    RefPtr<Frame> childFrame = Frame::create(m_frame->page(), ownerElement, newLoaderClient);
    newLoaderClient->setFrame(m_webFrame, childFrame.get());

    childFrame->tree()->setName(name);
    m_frame->tree()->appendChild(childFrame);

    childFrame->init();

    if (!childFrame->page())
        return 0;

    childFrame->loader()->loadURLIntoChildFrame(url, referrer, childFrame.get());
    
    if (!childFrame->tree()->parent())
        return 0;
    
    return childFrame.release();
}

void FrameLoaderClientHl::didTransferChildFrameToNewDocument(Page*)
{
    notImplemented();
}

void FrameLoaderClientHl::transferLoadingResourceFromPage(ResourceLoader*, const ResourceRequest&, Page*)
{
}

ObjectContentType FrameLoaderClientHl::objectContentType(const KURL& url, const String& mimeType, bool shouldPreferPlugInsForImages)
{
    notImplemented();
    return ObjectContentType();
}

PassRefPtr<Widget> FrameLoaderClientHl::createPlugin(const IntSize& size, HTMLPlugInElement* element, const KURL& url, const Vector<String>& paramNames, const Vector<String>& paramValues, const String& mimeType, bool loadManually)
{
    notImplemented();
    return 0;
}

void FrameLoaderClientHl::redirectDataToPlugin(Widget* pluginWidget)
{
    notImplemented();
}

ResourceError FrameLoaderClientHl::pluginWillHandleLoadError(const ResourceResponse& response)
{
    notImplemented();
    return ResourceError(String(), WebKitErrorCannotLoadPlugIn, response.url().string(), String());
}

PassRefPtr<Widget> FrameLoaderClientHl::createJavaAppletWidget(const IntSize&, HTMLAppletElement*, const KURL& baseURL,
                                                    const Vector<String>& paramNames, const Vector<String>& paramValues)
{
    notImplemented();
    return 0;
}

String FrameLoaderClientHl::overrideMediaType() const
{
    notImplemented();
    return String();
}

void FrameLoaderClientHl::dispatchDidClearWindowObjectInWorld(DOMWrapperWorld* world)
{
    notImplemented();
}

void FrameLoaderClientHl::startDownload(const ResourceRequest& request, const String& /* suggestedName */)
{
    notImplemented();
}

void FrameLoaderClientHl::documentElementAvailable()
{
    notImplemented();
}

void FrameLoaderClientHl::didPerformFirstNavigation() const
{
    notImplemented();
}

void FrameLoaderClientHl::registerForIconNotification(bool listen)
{
    notImplemented();
}

void FrameLoaderClientHl::savePlatformDataToCachedFrame(CachedFrame*)
{ 
    notImplemented();
}

void FrameLoaderClientHl::transitionToCommittedFromCachedFrame(CachedFrame*)
{ 
    notImplemented();
}

void FrameLoaderClientHl::transitionToCommittedForNewPage()
{ 
    IntSize size(800, 600);
    if (m_frame)
    	m_frame->createView(size, WebCore::Color::white, false, IntSize(), false); 
}

bool FrameLoaderClientHl::shouldUsePluginDocument(const String &mimeType) const
{
    notImplemented();
	return false;
}
void FrameLoaderClientHl::didSaveToPageCache()
{
}

void FrameLoaderClientHl::didRestoreFromPageCache()
{
}

void FrameLoaderClientHl::dispatchDidBecomeFrameset(bool)
{
}

PassRefPtr<FrameNetworkingContext> FrameLoaderClientHl::createNetworkingContext()
{
    return FrameNetworkingContextHl::create(m_frame);
}

}
