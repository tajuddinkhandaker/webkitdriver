 
#ifndef WEBKITDRIVERPRIVATE_H
#define WEBKITDRIVERPRIVATE_H

#include "config.h"
#include "Page.h"
#include "Frame.h"
#include "HTMLFrameOwnerElement.h"
#include "KURL.h"
#include "GeolocationControllerClientHl.h"
#include "DatabaseTrackerClientHl.h"

class WebKitDriverPrivate {

public:
    WebKitDriverPrivate() :
	    page(0),
            frame(0),
            geoClient(0),
            dbClient(0)
    {}
    
    WebCore::Page *page;
    WebCore::Frame* frame;
    WebCore::Frame* mainFrame;
    WebCore::GeolocationControllerClientHl* geoClient;
    WebCore::DatabaseTrackerClientHl* dbClient;
};

#endif
