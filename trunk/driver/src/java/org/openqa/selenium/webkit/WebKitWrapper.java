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

import org.openqa.selenium.WebDriverException;
import org.openqa.selenium.webkit.WebKitSerializer;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.net.Socket;

public class WebKitWrapper {
    public static void main(String[] args) {
        int port;
        try {
            port = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            throw new WebDriverException("Invalid port number: " + args[0]);
        }
        try {
            Socket dataSocket = new Socket("localhost", port);
            DataOutputStream out = new DataOutputStream(dataSocket.getOutputStream());
            DataInputStream in   = new DataInputStream(dataSocket.getInputStream());
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
        } catch (IOException e) {
            System.out.println("Wrapper finished: " + e.getMessage());
        }
    }
}
