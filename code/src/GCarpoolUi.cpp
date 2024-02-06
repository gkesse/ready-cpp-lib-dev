//===============================================
#include "GCarpoolUi.h"
//===============================================
GCarpoolUi::GCarpoolUi()
: GPage() {

}
//===============================================
GCarpoolUi::~GCarpoolUi() {

}
//===============================================
void GCarpoolUi::init() {

}
//===============================================
void GCarpoolUi::create() {
    slog(eGINF, "Création de la page carpool."
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
    lContent += sformat("<title>ReadyCar</title>\n");
    lContent += sformat("<meta name='viewport' content='width=device-width, maximum-scale=1.0, minimum-scale=1.0, initial-scale=1.0, user-scalable=no'/>\n");
    lContent += sformat("<meta charset='UTF-8'/>\n");
    lContent += sformat("<link rel='shortcut icon' type='image/png' href='/data/img/logo.png'/>\n");
    lContent += sformat("<link rel='stylesheet' href='/css/styles.css'/>\n");
    //
    lContent += sformat("</head>\n");
    lContent += sformat("<body>\n");
    //
    lContent += sformat("<div>\n");
    lContent += sformat("<a href='/carpool'>ReadyCar</a>\n");
    lContent += sformat("<a href='/carpool'>Covoiturage</a>\n");
    lContent += sformat("<a href='/carpool'>Bus</a>\n");
    lContent += sformat("<a href='/carpool'>Covoiturage du quotidien</a>\n");
    lContent += sformat("<a href='/carpool'>Rechercher</a>\n");
    lContent += sformat("<a href='/carpool'>Publier un trajet</a>\n");
    lContent += sformat("<a href='/carpool/connexion'>Connexion</a>\n");
    lContent += sformat("</div>\n");
    //
    lContent += sformat("<script src='/js/scripts.js'></script>\n");
    //
    lContent += sformat("</body>\n");
    lContent += sformat("</html>\n");

    GResponseHttp lResponse;
    lResponse.setObject(*this);
    lResponse.setContent(lContent);
    lResponse.create();

    m_response += lResponse.toResponse();
}
//===============================================
