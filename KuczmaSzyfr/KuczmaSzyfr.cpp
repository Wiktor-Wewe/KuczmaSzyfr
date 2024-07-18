#include <iostream>
#include <stdio.h>
#include <iomanip>

void printData(const uint8_t* data, size_t size) {
    for (size_t i = 0; i < size; ++i) {

        std::cout << "0x" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(data[i]);

        if (i != size - 1) {
            std::cout << ", ";
        }

        if ((i + 1) % 4 == 0) {
            std::cout << std::endl;
        }
    }
}

void KuczmaSzyfr(uint8_t* data, size_t size, const std::string& key, const std::string& salt) {
    size_t keyLength = key.length();
    size_t saltLength = salt.length();

    for (size_t i = 0; i < size; ++i) {
        data[i] ^= key[i % keyLength];
        data[i] ^= salt[i % saltLength]; 
    }
}

int main()
{
    uint8_t data[] = {
        0x12, 0x13, 0x54, 0x67,
        0x01, 0xAA, 0x54, 0xFF,
        0xFF, 0x8D, 0x2A, 0xAA,
        0x00, 0x13, 0xFC, 0x6F,
    };

    size_t dataSize = sizeof(data) / sizeof(data[0]);

    std::cout << "Original data:" << std::endl;
    printData(data, dataSize);

    KuczmaSzyfr(data, dataSize, "KUczMa", "8zXNp28zpseyAyX1MpTHLXKyXeDyfFSMCL0nJp0y96VpkZhcWz");

    std::cout <<  "\nEncrypted data:" << std::endl;
    printData(data, dataSize);

    KuczmaSzyfr(data, dataSize, "KUczMa", "8zXNp28zpseyAyX1MpTHLXKyXeDyfFSMCL0nJp0y96VpkZhcWz");
    
    std::cout << "\nDecrypted data:" << std::endl;
    printData(data, dataSize);

    return 0;
}