//===============================================
class GTestJs extends GObject {
    //===============================================
    constructor() {
        super();
    }
    //===============================================
    run() {
        if(this.m_module == "") {
            console.log(sprintf("Le module est obligatoire."));
        }
        // xml
        else if(this.m_module == "xml") {
            this.runXml();
        }
        //
        else {
            console.log(sprintf("Le module est inconnu."+
                                "|module=%s", this.m_module));
        }
    }
    //===============================================
    runXml() {
        var lDom = new GXml();
        lDom.createDoc();
        var lDom2 = lDom.addObj("datas");
        var lDom3 = lDom2.addObj("data");
        lDom3.addData("code", "logs");
        lDom3.addData("type", "error");
        lDom3.addData("side", "client_js");
        lDom3.addData("msg", "Le module est obligatoire.");
        console.log(lDom.toString());
        //
        console.log(lDom3.toNode());
        //
        var lDom4 = new GXml();
        lDom4.createDoc();
        lDom4.loadNode(lDom3.toNode());
        console.log(lDom4.toString());
        //
        lDom2.loadNode(lDom3.toNode());
        console.log(lDom.toString());
        //
        console.log(lDom.countNode("/rdv/datas/data"));
        //
        lDom.getNode("/rdv/datas/data[position()=2]/side").setValue("server_cpp")
        console.log(lDom.toString());
        //
        var lDom5 = new GXml();
        lDom5.createDoc();
        lDom5.createNode("/rdv/datas/data/code", "logs");
        lDom5.createNode("/rdv/datas/data/code", "logs");
        console.log(lDom5.toString());
    }
    //===============================================
}
//===============================================