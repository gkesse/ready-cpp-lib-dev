//===============================================
class GCarpoolTest extends GServer {
    //===============================================
    constructor() {
        super();
        var lAjax = new GAjax();
        lAjax.m_url = "/callback/carpool/test";
        this.m_ajax = lAjax
    }
    //===============================================
    readModule() {
        var lObj = document.getElementById("test_server_module");
        this.m_module = lObj.value;
    }
    //===============================================
    readMethod() {
        var lObj = document.getElementById("test_server_method");
        this.m_method = lObj.value;
    }
    //===============================================
    readParams() {
        var lObj = document.getElementById("test_server_params");
        this.m_params = lObj.value;
    }
    //===============================================
    run() {
        if(this.m_method == "run") {
            this.runTest();
        }
        else {
            console.log(sprintf("La méthode est inconnue."+
                                "|module=%s"+
                                "|method=%s", this.m_module, this.m_method));
        }
    }
    //===============================================
    runTest() {
        this.readModule();
        this.readMethod();
        this.readParams();
        var lAjax = this.m_ajax;
        lAjax.call(this.m_module, this.m_method, this.m_params, this.runTestCB);
    }
    //===============================================
    runTestCB(_data) {
        var lObj = new GCarpoolTest();
        lObj.setResponse(_data);
        if(lObj.isOK()) {
            console.log(sprintf("Message du serveur."+
                                "|msg=%s", lObj.getLog()));
        }
    }
    //===============================================
}
//===============================================