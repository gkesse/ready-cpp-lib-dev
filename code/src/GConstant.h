//===============================================
#ifndef _GConstant_
#define _GConstant_
//===============================================
// callback
//===============================================
const char* const CALLBACK_CONTENT_TYPE_FORM    = "application/x-www-form-urlencoded";
const char* const CALLBACK_CONTENT_TYPE_XML     = "application/xml";
const char* const CALLBACK_CONTENT_TYPE_JSON    = "application/json";
//===============================================
// debug
//===============================================
const char* const DEBUG_LOG_FILENAME            = "logs.txt";
const char* const DEBUG_LOG_DATE_FORMAT         = "%d/%m/%Y %H:%M:%S";
//===============================================
// socket
//===============================================
const char* const SOCKET_HOSTNAME               = "0.0.0.0";
const int SOCKET_PORT                           = 9050;
const int SOCKET_BACKLOG                        = 20;
const int SOCKET_BUFFER_SIZE                    = 1024; //---------- 1Ko
const int SOCKET_BUFFER_MAX                     = 1*1024*1024; //--- 1Mo
//===============================================
#endif
//===============================================
