//===============================================
#include "GCallbackXml.h"
#include "GResponseHttpXml.h"
//===============================================
GCallbackXml::GCallbackXml()
: GCallback() {

}
//===============================================
GCallbackXml::~GCallbackXml() {

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
    m_content += sformat("<result>NOK</result>");
}
//===============================================
