/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2016 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

#define USE_OPTIMIZE_PRINTF

//At the same time, only one can be 1
#define TCP_CLIENT 0
#define TCP_SERVER 0
#define UDP_TEST   1

#define STA_SSID "XXXXXXXXX"//your wifi SSID
#define STA_PASS "xxxxxxxxx"//your wifi password
#define STA_TYPE AUTH_WPA2_PSK

#define TCP_SERVER_IP    "192.168.1.10"//TCP server IP,it is according your TCP server PC or device IP
#define TCP_SERVER_PORT  6666
#define TCP_LOCAL_PORT	 8888

#define UDP_REMOTE_IP    "192.168.1.10"//UDP remote IP,With the connectionless UDP protocol, 
				       //I don't think we should divide the server and the client.
#define UDP_REMOTE_PORT  6666
#define UDP_LOCAL_PORT	 8888

#endif

