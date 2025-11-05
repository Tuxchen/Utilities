#ifndef HASH_H
#define HASH_H

#include <string>
#include <stdexcept>
#include "bcrypt.h"

namespace Hash {
    std::string hash_password(const std::string& str);

    bool verify_password(const std::string& password, const std::string& hash);
}

#endif