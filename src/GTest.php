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
    }
    //===============================================
    public function runString($_module, $_method) {
        echo "Bonjour tout le monde.";
    }
    //===============================================
}
//===============================================
?>