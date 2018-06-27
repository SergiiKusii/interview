#include "CryptoppTest.h"
#include <iostream>

#ifdef _USE_CRYPTO_

#include "Cryptopp\filters.h"
#include "Cryptopp\hex.h"
#include "Cryptopp\modes.h"
#include "Cryptopp\aes.h"
#include "Cryptopp\sha.h"

template<typename T>
void cout_cont(const std::string& sHeader, const T& vec) {
	std::cout << sHeader << "={ ";

	for (auto& val : vec) {
		std::cout << val << " ";
	}
	std::cout << "}" << std::endl;
}

void CryptoppTest::Run()
{
	std::cout << "CryptoppTest::Run()" << std::endl;
	try {
		std::cout << "SHA256" << std::endl;
		std::string plaintext = "333333333333333344444444444444444444444444444444444444444444445555555555555555555555555555555555555555555556666666666666666666666666666666666666667777777777777777777777777777777777777777777778888888888888888888888888";

		CryptoPP::SHA256 hash;
		std::vector<CryptoPP::byte> digest(hash.BlockSize());
		auto* psink = new CryptoPP::ArraySink(&digest.front(), digest.size());
		
		CryptoPP::StringSource s(plaintext, true, new CryptoPP::HashFilter(hash, psink));
		digest.resize((size_t)psink->TotalPutLength());
		
		std::cout << "AES" << std::endl;

		// hex decoder key
		std::string hexKey = "3131313131313131313131313131313131313131313131313131313131313131";
		std::cout << "hexKey = " << hexKey << std::endl;
		std::vector<CryptoPP::byte> decodedKey(hexKey.size());
		psink = new CryptoPP::ArraySink(&decodedKey.front(), decodedKey.size());
		CryptoPP::StringSource(hexKey, true, new CryptoPP::HexDecoder(psink));
		decodedKey.resize((size_t)psink->TotalPutLength());
		cout_cont("decodedKey = ", decodedKey);

		// encrypt 
		std::string plaintextHex;
		CryptoPP::ArraySource(&digest.front(), digest.size(), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(plaintextHex)));
		std::cout << "plaintextHex = " << plaintextHex << std::endl;

		CryptoPP::AES::Encryption aesEncryption(decodedKey.data(), decodedKey.size());
		CryptoPP::ECB_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption);
		auto padding = CryptoPP::BlockPaddingSchemeDef::NO_PADDING;
		std::vector<CryptoPP::byte> ciphertext(digest.size());
		psink = new CryptoPP::ArraySink(&ciphertext.front(), ciphertext.size());
		CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, psink, padding);
		stfEncryptor.Put(digest.data(), digest.size());
		stfEncryptor.MessageEnd();
		ciphertext.resize((size_t)psink->TotalPutLength());

		std::cout << "Cipher Text (" << ciphertext.size() << " bytes)" << std::endl;
		std::string ciphertextHex;
		CryptoPP::ArraySource(&ciphertext.front(), ciphertext.size(), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(ciphertextHex)));
		std::cout << "Cipher Text = " << ciphertextHex << std::endl;

		//decrypt
		std::vector<CryptoPP::byte> decryptedtext(ciphertext.size());
		CryptoPP::AES::Decryption aesDecryption(decodedKey.data(), decodedKey.size());
		CryptoPP::ECB_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption);

		psink = new CryptoPP::ArraySink(&decryptedtext.front(), decryptedtext.size());
		CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, psink, padding);
		stfDecryptor.Put(ciphertext.data(), ciphertext.size());
		stfDecryptor.MessageEnd();
		decryptedtext.resize((size_t)psink->TotalPutLength());

		std::string decryptedtextHex;
		CryptoPP::ArraySource(&decryptedtext.front(), decryptedtext.size(), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(decryptedtextHex)));

		std::cout << "decryptedtextHex = " << decryptedtextHex << std::endl;
	}
	catch (CryptoPP::Exception& exc) {
		std::cout << exc.GetWhat() << std::endl;
	}
	catch (...){
		std::cout << "some error " << std::endl;
	}
}

#else
void CryptoppTest::Run()
{
	std::cout << "Crypto is not used" << std::endl;
}
#endif
