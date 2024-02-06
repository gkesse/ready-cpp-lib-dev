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
        else if(m_uri == "/home") {
            runHome();
        }
        else {
            runUnknown();
        }
    }
    else {
        slog(eGINF, "Traitement de la requête HTTP GET."
                    "|adresse_ip=%s"
                    "|port=%d"
                    "|process=%d"
                    "|uri=%s", m_addressIP.c_str(), m_port, m_pid, m_uri.c_str());
    }
}
//===============================================
bool GDispatcherGet::loadResource() {
    GString lPath = spath(m_uri);
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
void GDispatcherGet::runHelloWorld() {
    GPage lPage;
    lPage.setObject(*this);
    lPage.setDispatcher(*this);
    lPage.createHelloWrold();
    m_response += lPage;
}
//===============================================
void GDispatcherGet::runHome() {
    GPage lPage;
    lPage.setObject(*this);
    lPage.setDispatcher(*this);
    lPage.createHome();
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
