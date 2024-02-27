//===============================================
class GAjax extends GObject {
    //===============================================
    constructor() {
        super();
        this.m_url = "";
        this.m_contentType = AJAX_TYPE_XML;
        this.m_method = "post";
        this.m_async = true;
        this.m_user = null;
        this.m_password = null;
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
        if(this.m_url == "") {
            console.log(sprintf("L'URL est obligatoire."));            
            return false;
        }
        if(this.m_contentType == "") {
            console.log(sprintf("Le content type est obligatoire."));            
            return false;
        }
        
        console.log(sprintf("Préparation de l'appel du serveur."+
                            "|module=%s"+
                            "|method=%s"+
                            "|url=%s"+
                            "|content_type=%s", _module, _method, this.m_url, this.m_contentType));            

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
                
                console.log(sprintf("Réponse du serveur."+
                                    "|data=%s", lData));            
                
                if(_callback) _callback(lData);
            }
        }
                
        var lMethod = this.m_method;
        var lUrl = this.m_url;
        var lContentType = this.m_contentType;
        var lAsync = this.m_async;
        var lUser = this.m_user;
        var lPassword = this.m_password;

        lXhttp.open(lMethod, lUrl, lAsync, lUser, lPassword);
        lXhttp.setRequestHeader("Content-Type", lContentType);

        var lReq = "";
        
        if(lContentType == AJAX_TYPE_FORM) {
            lReq = "req=" +_data;
        }
        else {
            lReq = _data;
        }

        lXhttp.send(lReq);
        return true;
    }
    //===============================================
}
//===============================================
