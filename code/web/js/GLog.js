//===============================================
class GCarpool extends GObject {
    //===============================================
    constructor() {
        super();
    }
    //===============================================
    run() {
        if(this.m_method == "") {
            console.log(sprintf("La méthode est obligatoire."+
                                "|module=%s", this.m_module));
        }
        else if(this.m_method == "inscription_email") {
            this.runInscriptionEmail();
        }
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
}
//===============================================