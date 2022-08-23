#include "encoding.h"

Encoding::Data::Data(int _type,
                     int _senderUid,
                     int _receiverUid,
                     const std::string& _time,
                     const std::string& _content)
    : type(_type),
      senderUid(_senderUid),
      receiverUid(_receiverUid),
      time(_time),
      content(_content) {
    timeSize = time.length();
    contentSize = content.length();
    dataSize = 4 * 6 + timeSize + contentSize;
}

Encoding::Data::Data(std::string data) {
    dataSize = decode(data.substr(0, 4));
    type = decode(data.substr(4, 4));
    senderUid = decode(data.substr(8, 4));
    receiverUid = decode(data.substr(12, 4));
    timeSize = decode(data.substr(16, 4));
    time = data.substr(20, timeSize);
    contentSize = decode(data.substr(20 + timeSize, 4));
    content = data.substr(24 + timeSize);
}

std::string Encoding::Data::encode() const {
    std::string data = Encoding::encode(dataSize);
    data += Encoding::encode(type);
    data += Encoding::encode(senderUid);
    data += Encoding::encode(receiverUid);
    data += Encoding::encode(timeSize);
    data += time;
    data += Encoding::encode(contentSize);
    data += content;
    return data;
}

std::vector<std::string> Encoding::Data::splitDataPack() const {
    std::string data = this->encode();
    std::vector<std::string> dataPack;
    for (int i = 0; i < (int)data.length(); i += SplitLength) {
        dataPack.emplace_back(data.substr(i, SplitLength));
    }
    return dataPack;
}

int Encoding::Data::getType() const {
    return type;
}
int Encoding::Data::getSenderUid() const {
    return senderUid;
}
int Encoding::Data::getReceiverUid() const {
    return receiverUid;
}
std::string Encoding::Data::getTime() const {
    return time;
}
std::string Encoding::Data::getContent() const {
    return content;
}