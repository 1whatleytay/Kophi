#ifndef KOPHI_PRIVATE_H
#define KOPHI_PRIVATE_H

#include <Kophi/Utils.h>

namespace Kophi {
    namespace Private {
        template <typename T> T swapEndian(T value) {
            T result = 0;
            for (int a = 0; a < sizeof(value); a++) {
                result <<= 8;
                result |= ((value >> (a * 8)) & 0xFF);
            }
            return result;
        }

        std::vector<unsigned char> fromFileGetBinary(const std::string &path);

        void log(const std::string &text);
        void logPut(const std::string &text);
    }
}

#endif //KOPHI_PRIVATE_H
