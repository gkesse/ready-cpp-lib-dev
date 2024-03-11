-- ==============================================
-- chat : base de données
-- ==============================================

drop database db_chat_test;

create database db_chat_test;

use db_chat_test;

-- ==============================================
-- _user : gestion des utilisateurs
-- ==============================================

drop table if exists _user;

create table if not exists _user (
    _id int not null auto_increment -- identifiant de l'utilisateur
    , _uuid varchar(50) -- uuid de l'utilisateur
    , _pseudo varchar(50) -- pseudo de l'utilisateur
    , _create_date datetime default current_timestamp -- date de création de l'utilisateur
    , _update_date datetime on update current_timestamp -- date de modification de l'utilisateur
    , primary key (_id)
    , unique (_uuid)
    , unique (_pseudo)
);

select * from _user;

-- ==============================================
