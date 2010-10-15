/*
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "config.h"
#include "CookieJar.h"
#include "CookieJarHl.h"

#include "Cookie.h"
#include "CString.h"
#include "Document.h"
#include "KURL.h"
#include "PlatformString.h"
#include "StringHash.h"

#include <wtf/HashMap.h>
#include <curl/curl.h>

namespace WebCore {

/**
 * Cookie value is fields separated by TAB symbol:
 * 0 - domain - The domain that created AND that can read the variable.
 * 1 - flag - A TRUE/FALSE value indicating if all machines within a given
 *      domain can access the variable. This value is set automatically
 *      by the browser, depending on the value you set for domain.
 * 2 - path - The path within the domain that the variable is valid for.
 * 3 - secure - A TRUE/FALSE value indicating if a secure connection with
 *      the domain is needed to access the variable.
 * 4 - expiration - The UNIX time that the variable will expire on. UNIX time
 *      is defined as the number of seconds since Jan 1, 1970 00:00:00 GMT.
 * 5 - name - The name of the variable.
 * 6 - value - The value of the variable.
 *
 * Multiple cookies are concatenated with TAB.
**/

typedef HashMap<String, String> cookieJar_t;

static cookieJar_t cookieJar;
static int cookieJarStatus;


// ---------------------------------------------------------------------
int getCookieJarStatus(void)
{
    return cookieJarStatus;
}


// ---------------------------------------------------------------------
// Normal behaviour: we can only rise status or clear it to OK.
int setCookieJarStatus(int status)
{
    int oldStatus = cookieJarStatus;

    cookieJarStatus = status;
    return oldStatus;
}


/** --------------------------------------------------------------------
 * Add new cookie to existing set.
**/
void setCookies(Document* doc/*document*/, const KURL& url, const String& value)
{
    int i, j, len;
    const int n = 7;
    String result, key1, key2, f[n], inCookie, outCookie;
    Vector<String> field;

    // printf("%s: input: %08X %s\n%s\n\n", __func__, (unsigned)doc, url.string().utf8().data(), value.utf8().data());

    if (value.length() == 0)
        return;

    String host = url.host();

    if (doc)
    {
        Vector<String> param;
        f[0] = "";
        f[1] = "TRUE";
        f[2] = "";
        f[3] = "FALSE";
        f[4] = "0";
        f[5] = "";
        f[6] = "";
        bool ok = false;

        value.split(';', param);

        len = param.size();

        for (i = 0; i < len; i++)
        {
            param[i] = param[i].stripWhiteSpace();

            if (param[i] == "secure")
            {
                f[3] = "TRUE";
                continue;
            }

            param[i].split('=', field);
            if (field.size() < 2)
                return;

            field[0] = field[0].stripWhiteSpace();
            field[1] = field[1].stripWhiteSpace();

            if (field[0] == "domain")
            {
                // if (!host.endsWith(field[1], false))
                //     return;

                f[0] = field[1];
            }
            else if (field[0] == "path")
            {
                f[2] = field[1];
            }
            else if (field[0] == "expires")
            {
                // --- Only GMT zone is valid ---
                time_t date = curl_getdate(field[1].utf8().data(), NULL);
                if (date < 0)
                    date = 0;
                f[4] = String::number(date);
            }
            else
            {
                f[5] = field[0];
                f[6] = field[1];
                ok = true;
            }
        }

        if (!ok)
            return;

        // --- Defaults ---
        if (f[0].isEmpty())
            f[0] = host;

        if (f[2].isEmpty())
            f[2] = url.path();

        result = f[0];
        for (i = 1; i < n; i++)
            result += "\t" + f[i];

        key1 = f[0] + f[2] + f[5];
    }
    else
    {
        value.split('\t', true, field);

        if (field.size() != n)
            return;

        if (!host.endsWith(field[0], false))
            return;

        key1 =  field[0] + field[2] + field[5];

        result = value;
    }

    // --- Remove existing entry ---
    inCookie = cookieJar.get(host);
    if (!inCookie.isEmpty())
    {
        inCookie.split('\t', true, field);
        len = field.size();

        for (j = 0; j < len; j += n)
        {
            key2 = field[j] + field[j + 2] + field[j + 5];

            if (key1 == key2)
                continue;

            for (i = 0; i < n; i++)
                outCookie += "\t" + field[j + i];
        }

        outCookie = result + outCookie;
    }
    else
        outCookie = result;

    // printf("%s: result: host=%s, cookie=%s\n\n", __func__, host.utf8().data(), outCookie.utf8().data());
    cookieJar.set(host, outCookie);

    if (doc)
    {
        int cookieJarStatus = getCookieJarStatus();
        if (cookieJarStatus <= COOKIE_JAR_OK)
            setCookieJarStatus(COOKIE_JAR_DIRTY);
    }
}


String cookies(const Document* /*document*/, const KURL& url)
{
    String rawCookie = cookieJar.get(url.host());
    String urlPath = url.path();
    String resCookie;
    Vector<String> field;
    const int fieldNum = 7;
    int i, len;

    if (rawCookie.length() == 0)
        return resCookie;

    // --- Parse raw cookie ---
    rawCookie.split('\t', true, field);
    len = field.size();

    for (i = 0; i < len; i += fieldNum)
        if (urlPath.startsWith(field[i + 2], false))
            resCookie += "; " + field[i + 5] + "=" + field[i + 6];

    // --- Trim leading separator ---
    if (!resCookie.isEmpty())
        resCookie.remove(0, 2);

    // printf("%s: %s\n%s\n\n", __func__, url.string().utf8().data(), resCookie.utf8().data());
    return resCookie;
}


String cookieRequestHeaderFieldValue(const Document* /*document*/, const KURL& url)
{
    // FIXME: include HttpOnly cookie.
    // return cookieJar.get(url.string());
    return cookies(NULL, url);
}


bool cookiesEnabled(const Document* /*document*/)
{
    return true;
}


/**
 * Get raw cookies from cookieJar hash for given url.
 * If url is empty return all cookies.
**/
String getCookieJar(const KURL& url)
{
    if (!url.isEmpty())
        return cookieJar.get(url.host());

    // --- Use all cookies for empty url ---
    String rawCookie;
    cookieJar_t::iterator i_beg = cookieJar.begin(), i_end = cookieJar.end();

    for (; i_beg != i_end; ++i_beg)
        rawCookie += "\t" + i_beg->second;

    // --- Trim leading TAB ---
    if (!rawCookie.isEmpty())
        rawCookie.remove(0);

    return rawCookie;
}


/**
 * Set raw cookies from cookieJar hash for given url (required).
**/
void setCookieJar(const KURL& url, const String& rawCookie)
{
    if (!url || url.isEmpty())
        return;

    cookieJar.set(url.host(), rawCookie);
    setCookieJarStatus(COOKIE_JAR_NEW);
}


/**
 * Get all raw cookies from cookieJar hash. Use this function to avoid serialization.
**/
void getAllCookieJar(Vector<String>& rawCookies)
{
    cookieJar_t::iterator i_beg = cookieJar.begin(), i_end = cookieJar.end();

    rawCookies.clear();

    // --- URL's loop ---
    for (; i_beg != i_end; ++i_beg)
    {
        String cookies = i_beg->second;
        int begin = 0, end;
        bool done = false;
        // --- Name/value loop ---
        // Deserialization of \(\(\S\+\t\)\{6\}\S\+\)\(\t\1\)*: result = \1
        while (!done)
        {
            end = begin;
            for (int i = 0; i < 7; i++)
            {
                end = cookies.find('\t', end + 1);

                if (end < 0)
                {
                    end = cookies.length();
                    done = true;
                    break;
                }
            }

            rawCookies.append(cookies.substring(begin, end - begin));
            begin = end + 1;
        }
    }
}


bool getRawCookies(const Document*, const KURL& url, Vector<Cookie>& rawCookies)
{
    String rawCookie = getCookieJar(url);

    Vector<String> field;
    const int fieldNum = 7;
    int i, len;

    rawCookies.clear();

    if (rawCookie.length() == 0)
        return true;

    // --- Parse raw cookie ---
    rawCookie.split('\t', true, field);
    len = field.size();

    for (i = 0; i < len; i += fieldNum)
    {
        Cookie resCookie(field[i + 5], field[i + 6], field[i], field[i + 2],
            field[i + 4].toDouble(), true, field[i + 3].upper() == "TRUE", true);
        rawCookies.append(resCookie);
    }

    return true;
}


void deleteCookie(const Document*, const KURL& url, const String& name)
{
    // --- Clear all cookies for empty url ---
    if (!url || url.isEmpty())
    {
        if (!cookieJar.isEmpty())
        {
            cookieJar.clear();
            setCookieJarStatus(COOKIE_JAR_NEW);
        }
        return;
    }

    String key = url.host();

    // --- Clear all cookies for given url ---
    if (name.isEmpty())
    {
        int n = cookieJar.size();

        cookieJar.remove(key);

        if (cookieJar.size() != n)
            setCookieJarStatus(COOKIE_JAR_NEW);

        return;
    }

    // --- Clear cookie for given url and name ---
    String outCookie, inCookie = cookieJar.get(key);

    if (inCookie.isEmpty())
        return;

    Vector<String> field;
    const int n = 7;    // - Num of fields in cookie record -
    int i, j, len;
    bool modified = false;

    inCookie.split('\t', true, field);
    len = field.size();

    for (j = 0; j < len; j += n)
    {
        if (field[j + 5] == name)
        {
            modified = true;
            continue;
        }

        for (i = 0; i < n; i++)
            outCookie += "\t" + field[j + i];
    }

    if (!modified)
        return;

    // --- Trim leading TAB ---
    if (outCookie.length() > 0)
        outCookie.remove(0);

    // printf("%s: result: %s\n\n", __func__, outCookie.utf8().data());
    cookieJar.set(key, outCookie);
    setCookieJarStatus(COOKIE_JAR_NEW);
}

}
