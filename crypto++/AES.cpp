#include "AES.hpp"


namespace AES {
    std::string encrypt(const std::string& plaintext) {
        CryptoPP::AutoSeededRandomPool prng;

        CryptoPP::SecByteBlock key(CryptoPP::AES::MAX_KEYLENGTH);
        CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);

        prng.GenerateBlock(key, key.size());
        prng.GenerateBlock(iv, iv.size());

        std::string encoded;

        try {
            std::string ciphertext;

            CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryptor(key, key.size(), iv);

            CryptoPP::StringSource(plaintext, true, 
                new CryptoPP::StreamTransformationFilter(encryptor,
                    new CryptoPP::StringSink(ciphertext)
                )
            );

            std::string combined(reinterpret_cast<const char*>(key.data()), key.size());
            combined.append(reinterpret_cast<const char*>(iv.data()), iv.size());
            combined.append(ciphertext);

            CryptoPP::StringSource(combined, true,
                new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encoded), false)
            );
        } catch(const CryptoPP::Exception& e) {
            throw;
        }

        return encoded;
    }

    std::string decrypt(const std::string& ciphertext) {
        std::string decoded;
        CryptoPP::StringSource(ciphertext, true,
            new CryptoPP::Base64Decoder(new CryptoPP::StringSink(decoded))
        );

        if(decoded.size() < CryptoPP::AES::MAX_KEYLENGTH + CryptoPP::AES::BLOCKSIZE) {
            throw std::runtime_error("Ciphertext zu kurz oder ungültig");
        }

        CryptoPP::SecByteBlock key(reinterpret_cast<const CryptoPP::byte*>(decoded.data()), CryptoPP::AES::MAX_KEYLENGTH);
        CryptoPP::SecByteBlock iv(reinterpret_cast<const CryptoPP::byte*>(decoded.data() + CryptoPP::AES::MAX_KEYLENGTH), CryptoPP::AES::BLOCKSIZE);
        std::string cipher = decoded.substr(CryptoPP::AES::MAX_KEYLENGTH + CryptoPP::AES::BLOCKSIZE);

        std::string decrypted;
        CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryptor(key, key.size(), iv);

        CryptoPP::StringSource(cipher, true,
            new CryptoPP::StreamTransformationFilter(decryptor,
                new CryptoPP::StringSink(decrypted)
            )
        );

        return decrypted;
    }
}