/*
 * Copyright (C) 2007 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *Transaction
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ChromeClientHl.h"
#include "VoidCallback.h"
#include "SQLTransaction.h"
#include <wtf/Threading.h>
#include "DatabaseHl.h"
#include "DatabaseTrackerClientHl.h"
#include "Logging.h"

#if ENABLE(DATABASE)

namespace WebCore {

class SQLError;
class SQLResultSet;

void SQLSuccessCallback::handleEvent() { 
    WTFLog(&WebCore::LogStorageAPI, "Success callback");
    m_client->successCallback(); 
}

SQLTransactionCallbackHl::SQLTransactionCallbackHl(DatabaseTrackerClientHl* client, const String& statement, const Vector<SQLValue>& arguments):
    m_client(client),
    m_statement(statement),
    m_arguments(arguments) {
}

void SQLTransactionCallbackHl::handleEvent(SQLTransaction* transaction, bool& raisedException) { 
    PassRefPtr<SQLStatementCallbackHl> statementCallback = adoptRef(new SQLStatementCallbackHl(m_client));
    PassRefPtr<SQLStatementErrorCallbackHl> statementErrorCallback = adoptRef(new SQLStatementErrorCallbackHl(m_client));
    ExceptionCode exception;
    m_client->setResult(0);

    // creating and executing SQLStatement(s)
    transaction->executeSQL(m_statement, m_arguments, statementCallback, statementErrorCallback, exception);
}

void SQLTransactionErrorCallbackHl::handleEvent(SQLError* error) { 
    WTFLog(&WebCore::LogStorageAPI, "Error callback");
    m_client->setError(error);
    m_client->successCallback(); 
}

void SQLStatementCallbackHl::handleEvent(SQLTransaction*, SQLResultSet* result, bool& raisedException) {
    // right now we are passing result to client, without other processing
    m_client->setResult(result);
}

}

#endif
