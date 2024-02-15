//===============================================
#include "GDispatcherHttpGet.h"
#include "GResponseHttp.h"
#include "GPage.h"
#include "GFile.h"
#include "GMimeType.h"
//===============================================
GDispatcherHttpGet::GDispatcherHttpGet()
: GDispatcherHttp() {

}
//===============================================
GDispatcherHttpGet::~GDispatcherHttpGet() {

}
//===============================================
void GDispatcherHttpGet::run() {
    slog(eGINF, "Traitement de la requête HTTP GET."
                "|uri=%s", m_uri.c_str());

    if(!loadResource()) {
        if(m_uri.startsWith("/carpool")) {
            runCarpool();
        }
        else {
            createUnknown();
        }
    }
    else {
        slog(eGINF, "La ressource a bien été chargée."
                    "|uri=%s", m_uri.c_str());
    }
}
//===============================================
bool GDispatcherHttpGet::loadResource() {
    if(!isResource()) {
        slog(eGERR, "La ressource n'est pas autorisée."
                    "|uri=%s", m_uri.c_str());
        return false;
    }
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
                lFile.setCommon(*this);
                GResponseHttp lResponse;
                lResponse.setCommon(*this);
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
            lMimeType.setCommon(*this);
            GResponseHttp lResponse;
            lResponse.setCommon(*this);
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
bool GDispatcherHttpGet::isResource() const {
    if(m_uri.startsWith("/data/img")) return true;
    if(m_uri.startsWith("/css")) return true;
    if(m_uri.startsWith("/js")) return true;
    return false;
}
//===============================================
void GDispatcherHttpGet::runCarpool() {
    GPage lPage;
    lPage.setCommon(*this);
    lPage.setDispatcher(*this);
    lPage.createCarpool();
    m_response += lPage.toResponse();
}
//===============================================
void GDispatcherHttpGet::createUnknown() {
    GPage lPage;
    lPage.setCommon(*this);
    lPage.setDispatcher(*this);
    lPage.createUnknown();
    m_response += lPage.toResponse();
}
//===============================================
