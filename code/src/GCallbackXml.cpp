//===============================================
#include "GCallbackXml.h"
#include "GCarpoolCB.h"
#include "GChatCB.h"
//===============================================
GCallbackXml::GCallbackXml()
: GCallback() {
    m_contentType = RESPONSE_HTTP_XML;
}
//===============================================
GCallbackXml::~GCallbackXml() {

}
//===============================================
void GCallbackXml::run() {
    if(m_uri.startsWith("/callback/carpool")) {
        runCarpool();
    }
    else if(m_uri.startsWith("/callback/chat")) {
        runChat();
    }
    else {
        slog(eGERR, "Le callback n'est pas géré."
                    "|uri=%s"
                    "|content_type=%s"
                    "|request=%s", m_uri.c_str(), m_contentTypeReq.c_str(), m_request.c_str());
        createUnknown();
    }
    createResponse();
}
//===============================================
void GCallbackXml::runCarpool() {
    GCarpoolCB lObj;
    lObj.setCommon(*this);
    lObj.setPage(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    setResponseHttp(lObj);
}
//===============================================
void GCallbackXml::runChat() {
    GChatCB lObj;
    lObj.setCommon(*this);
    lObj.setPage(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    setResponseHttp(lObj);
}
//===============================================
void GCallbackXml::createResponse() {
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
void GCallbackXml::createOK() {
    GXml lDom;
    lDom.createDoc("datas");
    lDom.addData("result", "success");
    lDom.addData("msg", "L'opération s'est bien déroulée.");
    m_content += lDom.toString();
}
//===============================================
void GCallbackXml::createUnknown() {
    GXml lDom;
    lDom.createDoc("datas");
    lDom.addData("result", "error");
    lDom.addData("msg", "Un problème a été rencontré");
    m_content += lDom.toString();
}
//===============================================
