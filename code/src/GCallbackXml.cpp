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
        m_content += sformat("<result>OK</result>");
    }
    GResponseHttpXml lResponse;
    lResponse.setCommon(*this);
    lResponse.setContent(m_content);
    lResponse.create();
    m_response += lResponse.toResponse();
}
//===============================================
void GCallbackXml::createUnknown() {
    m_content += sformat("<result>KO</result>");
}
//===============================================
