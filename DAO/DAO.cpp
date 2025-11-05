#include "DAO.hpp"

DAO::DAO(const std::string& name) : db(name, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE) {}

void DAO::createUserTable() {
    db.exec("CREATE TABLE IF NOT EXISTS Users(\
                u_id INTEGER PRIMARY KEY,\
                u_name VARCHAR(30) NOT NULL,\
                u_pass VARCHAR(65) NOT NULL,\
                u_admin BOOLEAN NOT NULL);");
}

void DAO::createPasswordTable() {
    db.exec("CREATE TABLE IF NOT EXISTS Passwords(\
                p_id INTEGER PRIMARY KEY,\
                p_uid INTEGER NOT NULL,\
                p_pass VARCHAR(100) NOT NULL,\
                FOREIGN KEY(p_uid) REFERENCES Users(u_id) ON DELETE CASCADE);");
}