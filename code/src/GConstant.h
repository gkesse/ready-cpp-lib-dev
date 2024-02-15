//===============================================
#ifndef _GConstant_
#define _GConstant_
//===============================================
// callback
//===============================================
const char* const CALLBACK_CONTENT_TYPE_FORM    = "application/x-www-form-urlencoded";
const char* const CALLBACK_CONTENT_TYPE_XML     = "application/xml; charset=UTF-8";
const char* const CALLBACK_CONTENT_TYPE_JSON    = "application/json; charset=UTF-8";
//===============================================
// debug
//===============================================
const char* const DEBUG_LOG_FILENAME            = "logs.txt";
const char* const DEBUG_LOG_DATE_FORMAT         = "%d/%m/%Y %H:%M:%S";
//===============================================
// response
//===============================================
const char* const RESPONSE_HTTP_FORM            = "application/x-www-form-urlencoded";
const char* const RESPONSE_HTTP_HTML            = "text/html; charset=UTF-8";
const char* const RESPONSE_HTTP_XML             = "application/xml; charset=UTF-8";
const char* const RESPONSE_HTTP_JSON            = "application/json; charset=UTF-8";
//===============================================
// socket
//===============================================
const char* const SOCKET_HOSTNAME               = "0.0.0.0";
const int SOCKET_PORT                           = 9050;
const int SOCKET_BACKLOG                        = 20;
const int SOCKET_BUFFER_SIZE                    = 1024;
const int SOCKET_BUFFER_MAX                     = 1*1024*1024;
//===============================================
#endif
//===============================================
