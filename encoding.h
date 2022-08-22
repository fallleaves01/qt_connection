#ifndef ENCODING_H
#define ENCODING_H

#include <string>
#include <vector>

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
class Data {
    int dataSize, type, senderUid, receiverUid, timeSize;
    std::string time;
    int contentSize;
    std::string content;

   public:
    static const int SplitLength = 1024;
    explicit Data(int _type,
                  int _senderUid,
                  int _receiverUid,
                  const std::string& _time,
                  const std::string& _content);
    explicit Data(std::string data);
    std::string encode() const;
    std::vector<std::string> splitDataPack() const;

    int getType() const;
    int getSenderUid() const;
    int getReceiverUid() const;
    std::string getTime() const;
    std::string getContent() const;
};
}  // namespace Encoding

#endif //encoding.h
