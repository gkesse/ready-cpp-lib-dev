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
void GRequestHttp::setRequest(const GRequestHttp& _request) {
    m_method = _request.m_method;
    m_uri = _request.m_uri;
    m_version = _request.m_version;
    m_contentType = _request.m_contentType;
    m_request = _request.m_request;
    m_forms = _request.m_forms;
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
                    "|adresse_ip=%s"
                    "|port=%d"
                    "|process=%d"
                    "|data=%s", m_addressIP.c_str(), m_port, m_pid, m_data.c_str());
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

    // data=GET /home/admin HTTP/1.1
    GString lMethod = m_data.extract(CRLF, 0);

    m_method = lMethod.extract(SPACE, 0);
    m_uri = lMethod.extract(SPACE, 1);
    m_version = lMethod.extract(SPACE, 2);

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

    slog(eGINF, "Méthode de la requête HTTP."
                "|adresse_ip=%s"
                "|port=%d"
                "|process=%d"
                "|method=%s"
                "|uri=%s"
                "|version=%s", m_addressIP.c_str(), m_port, m_pid, m_method.c_str(), m_uri.c_str(), m_version.c_str());

    return true;
}
//===============================================
bool GRequestHttp::analyzePost() {
    if(m_data.isEmpty()) return false;

    const GString CRLF = "\r\n";
    const GString CRLFCRLF = "\r\n\r\n";
    const GString SPACE = " ";
    const GString DOUBLE_POINT = ":";
    const GString FORM_DATA = "application/x-www-form-urlencoded";
    const GString FORM_SEP = "&";
    const GString DATA_SEP = "=";

    // POST /carpool/inscription/email HTTP/1.1
    GString lMethod = m_data.extract(CRLF, 0);

    m_method = lMethod.extract(SPACE, 0);
    m_uri = lMethod.extract(SPACE, 1);
    m_version = lMethod.extract(SPACE, 2);

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
    m_request = m_data.extractEnd(CRLFCRLF);

    if(m_contentType == FORM_DATA) {
        int lCount = m_request.count(FORM_SEP);
        for(int i = 0; i < lCount; i++) {
            GString lData = m_request.extract(FORM_SEP, i);
            GString lKey = lData.extract(DATA_SEP);
            GString lValue = lData.extractEnd(DATA_SEP);
            m_forms[lKey] = lValue;
        }
    }

    slog(eGINF, "Méthode de la requête HTTP POST."
                "|adresse_ip=%s"
                "|port=%d"
                "|process=%d"
                "|method=%s"
                "|uri=%s"
                "|version=%s"
                "|content_type=%s"
                "|request=%s", m_addressIP.c_str(), m_port, m_pid, m_method.c_str(), m_uri.c_str(), m_version.c_str(), m_contentType.c_str(), m_request.c_str());

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
    return m_uri;
}
//===============================================
const GRequestHttp::GForms& GRequestHttp::getForms() const {
    return m_forms;
}
//===============================================
