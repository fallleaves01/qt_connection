#ifndef ENCODING_H
#define ENCODING_H

#include<string>
namespace Encoding {
    inline std::string encode(int val) {
        std::string s = "";
        for (int i = 0; i < 32; i += 8) {
            s += (unsigned char)((val >> i) & 0xff);
        }
        return s;
    }
    inline int decode(std::string s) {
        int val = 0;
        for (int i = 0; i < 4; i++) {
            val |= (unsigned char)(s[i]) << (i * 8);
        }
        return val;
    }
}

#endif // ENCODING_H
