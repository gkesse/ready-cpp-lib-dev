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
void GResponseHttp::setStatus(const eGResponseHttpStatus& _status) {
    m_status = _status;
}
//===============================================
void GResponseHttp::setContentType(const GString& _contentType) {
    m_contentType = _contentType;
}
//===============================================
void GResponseHttp::setContent(const GString& _content) {
    m_content = _content;
}
//===============================================
void GResponseHttp::setResponseHttp(const GResponseHttp& _obj) {
    m_status        = _obj.m_status;
    m_content       = _obj.m_content;
    m_contentType   = _obj.m_contentType;
    m_connection    = _obj.m_connection;
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
        m_logs.addProblem();
    }
    return lStatus.name;
}
//===============================================
const GString& GResponseHttp::toContent() const {
    return m_content;
}
//===============================================
void GResponseHttp::create() {
    slog(eGINF, "Création de la réponse à envoyer au client."
                "|status=%d"
                "|content_type=%s", m_status, m_contentType.c_str());

    m_response += sformat("HTTP/1.1 %d %s\r\n", m_status, toReason(m_status).c_str());
    m_response += sformat("Content-Type: %s\r\n", m_contentType.c_str());
    m_response += sformat("Content-Length: %d\r\n", m_content.size());
    m_response += sformat("Connection: %s\r\n", m_connection.c_str());
    m_response += sformat("\r\n");
    m_response += m_content;
}
//===============================================
