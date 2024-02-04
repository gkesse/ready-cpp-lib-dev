//===============================================
#include "GResponseHttp.h"
//===============================================
#define GDEFINE_STATUS(x, y) {true, x, y}
#define GDEFINE_STATUS_LAST {false, GResponseHttp::eGStatus::BadRequest, "Unknown"}
//===============================================
GResponseHttp::sGStatus HTTP_STATUS_MAP[] {
    GDEFINE_STATUS(GResponseHttp::eGStatus::Continue, "Continue")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::SwitchingProtocol, "SwitchingProtocol")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::Processing, "Processing")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::EarlyHints, "EarlyHints")

    , GDEFINE_STATUS(GResponseHttp::eGStatus::Ok, "Ok")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::Created, "Created")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::Accepted, "Accepted")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::NonAuthoritativeInformation, "NonAuthoritativeInformation")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::NoContent, "NoContent")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::ResetContent, "ResetContent")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::PartialContent, "PartialContent")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::MultiStatus, "MultiStatus")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::AlreadyReported, "AlreadyReported")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::ImUsed, "ImUsed")

    , GDEFINE_STATUS(GResponseHttp::eGStatus::MultipleChoice, "MultipleChoice")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::MovedPermanently, "MovedPermanently")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::Found, "Found")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::SeeOther, "SeeOther")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::NotModified, "NotModified")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::UseProxy, "UseProxy")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::TemporaryRedirect, "TemporaryRedirect")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::PermanentRedirect, "PermanentRedirect")

    , GDEFINE_STATUS(GResponseHttp::eGStatus::BadRequest, "BadRequest")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::Unauthorized, "Unauthorized")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::PaymentRequired, "PaymentRequired")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::Forbidden, "Forbidden")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::NotFound, "NotFound")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::MethodNotAllowed, "MethodNotAllowed")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::NotAcceptable, "NotAcceptable")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::ProxyAuthenticationRequired, "ProxyAuthenticationRequired")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::RequestTimeout, "RequestTimeout")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::Conflict, "Conflict")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::Gone, "Gone")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::LengthRequired, "LengthRequired")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::PreconditionFailed, "PreconditionFailed")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::PayloadTooLarge, "PayloadTooLarge")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::UriTooLong, "UriTooLong")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::UnsupportedMediaType, "UnsupportedMediaType")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::RangeNotSatisfiable, "RangeNotSatisfiable")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::ExpectationFailed, "ExpectationFailed")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::MisdirectedRequest, "MisdirectedRequest")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::UnprocessableEntity, "UnprocessableEntity")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::Locked, "Locked")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::FailedDependency, "FailedDependency")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::TooEarly, "TooEarly")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::UpgradeRequired, "UpgradeRequired")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::PreconditionRequired, "PreconditionRequired")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::TooManyRequests, "TooManyRequests")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::RequestHeaderFieldsTooLarge, "RequestHeaderFieldsTooLarge")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::UnavailableForLegalReasons, "UnavailableForLegalReasons")

    , GDEFINE_STATUS(GResponseHttp::eGStatus::InternalServerError, "InternalServerError")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::NotImplemented, "NotImplemented")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::BadGateway, "BadGateway")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::ServiceUnavailable, "ServiceUnavailable")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::GatewayTimeout, "GatewayTimeout")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::HttpVersionNotSupported, "HttpVersionNotSupported")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::VariantAlsoNegotiates, "VariantAlsoNegotiates")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::InsufficientStorage, "InsufficientStorage")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::LoopDetected, "LoopDetected")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::NotExtended, "NotExtended")
    , GDEFINE_STATUS(GResponseHttp::eGStatus::NetworkAuthenticationRequired, "NetworkAuthenticationRequired")

    , GDEFINE_STATUS_LAST
};
//===============================================
GResponseHttp::GResponseHttp()
: GResponse()
, m_status(eGStatus::Ok)
, m_contentType("text/html; charset=UTF-8")
, m_connection("Closed") {

}
//===============================================
GResponseHttp::~GResponseHttp() {

}
//===============================================
void GResponseHttp::setStatus(const eGStatus& _status) {
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
GString GResponseHttp::toReason(const eGStatus& _status) const {
    int i = 0;
    sGStatus lStatus;
    while(1) {
        lStatus = HTTP_STATUS_MAP[i++];
        if(!lStatus.flag) break;
        if(lStatus.code == _status) break;
    }
    return lStatus.name;
}
//===============================================
void GResponseHttp::create() {
    m_response += sformat("HTTP/1.1 %d %s\r\n", m_status, toReason(m_status).c_str());
    m_response += sformat("Content-Type: %s\r\n", m_contentType.c_str());
    m_response += sformat("Content-Length: %d\r\n", m_content.size());
    m_response += sformat("Connection: %s\r\n", m_connection.c_str());
    m_response += sformat("\r\n");
    m_response += sformat("%s", m_content.c_str());
}
//===============================================
