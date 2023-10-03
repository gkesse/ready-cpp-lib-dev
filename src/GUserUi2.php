<?php
//===============================================
class GUserUi2 {
    //===============================================
    public function __construct() {
        
    }
    //===============================================
    public function run() {
        echo "<pre>";var_dump($_POST);echo "</pre>";

        echo sprintf("<form class='user1' action='/' method='post'>\n");
        // title
        echo sprintf("<div class='user2'><div class='user3'>Création d'un utilisateur</div></div>\n");
        // body
        echo sprintf("<div class='user4'>\n");
        // username
        echo sprintf("<div class='user5'>\n");
        echo sprintf("<label class='user6' for='username'>Nom d'utilisateur:</label>\n");
        echo sprintf("<input class='user7' type='text' id='username' name='username'>\n");
        echo sprintf("</div>\n");
        // password
        echo sprintf("<div class='user5'>\n");
        echo sprintf("<label class='user6' for='password'>Mot de passe:</label>\n");
        echo sprintf("<input class='user7' type='password' id='password' name='password'>\n");
        echo sprintf("</div>\n");
        // buttons
        echo sprintf("<div class='user8'>\n");
        echo sprintf("<div class='user9'>\n");
        //
        echo sprintf("<button class='user10' type='submit' name='action' value='new'>Nouveau</button>\n");
        echo sprintf("<button class='user10' type='submit' name='action' value='delete'>Supprimer</button>\n");
        echo sprintf("<button class='user10' type='submit' name='action' value='search'>Rechercher</button>\n");
        echo sprintf("<button class='user10' type='submit' name='action' value='save'>Enregistrer</button>\n");
        //
        echo sprintf("</div>\n");
        echo sprintf("</div>\n");
        //
        echo sprintf("</div>\n");
        echo sprintf("</form>\n");        
    }
    //===============================================
}
//===============================================
?>