//===============================================
class GServer extends GObject {
    //===============================================
    constructor() {
        super();
    }
    //===============================================
    run() {
        if(this.m_module == "") {
            console.log(sprintf("Le module est obligatoire."));
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
    runCarpool() {
        var lObj = new GCarpool();
        lObj.setObject(this);
        lObj.run();
    }
    //===============================================
}
//===============================================