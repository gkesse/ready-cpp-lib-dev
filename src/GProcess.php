<?php
//===============================================
class GProcess {
    //===============================================
    public function __construct() {
        
    }
    //===============================================
    public function run($_module, $_method) {
        if($_module == "test") {
            $this->runTest($_module, $_method);
        }
    }
    //===============================================
    public function runTest($_module, $_method) {
        $lObj = new GTest();
        $lObj->run($_module, $_method);
    }
    //===============================================
}
//===============================================
?>