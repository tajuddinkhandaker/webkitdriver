/*
 * Copyright (C) 2007 Kevin Ollivier <kevino@theolliviers.com>
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
#include "Logging.h"
#include "PlatformString.h"

namespace WebCore {

void InitializeLoggingChannelsIfNecessary()
{
    static bool didInitializeLoggingChannels = false;
    if (didInitializeLoggingChannels)
        return;

    didInitializeLoggingChannels = true;

    char* logEnv = getenv("WEBKIT_DEBUG");
    if (!logEnv)
        return;

    char tmp[128];
    for (int idx=0;;logEnv++) {
	if (*logEnv=='\0' || *logEnv==',') {
		tmp[idx] = '\0';
		String str = String::fromUTF8(tmp, idx);
		if (WTFLogChannel* channel = getChannelFromName(str))
		    channel->state = WTFLogChannelOn;
		idx = 0;
	} else if (idx < sizeof(tmp) - 1)
		  tmp[idx++] = *logEnv;
	if (!*logEnv) break;
    }
}

}
