//===============================================
class GCarpoolCB extends GServer {
    //===============================================
    constructor() {
        super();
    }
    //===============================================
    run() {
        if(this.m_module == "test") {
            this.runTest();
        }
        else if(this.m_module == "email") {
            this.runEmail();
        }
        else {
            console.log(sprintf("Le module est inconnu."+
                                "|module=%s"+
                                "|method=%s", this.m_module, this.m_method));
        }
    }
    //===============================================
    runTest() {
        var lObj = new GCarpoolTest();
        lObj.setServer(this);
        lObj.run();
    }
    //===============================================
    runEmail() {
        var lObj = new GCarpoolEmail();
        lObj.setServer(this);
        lObj.run();
    }
    //===============================================
}
//===============================================