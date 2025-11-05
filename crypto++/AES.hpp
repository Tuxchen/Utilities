#ifndef AES_H
#define AES_H

#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/secblock.h>
#include <cryptopp/hex.h>
#include <string>
#include <stdexcept>

namespace AES {
    std::string encrypt(const std::string& plaintext);

    std::string decrypt(const std::string& ciphertext);
}

#endif