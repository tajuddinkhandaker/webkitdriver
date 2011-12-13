/*
 * Copyright (C) 2007 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
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

#include "wtf/PassRefPtr.h"
#include "DatabaseTrackerClientHl.h"
#include "SQLResultSet.h"
#include "SQLError.h"
#include "SQLValue.h"
#include "WebKitDriver.h"

#if ENABLE(DATABASE)

namespace WebCore {

DatabaseTrackerClientHl::DatabaseTrackerClientHl(WebKitDriver* driver) : 
        m_driver(driver),
        m_rowsAffected(0),
        m_insertID(0), 
        m_resultIsOK(false) { 
    m_result = SQLResultSetRowList::create();
}

void DatabaseTrackerClientHl::successCallback() {
    m_driver->SetBusyState(WebKitDriver::DATABASE, false);
}

void DatabaseTrackerClientHl::setResult(SQLResultSet* resultSet) {
    m_resultIsOK = true;
    m_result = SQLResultSetRowList::create();
    m_rowsAffected = 0;
    m_insertID = 0;
    if (!resultSet) return;
    ExceptionCode code;
    SQLResultSetRowList* result = resultSet->rows();
    m_rowsAffected = resultSet->rowsAffected();
    m_insertID = resultSet->insertId(code);

    for (int i = 0; i < result->columnNames().size(); i++) {
        m_result->addColumn(result->columnNames()[i]);
    }

    for (int i = 0; i < result->values().size(); i++) {
        m_result->addResult(result->values()[i]);
    }
}

void DatabaseTrackerClientHl::setError(SQLError* error) {
    m_resultIsOK = false;
    m_error = adoptRef(error);
}
    
SQLResultSetRowList* DatabaseTrackerClientHl::getResult() {
    return m_result.get();
}
    
SQLError* DatabaseTrackerClientHl::getError() {
    return m_error.get();
}

} // namespace WebCore

#endif

