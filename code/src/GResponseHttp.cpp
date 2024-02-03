//===============================================
#include "GResponseHttp.h"
//===============================================
enum _eGStatus {
    Continue = 100,
    SwitchingProtocol = 101,
    Processing = 102,
    EarlyHints = 103,

    Ok = 200,
    Created = 201,
    Accepted = 202,
    NonAuthoritativeInformation = 203,
    NoContent = 204,
    ResetContent = 205,
    PartialContent = 206,
    MultiStatus = 207,
    AlreadyReported = 208,
    ImUsed = 226,

    MultipleChoice = 300,
    MovedPermanently = 301,
    Found = 302,
    SeeOther = 303,
    NotModified = 304,
    UseProxy = 305,
    TemporaryRedirect = 307,
    PermanentRedirect = 308,

    BadRequest = 400,
    Unauthorized = 401,
    PaymentRequired = 402,
    Forbidden = 403,
    NotFound = 404,
    MethodNotAllowed = 405,
    NotAcceptable = 406,
    ProxyAuthenticationRequired = 407,
    RequestTimeout = 408,
    Conflict = 409,
    Gone = 410,
    LengthRequired = 411,
    PreconditionFailed = 412,
    PayloadTooLarge = 413,
    UriTooLong = 414,
    UnsupportedMediaType = 415,
    RangeNotSatisfiable = 416,
    ExpectationFailed = 417,
    MisdirectedRequest = 421,
    UnprocessableEntity = 422,
    Locked = 423,
    FailedDependency = 424,
    TooEarly = 425,
    UpgradeRequired = 426,
    PreconditionRequired = 428,
    TooManyRequests = 429,
    RequestHeaderFieldsTooLarge = 431,
    UnavailableForLegalReasons = 451,

    InternalServerError = 500,
    NotImplemented = 501,
    BadGateway = 502,
    ServiceUnavailable = 503,
    GatewayTimeout = 504,
    HttpVersionNotSupported = 505,
    VariantAlsoNegotiates = 506,
    InsufficientStorage = 507,
    LoopDetected = 508,
    NotExtended = 510,
    NetworkAuthenticationRequired = 511
};
//===============================================
#define GDEFINE_STATUS(x, y) {true, x, #x, y}
#define GDEFINE_STATUS_LAST {false, BadRequest, "Inconnu", "Inconnu"}
//===============================================
GResponseHttp::sGStatus HTTP_STATUS_MAP[] {
    GDEFINE_STATUS(Continue, "Continue")
    , GDEFINE_STATUS(SwitchingProtocol, "SwitchingProtocol")
    , GDEFINE_STATUS(Processing, "Processing")
    , GDEFINE_STATUS(EarlyHints, "EarlyHints")

    , GDEFINE_STATUS(Ok, "Ok")
    , GDEFINE_STATUS(Created, "Created")
    , GDEFINE_STATUS(Accepted, "Accepted")
    , GDEFINE_STATUS(NonAuthoritativeInformation, "NonAuthoritativeInformation")
    , GDEFINE_STATUS(NoContent, "NoContent")
    , GDEFINE_STATUS(ResetContent, "ResetContent")
    , GDEFINE_STATUS(PartialContent, "PartialContent")
    , GDEFINE_STATUS(MultiStatus, "MultiStatus")
    , GDEFINE_STATUS(AlreadyReported, "AlreadyReported")
    , GDEFINE_STATUS(ImUsed, "ImUsed")

    , GDEFINE_STATUS(MultipleChoice, "MultipleChoice")
    , GDEFINE_STATUS(MovedPermanently, "MovedPermanently")
    , GDEFINE_STATUS(Found, "Found")
    , GDEFINE_STATUS(SeeOther, "SeeOther")
    , GDEFINE_STATUS(NotModified, "NotModified")
    , GDEFINE_STATUS(UseProxy, "UseProxy")
    , GDEFINE_STATUS(TemporaryRedirect, "TemporaryRedirect")
    , GDEFINE_STATUS(PermanentRedirect, "PermanentRedirect")

    , GDEFINE_STATUS(BadRequest, "BadRequest")
    , GDEFINE_STATUS(Unauthorized, "Unauthorized")
    , GDEFINE_STATUS(PaymentRequired, "PaymentRequired")
    , GDEFINE_STATUS(Forbidden, "Forbidden")
    , GDEFINE_STATUS(NotFound, "NotFound")
    , GDEFINE_STATUS(MethodNotAllowed, "MethodNotAllowed")
    , GDEFINE_STATUS(NotAcceptable, "NotAcceptable")
    , GDEFINE_STATUS(ProxyAuthenticationRequired, "ProxyAuthenticationRequired")
    , GDEFINE_STATUS(RequestTimeout, "RequestTimeout")
    , GDEFINE_STATUS(Conflict, "Conflict")
    , GDEFINE_STATUS(Gone, "Gone")
    , GDEFINE_STATUS(LengthRequired, "LengthRequired")
    , GDEFINE_STATUS(PreconditionFailed, "PreconditionFailed")
    , GDEFINE_STATUS(PayloadTooLarge, "PayloadTooLarge")
    , GDEFINE_STATUS(UriTooLong, "UriTooLong")
    , GDEFINE_STATUS(UnsupportedMediaType, "UnsupportedMediaType")
    , GDEFINE_STATUS(RangeNotSatisfiable, "RangeNotSatisfiable")
    , GDEFINE_STATUS(ExpectationFailed, "ExpectationFailed")
    , GDEFINE_STATUS(MisdirectedRequest, "MisdirectedRequest")
    , GDEFINE_STATUS(UnprocessableEntity, "UnprocessableEntity")
    , GDEFINE_STATUS(Locked, "Locked")
    , GDEFINE_STATUS(FailedDependency, "FailedDependency")
    , GDEFINE_STATUS(TooEarly, "TooEarly")
    , GDEFINE_STATUS(UpgradeRequired, "UpgradeRequired")
    , GDEFINE_STATUS(PreconditionRequired, "PreconditionRequired")
    , GDEFINE_STATUS(TooManyRequests, "TooManyRequests")
    , GDEFINE_STATUS(RequestHeaderFieldsTooLarge, "RequestHeaderFieldsTooLarge")
    , GDEFINE_STATUS(UnavailableForLegalReasons, "UnavailableForLegalReasons")

    , GDEFINE_STATUS(InternalServerError, "InternalServerError")
    , GDEFINE_STATUS(NotImplemented, "NotImplemented")
    , GDEFINE_STATUS(BadGateway, "BadGateway")
    , GDEFINE_STATUS(ServiceUnavailable, "ServiceUnavailable")
    , GDEFINE_STATUS(GatewayTimeout, "GatewayTimeout")
    , GDEFINE_STATUS(HttpVersionNotSupported, "HttpVersionNotSupported")
    , GDEFINE_STATUS(VariantAlsoNegotiates, "VariantAlsoNegotiates")
    , GDEFINE_STATUS(InsufficientStorage, "InsufficientStorage")
    , GDEFINE_STATUS(LoopDetected, "LoopDetected")
    , GDEFINE_STATUS(NotExtended, "NotExtended")
    , GDEFINE_STATUS(NetworkAuthenticationRequired, "NetworkAuthenticationRequired")

    , GDEFINE_STATUS_LAST
};
//===============================================
GResponseHttp::GResponseHttp()
: GObject()
, m_status(Ok)
, m_contentType("text/html; charset=UTF-8")
, m_connection("Closed") {

}
//===============================================
GResponseHttp::~GResponseHttp() {

}
//===============================================
void GResponseHttp::setStatus(int _status) {
    m_status = _status;
}
//===============================================
void GResponseHttp::setContentType(const GString& _contentType) {
    m_contentType = _contentType;
}
//===============================================
void GResponseHttp::setData(const GString& _data) {
    m_data = _data;
}
//===============================================
GString GResponseHttp::toReason(int _status) const {
    int i = 0;
    while(1) {
        sGStatus lStatus = HTTP_STATUS_MAP[i++];
        if(!lStatus.flag) break;
        if(lStatus.code == _status) return lStatus.name;
    }
    return "BadRequest";
}
//===============================================
GString GResponseHttp::toResponse() const {
    GString lData = "";
    lData += sformat("HTTP/1.1 %d %s\r\n", m_status, toReason(m_status).c_str());
    lData += sformat("Content-Type: %s\r\n", m_contentType.c_str());
    lData += sformat("Content-Length: %d\r\n", m_data.size());
    lData += sformat("Connection: %s\r\n", m_connection.c_str());
    lData += sformat("\r\n");
    lData += sformat("%s", m_data.c_str());
    return lData;
}
//===============================================
GString GResponseHttp::toError() const {
    GResponseHttp lResponse;
    lResponse.setStatus(NotFound);
    lResponse.setData("Page non trouvée.");
    return lResponse.toResponse();
}
//===============================================
