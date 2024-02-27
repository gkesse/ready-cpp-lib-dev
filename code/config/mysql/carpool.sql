-- ==============================================
-- db_carpool_test : base de données
-- ==============================================

drop database db_carpool_test;

create database db_carpool_test;

use db_carpool_test;

-- ==============================================
-- _user : gestion des utilisateurs
-- ==============================================

drop table if exists _user;

create table if not exists _user (
    _id int not null auto_increment -- identifiant de l'utilisateur
    , _uuid varchar(50) -- uuid de l'utilisateur
    , _email varchar(50) -- email de l'utilisateur
    , _password varchar(50) -- mot de passe de l'utilisateur
    , _is_newsletter varchar(1) default '0' -- l'utilisateur accepte de recevoir des newsletters ?
    , _status varchar(1) default '0' -- status de l'utilisateur
    , _create_date datetime default current_timestamp -- date de création de l'utilisateur
    , _update_date datetime on update current_timestamp -- date de modification de l'utilisateur
    , primary key (_id) -- clé primaire de l'utilisateur
    , unique (_email) -- unicité de l'email de l'utilisateur
);

select * from _user;

-- ==============================================
