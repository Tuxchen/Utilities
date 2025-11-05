#ifndef DAO_H
#define DAO_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

class DAO {
    SQLite::Database db;

    public:
    DAO(const std::string& name);

    void createUserTable();

    void createPasswordTable();
};

#endif