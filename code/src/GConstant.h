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
//
const int DEBUG_TYPE_OFF                        = 0;
const int DEBUG_TYPE_SRV                        = 1;
const int DEBUG_TYPE_EXT                        = 2;
const int DEBUG_TYPE_STA                        = 3;
const int DEBUG_TYPE_END                        = 4;
const int DEBUG_TYPE_INF                        = 5;
const int DEBUG_TYPE_WAR                        = 6;
const int DEBUG_TYPE_ERR                        = 7;
const int DEBUG_TYPE_MAN                        = 8;
//===============================================
// log
//===============================================
const char* const LOG_TYPE_ERROR                = "error";
const char* const LOG_TYPE_INFO                 = "info";
const char* const LOG_TYPE_DATA                 = "data";
//===============================================
// mysql
//===============================================
const char* const MYSQL_CONN_PROTOCOL           = "tcp";
const char* const MYSQL_CONN_HOSTNAME           = "localhost";
const char* const MYSQL_CONN_DATABASE           = "db_carpool_test";
const char* const MYSQL_CONN_USERNAME           = "admins";
const char* const MYSQL_CONN_PASSWORD           = "r8hnRmVWlATcb34Szrq6";
const int MYSQL_CONN_PORT                       = 3306;
//
const int MYSQL_ERROR_DUPLICATION               = 1062;
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
