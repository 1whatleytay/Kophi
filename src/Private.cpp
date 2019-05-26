#include <Kophi/Private.h>

#include <fstream>
#include <iostream>

namespace Kophi {
    namespace Private {
        std::vector<unsigned char> fromFileGetBinary(const std::string &path) {
            std::ifstream stream = std::ifstream(path, std::ios::binary | std::ios::ate);
            unsigned length = stream.tellg();
            stream.seekg(0, std::ios::beg);
            std::vector<unsigned char> data = std::vector<unsigned char>(length);
            stream.read((char *)&data[0], length);
            stream.close();
            return data;
        }

        void log(const std::string &text) {
            std::cout << text << std::endl;
        }

        void logPut(const std::string &text) {
            std::cout << text;
        }
    }
}
