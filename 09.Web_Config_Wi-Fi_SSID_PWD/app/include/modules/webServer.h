/*
MIT License

Copyright (c) 2018 imliubo
Base On Dave Gamble and cJSON contributors

Github  https://github.com/imliubo
Website https://www.makingfun.xyz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef WEBSERVER_H__
#define WEBSERVER_H__

/*********************
 *      INCLUDES
 *********************/
#include "c_types.h"

/*********************
 *      DEFINES
 *********************/
#define SERVER_PORT 80
#define URLSize 20

/**********************
 *      TYPEDEFS
 **********************/
typedef enum Result_Resp {
    RespFail = 0,
    RespSuc,
} Result_Resp;

typedef enum ProtocolType {
    GET = 0,
    POST,
} ProtocolType;

typedef enum _ParmType {
    SWITCH_STATUS = 0,
    INFOMATION,
    WIFI,
    SCAN,
	REBOOT,
    DEEP_SLEEP,
    LIGHT_STATUS,
    CONNECT_STATUS,
    USER_BIN
} ParmType;

typedef struct URL_Frame {
    enum ProtocolType Type;
    char pSelect[URLSize];
    char pCommand[URLSize];
    char pFilename[URLSize];
} URL_Frame;

typedef struct _rst_parm {
    ParmType parmtype;
    struct espconn *pespconn;
} rst_parm;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void user_webserver_init(uint32 port);

/**********************
 *      MACROS
 **********************/
#endif  /*   WEBSERVER_H__   */

