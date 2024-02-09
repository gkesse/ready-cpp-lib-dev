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

    if(!isRedirectUrl()) {
        m_content += sformat("<!DOCTYPE html>\n");
        m_content += sformat("<html lang='fr'>\n");
        m_content += sformat("<head>\n");
        //
        m_content += sformat("<title>ReadyCar</title>\n");
        m_content += sformat("<meta name='viewport' content='width=device-width, maximum-scale=1.0, minimum-scale=1.0, initial-scale=1.0, user-scalable=no'/>\n");
        m_content += sformat("<meta charset='UTF-8'/>\n");
        m_content += sformat("<link rel='shortcut icon' type='image/png' href='/data/img/logo.png'/>\n");
        m_content += sformat("<link rel='stylesheet' href='/css/styles.css'/>\n");
        //
        m_content += sformat("</head>\n");
        m_content += sformat("<body>\n");
        //
        createHome();
        //
        if(m_uri == "/carpool/profil") {
            createProfil();
        }
        else if(m_uri == "/carpool/connexion") {
            createConnexion();
        }
        else if(m_uri == "/carpool/inscription") {
            createInscription();
        }
        else if(m_uri == "/carpool/inscription/email") {
            createInscriptionEmail();
        }
        // scripts
        m_content += sformat("<script src='/js/GObject.js'></script>\n");
        m_content += sformat("<script src='/js/GServer.js'></script>\n");
        m_content += sformat("<script src='/js/scripts.js'></script>\n");
        // footer
        m_content += sformat("</body>\n");
        m_content += sformat("</html>\n");
    }

    GResponseHttp lResponse;
    lResponse.setObject(*this);
    lResponse.setContent(m_content);
    lResponse.create();

    m_response += lResponse.toResponse();
}
//===============================================
bool GCarpoolUi::isRedirectUrl() {
    if(m_type == Type::REQ_TYPE_HTTP_POST) {
        if(m_uri == "/carpool/inscription/email") {
            return redirectInscriptionEmail();
        }
    }
    return false;
}
//===============================================
void GCarpoolUi::redirectUrl(const GString& _url) {
    m_content += sformat("<meta http-equiv='refresh' content='0; url=%s'>\n", _url.c_str());
}
//===============================================
void GCarpoolUi::createHome() {
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool'>ReadyCar</a>\n");
    m_content += sformat("<a href='/carpool/covoiturage'>Covoiturage</a>\n");
    m_content += sformat("<a href='/carpool/bus'>Bus</a>\n");
    m_content += sformat("<a href='/carpool/quotidien'>Covoiturage du quotidien</a>\n");
    m_content += sformat("<a href='/carpool/recherche'>Rechercher</a>\n");
    m_content += sformat("<a href='/carpool/publication'>Publier un trajet</a>\n");
    m_content += sformat("<a href='/carpool/profil'>Profil</a>\n");
    m_content += sformat("</div>\n");
}
//===============================================
void GCarpoolUi::createProfil() {
    // address
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool'>Home</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/profil'>Profil</a>\n");
    m_content += sformat("</div>\n");
    //
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool/connexion'>Connexion</a>\n");
    m_content += sformat("<a href='/carpool/inscription'>Inscription</a>\n");
    m_content += sformat("</div>\n");
}
//===============================================
void GCarpoolUi::createConnexion() {
    // address
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool'>Home</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/profil'>Profil</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/connexion'>Connexion</a>\n");
    m_content += sformat("</div>\n");
    //
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool/connexion/email'>Connexion avec une adresse email</a>\n");
    m_content += sformat("<span>Pas encore membre ? <a href='/carpool/inscription'>Inscrivez-vous</a></span>\n");
    m_content += sformat("</div>\n");
}
//===============================================
void GCarpoolUi::createInscription() {
    // address
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool'>Home</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/profil'>Profil</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/inscription'>Inscription</a>\n");
    m_content += sformat("</div>\n");
    //
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool/inscription/email'>Inscription avec une adresse email</a>\n");
    m_content += sformat("<span>Déjà membre ? <a href='/carpool/connexion'>Connectez-vous</a></span>\n");
    m_content += sformat("</div>\n");
}
//===============================================
bool GCarpoolUi::redirectInscriptionEmail() {
    GString lEmail = m_forms.getData("email");
    GString lNewletter = m_forms.getData("newsletter");
    bool isNewsletter = (lNewletter == "on");
    slog(eGINF, "Les informations de la fiche d'inscription."
                "|email=%s"
                "|lNewletter=%s", lEmail.c_str(), lNewletter.c_str());
    return isNewsletter;
}
//===============================================
void GCarpoolUi::createInscriptionEmail() {
    if(m_type == Type::REQ_TYPE_HTTP_POST) {
        GString lEmail = m_forms.getData("email");
        GString lNewletter = m_forms.getData("newsletter");
        bool isNewsletter = (lNewletter == "on");
        m_content += sformat("<div>email: %s</div>\n", lEmail.c_str());
        m_content += sformat("<div>is_newsletter: %d</div>\n", isNewsletter);
    }
    // address
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool'>Home</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/profil'>Profil</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/inscription'>Inscription</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/inscription/email'>Email</a>\n");
    m_content += sformat("</div>\n");
    // form_start
    m_content += sformat("<form action='' method='post'>\n");
    // email
    m_content += sformat("<div>\n");
    m_content += sformat("<label for='email'>Email :</label>\n");
    m_content += sformat("<input type='email' id='email' name='email' required/>\n");
    m_content += sformat("</div>\n");
    // newsletter
    m_content += sformat("<div>\n");
    m_content += sformat("<input type='checkbox' id='newsletter' name='newsletter'/>\n");
    m_content += sformat("<label for='newsletter'>Je ne souhaite pas recevoir d'informations, de bons plans et de cadeaux.</label>\n");
    m_content += sformat("</div>\n");
    // buttons
    m_content += sformat("<div>\n");
    m_content += sformat("<button type='submit'>Continuer</button>\n");
    m_content += sformat("</div>\n");
    // from_end
    m_content += sformat("</form>\n");
}
//===============================================
