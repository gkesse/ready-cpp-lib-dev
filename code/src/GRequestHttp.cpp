//===============================================
#include "GRequestHttp.h"
//===============================================
GRequestHttp::GRequestHttp()
: GObject()
, m_total(0) {

}
//===============================================
GRequestHttp::~GRequestHttp() {

}
//===============================================
void GRequestHttp::setData(const GString& _data) {
    m_data = _data;
}
//===============================================
void GRequestHttp::setRequest(const GRequestHttp& _obj) {
    m_method            = _obj.m_method;
    m_uri               = _obj.m_uri;
    m_version           = _obj.m_version;
    m_contentType       = _obj.m_contentType;
    m_request           = _obj.m_request;
    m_secWebSocketKey   = _obj.m_secWebSocketKey;
}
//===============================================
int GRequestHttp::getTotal() const {
    return m_total;
}
//===============================================
bool GRequestHttp::analyzeHeader() {
    if(m_data.isEmpty()) return false;
    const GString CRLF = "\r\n";
    const GString CRLFCRLF = "\r\n\r\n";
    int lContentLenght = m_data.extract("Content-Length:", CRLF).trim().toInt();
    GString lHeader = m_data.extract(CRLFCRLF);
    if(lHeader.isEmpty()) {
        slog(eGERR, "La lecture l'entête de la requête HTTP a échoué."
                    "|data=%s", m_data.c_str());
        return false;
    }
    m_total = lHeader.size() + CRLFCRLF.size() + lContentLenght;
    return true;
}
//===============================================
bool GRequestHttp::analyzeGet() {
    if(m_data.isEmpty()) return false;

    const GString CRLF = "\r\n";
    const GString CRLFCRLF = "\r\n\r\n";
    const GString SPACE = " ";
    const GString DOUBLE_POINT = ":";

    // GET /home/admin HTTP/1.1
    GString lData = m_data.extract(CRLF, 0);
    GString lMethod = lData.extract(SPACE, 0);
    GString lUri = lData.extract(SPACE, 1);
    GString lVersion = lData.extract(SPACE, 2);

    // Host: 192.168.1.8:9050
    GString lHost = m_data.extract("Host:", CRLF).trim();
    // Connection: keep-alive
    GString lConnection = m_data.extract("Connection:", CRLF).trim();
    // Cache-Control: max-age=0
    GString lCacheControl = m_data.extract("Cache-Control:", CRLF).trim();
    // Upgrade-Insecure-Requests: 1
    GString lUpgradeInsecureRequests = m_data.extract("Upgrade-Insecure-Requests:", CRLF).trim();
    // User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36
    GString lUserAgent = m_data.extract("User-Agent:", CRLF).trim();
    // Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
    GString lAccept = m_data.extract("Accept:", CRLF).trim();
    // Accept-Encoding: gzip, deflate
    GString lAcceptEncoding = m_data.extract("Accept-Encoding:", CRLF).trim();
    // Accept-Language: fr-FR,fr;q=0.9,en-US;q=0.8,en;q=0.7,zh-CN;q=0.6,zh;q=0.5
    GString lAcceptLanguage = m_data.extract("Accept-Language:", CRLF).trim();
    // Sec-WebSocket-Version: 13
    GString lSecWebSocketVersion = m_data.extract("Sec-WebSocket-Version:", CRLF).trim();
    // Sec-WebSocket-Key: p5oc3ITL2LPtsOroR04Ztw==
    GString lSecWebSocketKey = m_data.extract("Sec-WebSocket-Key:", CRLF).trim();
    // Upgrade: websocket
    GString lUpgrade = m_data.extract("Upgrade:", CRLF).trim();
    // Sec-WebSocket-Extensions: permessage-deflate; client_max_window_bits
    GString lSecWebSocketExtensions = m_data.extract("Sec-WebSocket-Extensions:", CRLF).trim();

    m_method            = lMethod;
    m_uri               = lUri;
    m_version           = lVersion;
    m_secWebSocketKey   = lSecWebSocketKey;

    slog(eGINF, "Analyse de la requête HTTP GET."
                "|method=%s"
                "|uri=%s"
                "|version=%s"
                "|connection=%s"
                "|upgrade=%s"
                "|sec_websocket_key=%s", m_method.c_str(), m_uri.c_str(), m_version.c_str()
                , lConnection.c_str(), lUpgrade.c_str(), m_secWebSocketKey.c_str());

    return true;
}
//===============================================
bool GRequestHttp::analyzePost() {
    if(m_data.isEmpty()) return false;

    const GString CRLF = "\r\n";
    const GString CRLFCRLF = "\r\n\r\n";
    const GString SPACE = " ";
    const GString DOUBLE_POINT = ":";
    const GString FORM_SEP = "&";
    const GString DATA_SEP = "=";

    // POST /carpool/inscription/email HTTP/1.1
    GString lData = m_data.extract(CRLF, 0);
    GString lMethod = lData.extract(SPACE, 0);
    GString lUri = lData.extract(SPACE, 1);
    GString lVersion = lData.extract(SPACE, 2);

    // Host: 192.168.1.8:9050
    GString lHost = m_data.extract("Host:", CRLF).trim();
    // Connection: keep-alive
    GString lConnection = m_data.extract("Connection:", CRLF).trim();
    // Cache-Control: max-age=0
    GString lCacheControl = m_data.extract("Cache-Control:", CRLF).trim();
    // Upgrade-Insecure-Requests: 1
    GString lUpgradeInsecureRequests = m_data.extract("Upgrade-Insecure-Requests:", CRLF).trim();
    // Origin: http://192.168.1.8:9050
    GString lOrigin = m_data.extract("Origin:", CRLF).trim();
    // Content-Type: application/x-www-form-urlencoded
    m_contentType = m_data.extract("Content-Type:", CRLF).trim();
    // User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36
    GString lUserAgent = m_data.extract("User-Agent:", CRLF).trim();
    // Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
    GString lAccept = m_data.extract("Accept:", CRLF).trim();
    // Referer: http://192.168.1.8:9050/carpool/inscription/email
    GString lReferer = m_data.extract("Referer:", CRLF).trim();
    // Accept-Encoding: gzip, deflate
    GString lAcceptEncoding = m_data.extract("Accept-Encoding:", CRLF).trim();
    // Accept-Language: fr-FR,fr;q=0.9,en-US;q=0.8,en;q=0.7,zh-CN;q=0.6,zh;q=0.5
    GString lAcceptLanguage = m_data.extract("Accept-Language:", CRLF).trim();
    // request
    GString lRequest = m_data.extractEnd(CRLFCRLF);

    m_method            = lMethod;
    m_uri               = lUri;
    m_version           = lVersion;
    m_request           = lRequest;

    slog(eGINF, "Méthode de la requête HTTP POST."
                "|method=%s"
                "|uri=%s"
                "|version=%s"
                "|content_type=%s", m_method.c_str(), m_uri.c_str(), m_version.c_str(), m_contentType.c_str());

    return true;
}
//===============================================
const GString& GRequestHttp::getMethod() const {
    return m_method;
}
//===============================================
const GString& GRequestHttp::getUri() const {
    return m_uri;
}
//===============================================
const GString& GRequestHttp::getVersion() const {
    return m_version;
}
//===============================================
const GString& GRequestHttp::getContentType() const {
    return m_contentType;
}
//===============================================
const GString& GRequestHttp::getSecWebSocketKey() const {
    return m_secWebSocketKey;
}
//===============================================
const GString& GRequestHttp::getRequest() const {
    return m_request;
}
//===============================================
