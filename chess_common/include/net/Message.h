#ifndef CHESSMULTIPLAYER_MESSAGE_H
#define CHESSMULTIPLAYER_MESSAGE_H

#include <vector>
#include <variant>

#include "MessageTypes.h"

namespace poler::net {
    struct MsgHeader {
        MessageTypes type{};
        uint32_t size = 0;
    };

    struct Message {
        MsgHeader header{};
        std::vector<std::pair<std::string, std::variant<int, double, std::string>>> data;
    };
}

#endif //CHESSMULTIPLAYER_MESSAGE_H
