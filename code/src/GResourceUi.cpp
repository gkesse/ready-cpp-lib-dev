//===============================================
#include "GResourceUi.h"
#include "GFile.h"
#include "GMimeType.h"
//===============================================
GResourceUi::GResourceUi()
: GPage() {

}
//===============================================
GResourceUi::~GResourceUi() {

}
//===============================================
bool GResourceUi::loadResource() {
    if(!isResource()) {
        slog(eGWAR, "La ressource n'est pas autorisée."
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
                m_content = lFile.readData();
                return true;
            }
        }
        // la ressource est un fichier.
        else {
            // on charge la ressource.
            GFile lFile(lPath, GFile::Mode::FILE_MODE_READ_BIN);
            GMimeType lMimeType;
            lMimeType.setCommon(*this);
            m_contentType = lMimeType.getMimeType(lPath.getExtension());
            m_content = lFile.readData();
            return true;
        }
    }
    return false;
}
//===============================================
bool GResourceUi::isResource() const {
    if(m_uri.startsWith("/data/img")) return true;
    if(m_uri.startsWith("/css")) return true;
    if(m_uri.startsWith("/js")) return true;
    return false;
}
//===============================================
