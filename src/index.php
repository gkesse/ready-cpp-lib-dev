<?php
//===============================================
require "autoload.php";
//===============================================
echo sprintf("<!DOCTYPE html>\n");
echo sprintf("<html>\n");
echo sprintf("<head>\n");
//===============================================
echo sprintf("<title>ReadyApp</title>\n");
echo sprintf("<link rel='icon' type='image/x-icon' href='/data/img/favicon.ico'>\n");
echo sprintf("<link rel='stylesheet' href='/css/styles.css'>\n");
//===============================================
echo sprintf("</head>\n");
echo sprintf("<body>\n");
//===============================================
echo sprintf("<script src='/js/scripts.js'></script>\n");
echo sprintf("<script src='/js/GServer.js'></script>\n");
//===============================================
echo sprintf("<script>callServer('test', 'hello');</script>\n");
//===============================================
echo sprintf("</body>\n");
echo sprintf("</html>\n");
//===============================================
?>