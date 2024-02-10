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
        else if(this.m_module == "xml") {
            this.runXml();
        }
        else if(this.m_module == "code") {
            this.runCode();
        }
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
    runCode() {
        var lDom = new GCode();
        lDom.createDoc();
        lDom.createDatas();
        lDom.createDatas();
        lDom.createCode("logs");
        lDom.createCode("logs");
        lDom.addData("logs", "type", "error");
        lDom.addData("logs", "side", "client_js");
        lDom.addData("logs", "msg", "Le module est obligatoire.");
        console.log(lDom.toString());
        //
        lDom.addData("logs", "side", "server_cpp");
        console.log(lDom.toString());
        //
        console.log(lDom.getData("logs", "msg"));
        //
        console.log(lDom.toDatas(lDom.toString()));
        //
        console.log(lDom.toCode(lDom.toDatas(lDom.toString())));
        //
        console.log(lDom.toString());
        lDom.loadData(lDom.toString());
        console.log(lDom.toString());
        //
        var lLog = new GLog();
        lLog.addLog("L'opération a réussi.");
        lLog.addError("Le module est en erreur.");
        lLog.addData("x + y = 20.");
        console.log(lLog.serialize());
        //
        lLog.loadFromMap(1);
        console.log(lLog.serialize());
        //
        lLog.m_msg = "L'opération s'est bien déroulée.";
        lLog.loadToMap(1);
        console.log(lLog.serialize());
    }
    //===============================================
}
//===============================================