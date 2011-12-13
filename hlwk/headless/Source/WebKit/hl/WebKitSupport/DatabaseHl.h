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

#ifndef SQLDatabaseHl_h
#define SQLDatabaseHl_h

#if ENABLE(DATABASE)

#include "config.h"
#include "ChromeClientHl.h"
#include "VoidCallback.h"
#include "SQLTransactionCallback.h"
#include "SQLTransactionErrorCallback.h"
#include "SQLStatementCallback.h"
#include "SQLStatementErrorCallback.h"
#include "SQLTransaction.h"
#include <wtf/Threading.h>

#include <stdio.h>

namespace WebCore {

class SQLError;
class SQLResultSet;
class SQLTransaction;
class DatabaseTrackerClientHl;

// Success callback handleEvent is called when transaction is successfulyy
class SQLSuccessCallback : public VoidCallback {
public:
    SQLSuccessCallback(DatabaseTrackerClientHl* client) : m_client(client) { }
    virtual ~SQLSuccessCallback() { }
    virtual void handleEvent();
private:
    DatabaseTrackerClientHl* m_client;
};

// SQLTransaction callback handleEvent is called when transaction has started
// we can add SQLStatements now
class SQLTransactionCallbackHl : public SQLTransactionCallback {
public:
    SQLTransactionCallbackHl(DatabaseTrackerClientHl* client, const String&, const Vector<SQLValue>&);
    virtual ~SQLTransactionCallbackHl() { }
    virtual void handleEvent(SQLTransaction*, bool& raisedException);
private:
    String m_statement;
    Vector<SQLValue> m_arguments;
    DatabaseTrackerClientHl* m_client;
};

// our error handling goes here, since we are operating on a transaction level
class SQLTransactionErrorCallbackHl : public SQLTransactionErrorCallback {
public:
    SQLTransactionErrorCallbackHl(DatabaseTrackerClientHl* client) : m_client(client) { }
    virtual ~SQLTransactionErrorCallbackHl() { }
    virtual bool handleEvent(SQLError*);
private:
    DatabaseTrackerClientHl* m_client;
};

// Statement callback handleEvent is called when Statement has been initiated
class SQLStatementCallbackHl : public SQLStatementCallback {
public:
    SQLStatementCallbackHl(DatabaseTrackerClientHl* client) : m_client(client) { }
    virtual ~SQLStatementCallbackHl() { }
    virtual bool handleEvent(SQLTransaction*, SQLResultSet*);
private:
    DatabaseTrackerClientHl* m_client;
};

class SQLStatementErrorCallbackHl : public SQLStatementErrorCallback {
public:
    SQLStatementErrorCallbackHl(DatabaseTrackerClientHl* client) : m_client(client) { }
    virtual ~SQLStatementErrorCallbackHl() { }
    virtual bool handleEvent(SQLTransaction*, SQLError*);
private:
    DatabaseTrackerClientHl* m_client;
};

}

#endif

#endif // SQLDatabaseHl_h
