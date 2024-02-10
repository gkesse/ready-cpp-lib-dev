//===============================================
class GAjax extends GObject {
    //===============================================
    constructor() {
        super();
    }
    //===============================================
    call(_module, _method, _params = "", _callback = null) {
        if(_module == "") {
            console.log(sprintf("Le module est obligatoire."));            
            return false;
        }
        if(_method == "") {
            console.log(sprintf("La méthode est obligatoire."));            
            return false;
        }
        
        console.log(sprintf("Préparation de l'appel."+
                            "|module=%s"+
                            "|method=%s", _module, _method));            

        var lDom = new GCode();
        lDom.createDoc();
        lDom.addData("manager", "module", _module);
        lDom.addData("manager", "method", _method);
        lDom.loadData(_params);
        var lData = lDom.toString();
        this.callServer(lData, _callback);
        return true;
    }
    //===============================================
    callServer(_data, _callback) {
        if(_data == "") {
            console.log(sprintf("La donnée est obligatoire."));            
            return false;
        }
        
        console.log(sprintf("Appel du serveur."+
                            "|data=%s", _data));            

        var lXhttp = new XMLHttpRequest();
        lXhttp.onreadystatechange = function() {
            if(this.readyState == 4 && this.status == 200) {
                var lData = this.responseText;
                
                console.log(sprintf("Retour du serveur."+
                                    "|data=%s", lData));            

                if(_callback) _callback(lData);
            }
        }
        
        var lMethod = "POST";
        var lUrl = "/carpool/callback";
        var lContentType = "application/x-www-form-urlencoded";
        var lAsync = true;
        var lUser = null;
        var lPassword = null;

        lXhttp.open(lMethod, lUrl, lAsync, lUser, lPassword);
        lXhttp.setRequestHeader("Content-Type", lContentType);

        var lReq = "";
        lReq += sprintf("req=%s", _data);
        lXhttp.send(lReq);
        return true;
    }
    //===============================================
}
//===============================================
