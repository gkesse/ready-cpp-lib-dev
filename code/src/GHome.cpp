//===============================================
#include "GHome.h"
//===============================================
GHome::GHome()
: GPage() {

}
//===============================================
GHome::~GHome() {

}
//===============================================
void GHome::init() {
    m_logo = spath("/data/img/logo.png");

    if(m_logo.isEmpty()) {
        slog(eGERR, "Le chemin du logo n'a pas été configuré.");
    }
}
//===============================================
void GHome::create() {
    slog(eGINF, "Création de la page Home."
                "|adresse_ip=%s"
                "|port=%d"
                "|process=%d"
                "|uri=%s", m_addressIP.c_str(), m_port, m_pid, m_uri.c_str());

    init();

    GString lContent;
    lContent += sformat("<!DOCTYPE html>\n");
    lContent += sformat("<html lang='fr'>\n");
    lContent += sformat("<head>\n");
    //
    lContent += sformat("<title>ReadyPad</title>\n");
    lContent += sformat("<meta name='viewport' content='width=device-width, maximum-scale=1.0, minimum-scale=1.0, initial-scale=1.0, user-scalable=no'/>\n");
    lContent += sformat("<meta charset='UTF-8'/>\n");
    lContent += sformat("<link rel='shortcut icon' type='image/png' href='%s'/>\n", m_logo.c_str());
    //
    lContent += sformat("</head>\n");
    lContent += sformat("<body>\n");
    lContent += sformat("<h1>Bonjour Tout le Monde.</h1>\n");
    lContent += sformat("</body>\n");
    lContent += sformat("</html>\n");

    GResponseHttp lResponse;
    lResponse.setContent(lContent);
    lResponse.create();

    m_response += lResponse.toResponse();
}
//===============================================
