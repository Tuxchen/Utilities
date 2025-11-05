#include "Hash.hpp"

namespace Hash {
    std::string hash_password(const std::string& password) {
        char hash[61];
        char salt[30];

        if(bcrypt_gensalt(12, salt) != 0) {
            throw std::runtime_error("Fehler beim Generieren des Salts");
        }

        if(bcrypt_hashpw(password.c_str(), salt, hash) != 0) {
            throw std::runtime_error("Fehler beim hashen");
        }

        return std::string(hash);
    }

    bool verify_password(const std::string& password, const std::string& hash) {
        if(bcrypt_checkpw(password.c_str(), hash.c_str())) {
            return true;
        }

        return false;
    }
}