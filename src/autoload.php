<?php
//===============================================
spl_autoload_register(function ($_className) {
    require $_className . ".php";
});
//===============================================
?>