<?php
//===============================================
class GTest {
    //===============================================
    public function __construct() {
        
    }
    //===============================================
    public function run($_module, $_method) {
        if($_method == "string") {
            $this->runString($_module, $_method);
        }
        else if($_method == "user") {
            $this->runUser($_module, $_method);
        }
    }
    //===============================================
    public function runString($_module, $_method) {
        echo sprintf("<p>Bonjour tout le monde.</p>\n");
    }
    //===============================================
    public function runUser($_module, $_method) {
        $lUserUi = new GUserUi();
        $lUserUi->run();
    }
    //===============================================
}
//===============================================
?>