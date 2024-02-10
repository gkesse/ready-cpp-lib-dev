//===============================================
function call_server(_module, _method, _obj = null, _params = null) {
    var lServer = new GServer();
    lServer.setObjects(_module, _method, _obj, _params);
    lServer.run();
    return true;
}
//===============================================
