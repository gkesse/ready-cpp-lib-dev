//===============================================
class GCarpoolUi extends GServer {
    //===============================================
    constructor() {
        super();
    }
    //===============================================
    run() {
        if(this.m_module == "test") {
            this.runTest();
        }
        else if(this.m_module == "carpool") {
            this.runCarpool();
        }
        else {
            console.log(sprintf("Le module est inconnu."+
                                "|module=%s", this.m_module));
        }
    }
    //===============================================
    runTest() {
        var lObj = new GCarpool();
        lObj.setObject(this);
        lObj.run();
    }
    //===============================================
    runCarpool() {
        var lObj = new GCarpool();
        lObj.setObject(this);
        lObj.run();
    }
    //===============================================
}
//===============================================