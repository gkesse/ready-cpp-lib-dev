//===============================================
function call_carpool(_module, _method = "", _obj = null, _params = "") {
    var lServer = new GCarpoolCB();
    lServer.setParams(_module, _method, _obj, _params);
    lServer.run();
}
//===============================================
function call_test_js() {
    var lServer = new GTestJs();
    lServer.readModule();
    lServer.run();
}
//===============================================
