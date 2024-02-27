//===============================================
#include "GCallbackXml.h"
#include "GResponseHttpXml.h"
#include "GCarpoolCB.h"
//===============================================
GCallbackXml::GCallbackXml()
: GCallback() {

}
//===============================================
GCallbackXml::~GCallbackXml() {

}
//===============================================
void GCallbackXml::run() {
    if(m_uri.startsWith("/callback/carpool")) {
        runCarpool();
    }
    else {
        slog(eGERR, "Le callback n'est pas géré."
                    "|uri=%s"
                    "|content_type=%s"
                    "|request=%s", m_uri.c_str(), m_contentType.c_str(), m_request.c_str());
        createUnknown();
    }
}
//===============================================
void GCallbackXml::runCarpool() {
    GCarpoolCB lObj;
    lObj.setCommon(*this);
    lObj.setPage(*this);
    lObj.run();
    m_response += lObj.toResponse();
}
//===============================================
void GCallbackXml::createResponse() {
    if(m_content.isEmpty()) {
        if(m_logs.isEmpty()) {
            createUnknown();
        }
        else {
            m_content += m_logs.serialize();
        }
    }
    GResponseHttpXml lResponse;
    lResponse.setCommon(*this);
    lResponse.setContent(m_content);
    lResponse.create();
    m_response += lResponse.toResponse();
}
//===============================================
void GCallbackXml::createOK() {
    m_content += sformat("<result>OK</result>");
}
//===============================================
void GCallbackXml::createUnknown() {
    m_content += sformat("<result>KO</result>");
}
//===============================================
