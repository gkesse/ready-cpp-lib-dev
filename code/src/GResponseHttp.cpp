//===============================================
#include "GResponseHttp.h"
//===============================================
#define GDEFINE_STATUS(x, y)    {true, x, y}
#define GDEFINE_STATUS_LAST     {false, eGResponseHttpStatus::BadRequest, "Unknown"}
//===============================================
sGResponseHttpStatus HTTP_STATUS_MAP[] {
    GDEFINE_STATUS(eGResponseHttpStatus::Continue, "Continue")
    , GDEFINE_STATUS(eGResponseHttpStatus::SwitchingProtocol, "SwitchingProtocol")
    , GDEFINE_STATUS(eGResponseHttpStatus::Processing, "Processing")
    , GDEFINE_STATUS(eGResponseHttpStatus::EarlyHints, "EarlyHints")

    , GDEFINE_STATUS(eGResponseHttpStatus::Ok, "Ok")
    , GDEFINE_STATUS(eGResponseHttpStatus::Created, "Created")
    , GDEFINE_STATUS(eGResponseHttpStatus::Accepted, "Accepted")
    , GDEFINE_STATUS(eGResponseHttpStatus::NonAuthoritativeInformation, "NonAuthoritativeInformation")
    , GDEFINE_STATUS(eGResponseHttpStatus::NoContent, "NoContent")
    , GDEFINE_STATUS(eGResponseHttpStatus::ResetContent, "ResetContent")
    , GDEFINE_STATUS(eGResponseHttpStatus::PartialContent, "PartialContent")
    , GDEFINE_STATUS(eGResponseHttpStatus::MultiStatus, "MultiStatus")
    , GDEFINE_STATUS(eGResponseHttpStatus::AlreadyReported, "AlreadyReported")
    , GDEFINE_STATUS(eGResponseHttpStatus::ImUsed, "ImUsed")

    , GDEFINE_STATUS(eGResponseHttpStatus::MultipleChoice, "MultipleChoice")
    , GDEFINE_STATUS(eGResponseHttpStatus::MovedPermanently, "MovedPermanently")
    , GDEFINE_STATUS(eGResponseHttpStatus::Found, "Found")
    , GDEFINE_STATUS(eGResponseHttpStatus::SeeOther, "SeeOther")
    , GDEFINE_STATUS(eGResponseHttpStatus::NotModified, "NotModified")
    , GDEFINE_STATUS(eGResponseHttpStatus::UseProxy, "UseProxy")
    , GDEFINE_STATUS(eGResponseHttpStatus::TemporaryRedirect, "TemporaryRedirect")
    , GDEFINE_STATUS(eGResponseHttpStatus::PermanentRedirect, "PermanentRedirect")

    , GDEFINE_STATUS(eGResponseHttpStatus::BadRequest, "BadRequest")
    , GDEFINE_STATUS(eGResponseHttpStatus::Unauthorized, "Unauthorized")
    , GDEFINE_STATUS(eGResponseHttpStatus::PaymentRequired, "PaymentRequired")
    , GDEFINE_STATUS(eGResponseHttpStatus::Forbidden, "Forbidden")
    , GDEFINE_STATUS(eGResponseHttpStatus::NotFound, "NotFound")
    , GDEFINE_STATUS(eGResponseHttpStatus::MethodNotAllowed, "MethodNotAllowed")
    , GDEFINE_STATUS(eGResponseHttpStatus::NotAcceptable, "NotAcceptable")
    , GDEFINE_STATUS(eGResponseHttpStatus::ProxyAuthenticationRequired, "ProxyAuthenticationRequired")
    , GDEFINE_STATUS(eGResponseHttpStatus::RequestTimeout, "RequestTimeout")
    , GDEFINE_STATUS(eGResponseHttpStatus::Conflict, "Conflict")
    , GDEFINE_STATUS(eGResponseHttpStatus::Gone, "Gone")
    , GDEFINE_STATUS(eGResponseHttpStatus::LengthRequired, "LengthRequired")
    , GDEFINE_STATUS(eGResponseHttpStatus::PreconditionFailed, "PreconditionFailed")
    , GDEFINE_STATUS(eGResponseHttpStatus::PayloadTooLarge, "PayloadTooLarge")
    , GDEFINE_STATUS(eGResponseHttpStatus::UriTooLong, "UriTooLong")
    , GDEFINE_STATUS(eGResponseHttpStatus::UnsupportedMediaType, "UnsupportedMediaType")
    , GDEFINE_STATUS(eGResponseHttpStatus::RangeNotSatisfiable, "RangeNotSatisfiable")
    , GDEFINE_STATUS(eGResponseHttpStatus::ExpectationFailed, "ExpectationFailed")
    , GDEFINE_STATUS(eGResponseHttpStatus::MisdirectedRequest, "MisdirectedRequest")
    , GDEFINE_STATUS(eGResponseHttpStatus::UnprocessableEntity, "UnprocessableEntity")
    , GDEFINE_STATUS(eGResponseHttpStatus::Locked, "Locked")
    , GDEFINE_STATUS(eGResponseHttpStatus::FailedDependency, "FailedDependency")
    , GDEFINE_STATUS(eGResponseHttpStatus::TooEarly, "TooEarly")
    , GDEFINE_STATUS(eGResponseHttpStatus::UpgradeRequired, "UpgradeRequired")
    , GDEFINE_STATUS(eGResponseHttpStatus::PreconditionRequired, "PreconditionRequired")
    , GDEFINE_STATUS(eGResponseHttpStatus::TooManyRequests, "TooManyRequests")
    , GDEFINE_STATUS(eGResponseHttpStatus::RequestHeaderFieldsTooLarge, "RequestHeaderFieldsTooLarge")
    , GDEFINE_STATUS(eGResponseHttpStatus::UnavailableForLegalReasons, "UnavailableForLegalReasons")

    , GDEFINE_STATUS(eGResponseHttpStatus::InternalServerError, "InternalServerError")
    , GDEFINE_STATUS(eGResponseHttpStatus::NotImplemented, "NotImplemented")
    , GDEFINE_STATUS(eGResponseHttpStatus::BadGateway, "BadGateway")
    , GDEFINE_STATUS(eGResponseHttpStatus::ServiceUnavailable, "ServiceUnavailable")
    , GDEFINE_STATUS(eGResponseHttpStatus::GatewayTimeout, "GatewayTimeout")
    , GDEFINE_STATUS(eGResponseHttpStatus::HttpVersionNotSupported, "HttpVersionNotSupported")
    , GDEFINE_STATUS(eGResponseHttpStatus::VariantAlsoNegotiates, "VariantAlsoNegotiates")
    , GDEFINE_STATUS(eGResponseHttpStatus::InsufficientStorage, "InsufficientStorage")
    , GDEFINE_STATUS(eGResponseHttpStatus::LoopDetected, "LoopDetected")
    , GDEFINE_STATUS(eGResponseHttpStatus::NotExtended, "NotExtended")
    , GDEFINE_STATUS(eGResponseHttpStatus::NetworkAuthenticationRequired, "NetworkAuthenticationRequired")

    , GDEFINE_STATUS_LAST
};
//===============================================
GResponseHttp::GResponseHttp()
: GResponse()
, m_status(eGResponseHttpStatus::Ok)
, m_contentType(RESPONSE_HTTP_HTML)
, m_connection(RESPONSE_CONNECT_CLOSE) {

}
//===============================================
GResponseHttp::~GResponseHttp() {

}
//===============================================
void GResponseHttp::setResponseHttp(const GResponseHttp& _obj) {
    m_status            = _obj.m_status;
    m_content           = _obj.m_content;
    m_contentType       = _obj.m_contentType;
    m_connection        = _obj.m_connection;
    m_secWebSocketKey   = _obj.m_secWebSocketKey;
    setResponse(_obj);
}
//===============================================
GString GResponseHttp::toReason(const eGResponseHttpStatus& _status) const {
    int i = 0;
    sGResponseHttpStatus lStatus;
    while(1) {
        lStatus = HTTP_STATUS_MAP[i++];
        if(!lStatus.flag) break;
        if(lStatus.code == _status) break;
    }
    if(!lStatus.flag) {
        slog(eGERR, "Le status recherché n'a pas été trouvé."
                    "|status=%d", _status);
    }
    return lStatus.name;
}
//===============================================
void GResponseHttp::create() {
    if(!m_secWebSocketKey.isEmpty()) {
        createWebsocket();
    }
    else {
        createHttp();
    }
}
//===============================================
void GResponseHttp::createHttp() {
    if(m_isContinue) m_connection = RESPONSE_CONNECT_KEEP_ALIVE;

    slog(eGINF, "Création de la réponse à envoyer au client."
                "|status=%d"
                "|contentType=%s"
                "|continue=%d"
                "|connection=%s", m_status, m_contentType.c_str(), m_isContinue, m_connection.c_str());

    m_response += sformat("HTTP/1.1 %d %s\r\n", m_status, toReason(m_status).c_str());
    m_response += sformat("Content-Type: %s\r\n", m_contentType.c_str());
    m_response += sformat("Content-Length: %d\r\n", m_content.size());
    m_response += sformat("Connection: %s\r\n", m_connection.c_str());
    m_response += sformat("\r\n");
    m_response += m_content;
}
//===============================================
void GResponseHttp::createWebsocket() {
    m_connection = RESPONSE_CONNECT_UPGRADE;
    m_status = eGResponseHttpStatus::SwitchingProtocol;
    GString lUpgrade = RESPONSE_UPGRADE_WEBSOCKET;
    m_content = "";

    slog(eGINF, "Création de la réponse à envoyer au client."
                "|status=%d"
                "|contentType=%s"
                "|continue=%d"
                "|connection=%s"
                "|secWebSocketKey=%s", m_status, m_contentType.c_str(), m_isContinue
                , m_connection.c_str(), m_secWebSocketKey.c_str());

    GString lSecWebSocketAccept = m_secWebSocketKey + WEBSOCKET_MAGGIC_NUMBER;
    uchar lHashBuf[SHA_DIGEST_LENGTH];
    SHA1(lSecWebSocketAccept.uc_str(), lSecWebSocketAccept.size(), lHashBuf);
    GString lHash(lHashBuf, SHA_DIGEST_LENGTH);

    m_response += sformat("HTTP/1.1 %d %s\r\n", m_status, toReason(m_status).c_str());
    m_response += sformat("Upgrade: %s\r\n", lUpgrade.c_str());
    m_response += sformat("Connection: %s\r\n", m_connection.c_str());
    m_response += sformat("Sec-WebSocket-Accept: %s\r\n", lHash.toBase64().c_str());
    m_response += sformat("\r\n");
    m_response += m_content;
}
//===============================================
