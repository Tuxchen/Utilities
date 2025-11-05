#include <iostream>
#include "DAO/DAO.hpp"
#include "bcrypt/Hash.hpp"
#include "crypto++/AES.hpp"

int main() {
    DAO db("users.db");
    
    // Tabellen initalisieren, falls noch nicht existent
    try {
        db.createUserTable();
        db.createPasswordTable();
    } catch(const SQLite::Exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::string cipher = AES::encrypt("Cipherpunk");

    std::cout << "AES-Verschlüsselt: " << cipher << std::endl;

    std::string plain = AES::decrypt(cipher);

    std::cout << "AES-Entschlüsselt: " << plain << std::endl;

    std::cout << "Länge des Ciphertextes: " << cipher.size() << std::endl;

    return 0;
}