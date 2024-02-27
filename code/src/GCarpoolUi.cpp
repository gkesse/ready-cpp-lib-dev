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
                "|uri=%s", m_uri.c_str());

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
        createLog();
        createHome();
        // test
        if(m_uri == "/carpool/test") {
            createTest();
        }
        else if(m_uri == "/carpool/test/js") {
            createTestJs();
        }
        else if(m_uri == "/carpool/test/get") {
            createTestGet();
        }
        else if(m_uri == "/carpool/test/post") {
            createTestPost();
        }
        else if(m_uri == "/carpool/test/server") {
            createTestServer();
        }
        // profil
        else if(m_uri == "/carpool/profil") {
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
        else {
            createUnknown();
        }
        // scripts
        m_content += sformat("<script src='/js/functions.js'></script>\n");
        m_content += sformat("<script src='/js/GConstant.js'></script>\n");
        m_content += sformat("<script src='/js/GXml.js'></script>\n");
        m_content += sformat("<script src='/js/GCode.js'></script>\n");
        m_content += sformat("<script src='/js/GLog.js'></script>\n");
        m_content += sformat("<script src='/js/GObject.js'></script>\n");
        m_content += sformat("<script src='/js/GAjax.js'></script>\n");
        m_content += sformat("<script src='/js/GServer.js'></script>\n");
        m_content += sformat("<script src='/js/GCarpoolCB.js'></script>\n");
        m_content += sformat("<script src='/js/GCarpoolTest.js'></script>\n");
        m_content += sformat("<script src='/js/GCarpoolEmail.js'></script>\n");
        m_content += sformat("<script src='/js/GTestJs.js'></script>\n");
        m_content += sformat("<script src='/js/scripts.js'></script>\n");
        // footer
        m_content += sformat("</body>\n");
        m_content += sformat("</html>\n");
    }

    GResponseHttp lResponse;
    lResponse.setCommon(*this);
    lResponse.setContent(m_content);
    lResponse.create();

    m_response += lResponse.toResponse();
}
//===============================================
bool GCarpoolUi::isRedirectUrl() {
    if(m_type == Type::REQ_TYPE_HTTP_POST) {
        if(m_uri == "/carpool/test/post") {
            return redirectTestPost();
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
    m_content += sformat("<a href='/carpool/test'>Test</a>\n");
    m_content += sformat("</div>\n");
}
//===============================================
void GCarpoolUi::createLog() {
    m_content += sformat("<div id='LogId' class='Log1'>\n");
    m_content += sformat("<div class='Log2'>\n");
    m_content += sformat("<div id='LogTitle'><span>Messages</span> <span onclick='call_server(\"carpool\", \"fermer_log\")'>Fermer</span></div>\n");
    m_content += sformat("<div id='LogMsg'>Logs</div>\n");
    m_content += sformat("</div>\n");
    m_content += sformat("</div>\n");
}
//===============================================
void GCarpoolUi::createTest() {
    // address
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool'>home</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/test'>test</a>\n");
    m_content += sformat("</div>\n");
    //
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool/test/js'>Js</a>\n");
    m_content += sformat("<a href='/carpool/test/get'>Get</a>\n");
    m_content += sformat("<a href='/carpool/test/post'>Post</a>\n");
    m_content += sformat("<a href='/carpool/test/server'>Server</a>\n");
    m_content += sformat("</div>\n");
}
//===============================================
void GCarpoolUi::createTestJs() {
    // address
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool'>home</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/test'>test</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/test/js'>js</a>\n");
    m_content += sformat("</div>\n");
    //
    m_content += sformat("<div>\n");
    m_content += sformat("<label for='test_js_module'>Module :</label>\n");
    m_content += sformat("<input type='text' id='test_js_module' maxlength='50'/>\n");
    m_content += sformat("<button onclick='call_test_js()'>Tester</button>\n");
    m_content += sformat("</div>\n");
}
//===============================================
void GCarpoolUi::createTestGet() {
    // address
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool'>home</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/test'>test</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/test/get'>get</a>\n");
    m_content += sformat("</div>\n");
    //
    m_content += sformat("Bonjour tout le monde.");
}
//===============================================
bool GCarpoolUi::redirectTestPost() {
    GMap lForms;
    lForms.createMap();
    lForms.loadMap(m_request);
    GString lEmail = lForms.getData("email");
    GString lNewletter = lForms.getData("newsletter");
    bool isNewsletter = (lNewletter == "on");

    slog(eGINF, "Les données du test post."
                "|email=%s"
                "|newletter=%s"
                "|is_newsletter=%d", lEmail.c_str(), lNewletter.c_str(), isNewsletter);
    return false;
}
//===============================================
void GCarpoolUi::createTestPost() {
    // post
    if(m_type == Type::REQ_TYPE_HTTP_POST) {
        GMap lForms;
        lForms.createMap();
        lForms.loadMap(m_request);
        GString lEmail = lForms.getData("email");
        GString lNewsletter = lForms.getData("newsletter");
        bool isNewsletter = (lNewsletter == "on");
        m_content += sformat("<div>email: %s</div>\n", lEmail.c_str());
        m_content += sformat("<div>is_newsletter: %d</div>\n", isNewsletter);
    }
    // address
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool'>home</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/test'>test</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/test/post'>post</a>\n");
    m_content += sformat("</div>\n");
    // form_start
    m_content += sformat("<form action='/carpool/test/post' method='post'>\n");
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
    m_content += sformat("</div>\n");
}
//===============================================
void GCarpoolUi::createTestServer() {
    // address
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool'>home</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/test'>test</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/test/server'>server</a>\n");
    m_content += sformat("</div>\n");
    //
    m_content += sformat("<div>\n");
    m_content += sformat("<div>\n");
    m_content += sformat("<label for='test_server_module'>Module :</label>\n");
    m_content += sformat("<input type='text' id='test_server_module' maxlength='50'/>\n");
    m_content += sformat("</div>\n");
    m_content += sformat("<div>\n");
    m_content += sformat("<label for='test_server_method'>Méthode :</label>\n");
    m_content += sformat("<input type='text' id='test_server_method' maxlength='50'/>\n");
    m_content += sformat("</div>\n");
    m_content += sformat("<div>\n");
    m_content += sformat("<label for='test_server_params'>Paramètres :</label>\n");
    m_content += sformat("<textarea type='text' id='test_server_params' maxlength='5000'></textarea>\n");
    m_content += sformat("</div>\n");
    m_content += sformat("<div>\n");
    m_content += sformat("<button onclick='call_carpool(\"test\", \"run\")'>Tester</button>\n");
    m_content += sformat("</div>\n");
    m_content += sformat("</div>\n");
}
//===============================================
void GCarpoolUi::createProfil() {
    // address
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool'>home</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/profil'>profil</a>\n");
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
    m_content += sformat("<a href='/carpool'>home</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/profil'>profil</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/connexion'>connexion</a>\n");
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
    m_content += sformat("<a href='/carpool'>home</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/profil'>profil</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/inscription'>inscription</a>\n");
    m_content += sformat("</div>\n");
    //
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool/inscription/email'>Inscription avec une adresse email</a>\n");
    m_content += sformat("<span>Déjà membre ? <a href='/carpool/connexion'>Connectez-vous</a></span>\n");
    m_content += sformat("</div>\n");
}
//===============================================
void GCarpoolUi::createInscriptionEmail() {
    // address
    m_content += sformat("<div>\n");
    m_content += sformat("<a href='/carpool'>home</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/profil'>profil</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/inscription'>inscription</a>\n");
    m_content += sformat(">\n");
    m_content += sformat("<a href='/carpool/inscription/email'>email</a>\n");
    m_content += sformat("</div>\n");
    // form_start
    m_content += sformat("<div>\n");
    // email
    m_content += sformat("<div>\n");
    m_content += sformat("<label for='inscription_email'>Email :</label>\n");
    m_content += sformat("<input type='email' id='inscription_email' name='inscription_email' required/>\n");
    m_content += sformat("</div>\n");
    // newsletter
    m_content += sformat("<div>\n");
    m_content += sformat("<input type='checkbox' id='inscription_newsletter' name='inscription_newsletter'/>\n");
    m_content += sformat("<label for='inscription_newsletter'>Je ne souhaite pas recevoir d'informations, de bons plans et de cadeaux.</label>\n");
    m_content += sformat("</div>\n");
    // buttons
    m_content += sformat("<div>\n");
    m_content += sformat("<button type='button' onclick='call_server(\"carpool\", \"inscription_email\")'>Continuer</button>\n");
    m_content += sformat("</div>\n");
    // from_end
    m_content += sformat("</div>\n");
}
//===============================================
void GCarpoolUi::createUnknown() {
    m_content += sformat("Page non trouvée.");
}
//===============================================
