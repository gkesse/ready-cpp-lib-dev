//===============================================
#include "GPage.h"
#include "GDispatcherHttp.h"
//===============================================
GPage::GPage()
: GResponseHttp() {



}
//===============================================
GPage::~GPage() {

}
//===============================================
void GPage::setPage(const GPage& _obj) {
    m_method            = _obj.m_method;
    m_uri               = _obj.m_uri;
    m_version           = _obj.m_version;
    m_contentTypeReq    = _obj.m_contentTypeReq;
    m_secWebSocketKey   = _obj.m_secWebSocketKey;
    m_request           = _obj.m_request;
    m_type              = _obj.m_type;
}
//===============================================
void GPage::setRequest(const GRequest& _obj) {
    m_method            = _obj.getHttp().getMethod();
    m_uri               = _obj.getHttp().getUri();
    m_version           = _obj.getHttp().getVersion();
    m_contentTypeReq    = _obj.getHttp().getContentType();
    m_secWebSocketKey   = _obj.getHttp().getSecWebSocketKey();
    m_request           = _obj.getHttp().getRequest();
    m_type              = _obj.getType();
}
//===============================================
void GPage::setDispatcher(const GDispatcherHttp& _obj) {
    m_method            = _obj.getMethod();
    m_uri               = _obj.getUri();
    m_version           = _obj.getVersion();
    m_contentTypeReq    = _obj.getContentType();
    m_secWebSocketKey   = _obj.getSecWebSocketKey();
    m_request           = _obj.getRequest();
    m_type              = _obj.getType();
}
//===============================================
void GPage::createResponse() {
    if(m_content.isEmpty()) {
        if(m_logs.isEmpty()) {
            createUnknown();
        }
        else if(m_logs.hasErrors()) {
            createUnknown();
        }
        else {
            createOK();
        }
    }

    GResponseHttp lResponse;
    lResponse.setCommon(*this);
    lResponse.setResponseHttp(*this);
    lResponse.create();
    setResponse(lResponse);
}
//===============================================
void GPage::createOK() {
    m_content += sformat("L'opération s'est bien déroulée.\n");
}
//===============================================
void GPage::createUnknown() {
    m_content += sformat("Page non trouvée.\n");
}
//===============================================
