/*
Copyright 2007-2009 WebDriver committers
Copyright 2007-2009 Google Inc.
Portions copyright 2007 ThoughtWorks, Inc

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/*
 * Copyright 2007 ThoughtWorks, Inc
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */
package org.openqa.selenium.webkit;

import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.HashSet;
import java.lang.Thread;

import org.openqa.selenium.By;
import org.openqa.selenium.Cookie;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.html5.*;
import org.openqa.selenium.RenderedWebElement;
import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.webkit.WebKitDriver;
import org.openqa.selenium.webkit.WebKitWebElement;
import org.openqa.selenium.webkit.WebKitSerializer;
import org.openqa.selenium.webkit.WebKitJNI;

import java.io.FileOutputStream;
import java.io.PrintStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.EOFException;
import java.io.IOException;
import java.nio.ByteBuffer;

public class WebKitWrapper {
    public static void main(String[] args) {
        try {

            /* WebKitWrapper communicates with proxy using stdin/stdout. However, 
             * WebKit code can contain debug output to stdout, which can interfere this 
             * communication. To avoid this, stdin and stdout should be duplicated and
             * then reopened to another file.
            */
            //String redirectTo = "/dev/tty";
            String redirectTo = "/tmp/children.out";
            int next;
            /* Get next available file descriptor */
            next = WebKitJNI.getInstance().getAvailableFD();
            /* Create new output stream. In UNIX we can be sure it will have next available
             * file descriptor. */
            DataOutputStream out = new DataOutputStream(new FileOutputStream("/dev/null"));
            /* Dupclicate stdout descriptor to the new one and reopen stdin to specified
             *  file */
            WebKitJNI.getInstance().reassignFD(1, next, redirectTo);

            next = WebKitJNI.getInstance().getAvailableFD();
            DataOutputStream err = new DataOutputStream(new FileOutputStream("/dev/null"));
            WebKitJNI.getInstance().reassignFD(2, next, redirectTo);

            DataInputStream in = new DataInputStream(System.in);
            /*
            DataOutputStream out = new DataOutputStream(System.out);
            */
            System.setOut(new PrintStream(new FileOutputStream(redirectTo, true)));
            System.setErr(new PrintStream(new FileOutputStream(redirectTo + ".err", true)));
            //System.setErr(System.out);

            WebKitSerializer serializer = new WebKitSerializer();
            while (true) {
                int len = in.readInt();
                ByteBuffer buffer = ByteBuffer.allocate(len);
                int c = in.read(buffer.array());
                if (c != len)
                    break;
                Object res;
                try {
                    res = WebKitSerializer.invokeMethodFromStream(buffer);
                } catch (Exception e) {
                    res = e;
                }
                ByteBuffer bb = ByteBuffer.allocate(30000);
                try {
                    WebKitSerializer.serialize(bb, res);
                } catch (Exception e) {
                    res = 0;
                    WebKitSerializer.serialize(bb, res);
                }
                out.writeInt(bb.position());
                out.write(bb.array(), 0, bb.position());
                out.flush();
            }
        } catch (EOFException e) {
        } catch (IOException e) {
            System.out.println("Wrapper finished: " + e.toString());
        }
    }
}
