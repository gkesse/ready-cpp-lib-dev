//===============================================
class GCarpool extends GObject {
    //===============================================
    constructor() {
        super();
        this.m_email = "";
        this.m_password = "";
    }
    //===============================================
    serialize(_code = "carpool") {
        var lDom = new GCode();
        lDom.createDoc();
        lDom.addData(_code, "email", this.m_email);
        lDom.addData(_code, "password", this.m_password);
        return lDom.toString();
    }
    //===============================================
    deserialize(_data, _code = "carpool") {
        var lData = new GCode();
        lData.loadXml(_data);
        this.m_email = lData.getData(_code, "email");
        this.m_password = lData.getData(_code, "password");
    }
    //===============================================
    run() {
        if(this.m_method == "") {
            console.log(sprintf("La méthode est obligatoire."+
                                "|module=%s", this.m_module));
        }
        // inscription
        else if(this.m_method == "inscription_email") {
            this.runInscriptionEmail();
        }
        // log
        else if(this.m_method == "fermer_log") {
            this.runFermerLog();
        }
        // test
        else if(this.m_method == "test_js") {
            this.runTestJs();
        }
        //
        else {
            console.log(sprintf("La méthode est inconnue."+
                                "|module=%s"+
                                "|method=%s", this.m_module, this.m_method));
        }
    }
    //===============================================
    runInscriptionEmail() {
        var lEmailObj = document.getElementById("email");
        var lNewsletterObj = document.getElementById("newsletter");
        var lEmail = lEmailObj.value;
        var lNewsletter = lNewsletterObj.value;
        console.log(sprintf("Inscription par email."+
                            "|email=%s"+
                            "|newsletter=%s", lEmail, lNewsletter));
    }
    //===============================================
    runFermerLog() {
        var lLogObj = document.getElementById("LogId");
        lLogObj.style.display = "none";
        console.log(sprintf("Fermeture des logs."));
    }
    //===============================================
    runTestJs() {
        var lModuleObj = document.getElementById("test_js_module");
        var lModule = lModuleObj.value;
        var lObj = new GTestJs();
        lObj.setObjects(lModule);
        lObj.run();
    }
    //===============================================
}
//===============================================