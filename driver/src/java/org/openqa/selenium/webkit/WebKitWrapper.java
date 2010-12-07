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
import org.openqa.selenium.webkit.WebKitJNI;

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
            Socket dataSocket = new Socket((String)null, port);
            dataSocket.setTcpNoDelay(true);
            DataOutputStream out = new DataOutputStream(dataSocket.getOutputStream());
            DataInputStream in   = new DataInputStream(dataSocket.getInputStream());

            boolean endOfSession = false;
        
            // Handle serialized data while communication socket is open.
            while (!endOfSession) {
                Object res;
                
                // Process background events when idle. Idle interval 
                // can be up to 5 seconds.
                for (int i = 0; in.available() == 0 && i < 100; i++) {
                    long startTime = System.currentTimeMillis();
                    WebKitJNI.getInstance().processEvents();
                    long timeToWait = 50 - (System.currentTimeMillis() - startTime);
                    if (timeToWait > 0) {
                        try { 
                            Thread.sleep(timeToWait);
                        } catch(InterruptedException ignore) { 
                            break;
                        }
                    }
                }

                try {
                    res = WebKitSerializer.invokeMethodFromStream(in);
                } catch (Exception e) {
                    res = e;
                }

                try {
                    WebKitSerializer.serialize(out, res);
                } catch (Exception e) {
                    System.out.println("Caught exceptiong - returning 0");
                    System.out.println(e.toString());
                    res = 0;
                    WebKitSerializer.serialize(out, res);
                }
                out.flush();
                try {
                    endOfSession = in.readBoolean();
                } catch (IOException e) {
                    endOfSession = true;
                }
            }
        } catch (IOException e) {
            System.out.println("Wrapper finished: " + e.getMessage());
        }
    }
}
