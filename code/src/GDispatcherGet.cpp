//===============================================
#include "GDispatcherGet.h"
#include "GResponseHttp.h"
#include "GPage.h"
#include "GFile.h"
#include "GMimeType.h"
//===============================================
GDispatcherGet::GDispatcherGet()
: GDispatcherHttp() {

}
//===============================================
GDispatcherGet::~GDispatcherGet() {

}
//===============================================
void GDispatcherGet::run() {
    slog(eGINF, "Traitement de la requête HTTP GET."
                "|adresse_ip=%s"
                "|port=%d"
                "|process=%d"
                "|uri=%s", m_addressIP.c_str(), m_port, m_pid, m_uri.c_str());

    if(!loadResource()) {
        if(m_uri == "/hello/world") {
            runHelloWorld();
        }
        else if(isPage("/carpool")) {
            runCarpool();
        }
        else {
            runUnknown();
        }
    }
    else {
        slog(eGINF, "La ressource a bien été chargée."
                    "|adresse_ip=%s"
                    "|port=%d"
                    "|process=%d"
                    "|uri=%s", m_addressIP.c_str(), m_port, m_pid, m_uri.c_str());
    }
}
//===============================================
bool GDispatcherGet::loadResource() {
    GString lPath = sres(m_uri);
    struct stat lStat;
    // la ressource existe ?
    if(!stat(lPath.c_str(), &lStat)) {
        // la ressource est un répertoire ?
        if(lStat.st_mode & S_IFDIR) {
            if(lPath.back() != '/') lPath += "/";
            lPath += "index.html";
            // le fichier (index.html) existe ?
            if(!stat(lPath.c_str(), &lStat) && !(lStat.st_mode & S_IFDIR)) {
                // on charge le fichier (index.html).
                GFile lFile(lPath, GFile::Mode::FILE_MODE_READ_BIN);
                lFile.setObject(*this);
                GResponseHttp lResponse;
                lResponse.setObject(*this);
                lResponse.setContent(lFile.readData());
                lResponse.create();
                m_response += lResponse.toResponse();
                return true;
            }
        }
        // la ressource est un fichier.
        else {
            // on charge la ressource.
            GFile lFile(lPath, GFile::Mode::FILE_MODE_READ_BIN);
            GMimeType lMimeType;
            lMimeType.setObject(*this);
            GResponseHttp lResponse;
            lResponse.setObject(*this);
            lResponse.setContentType(lMimeType.getMimeType(lPath.getExtension()));
            lResponse.setContent(lFile.readData());
            lResponse.create();
            m_response += lResponse.toResponse();
            return true;
        }
    }
    return false;
}
//===============================================
bool GDispatcherGet::isPage(const GString& _page) {
    if(!m_uri.startsWith(_page)) return false;
    m_pageId = m_uri.substr(_page.size());
    if(m_pageId.back() == '/') m_pageId.pop();
    return true;
}
//===============================================
void GDispatcherGet::runHelloWorld() {
    GPage lPage;
    lPage.setObject(*this);
    lPage.setDispatcher(*this);
    lPage.createHelloWrold();
    m_response += lPage;
}
//===============================================
void GDispatcherGet::runCarpool() {
    GPage lPage;
    lPage.setObject(*this);
    lPage.setDispatcher(*this);
    lPage.createCarpool();
    m_response += lPage;
}
//===============================================
void GDispatcherGet::runUnknown() {
    GPage lPage;
    lPage.setObject(*this);
    lPage.setDispatcher(*this);
    lPage.createUnknown();
    m_response += lPage;
}
//===============================================
