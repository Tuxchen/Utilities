# Utilities
Here some useful classes and functions in C++ for database connections (sqlite), password hasshing (bcrypt) and encryption (AES)

# Example for database connection (sqlite)

```cpp
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>

int main() {
  try {
    // open database (created if not exists)
    SQLite::Database db("test.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    // create table
    db.exec("CREATE TABLE IF NOT EXISTS users(\
      id INTEGER PRIMARY KEY,\
      name TEXT,\
      age INTEGER);");

    // insert data
    SQLite::Statement query(db, "INSERT INTO users(name, age) VALUES(?, ?)");
    query.bind(1, "Alice");
    query.bind(2, 30);
    query.exec();

    // read data
    SQLite::Statement select(db, "SELECT id, name, age FROM users");

    while(select.executeStep()) {
      std::cout << "ID: " << select.getColumn(0)
        << ", Name: " << select.getColumn(1)
        << ", Age: " << select.getColumn(2)
        << std::endl;
    }
  } catch(const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
```
