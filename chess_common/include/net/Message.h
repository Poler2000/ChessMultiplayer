#ifndef CHESSMULTIPLAYER_MESSAGE_H
#define CHESSMULTIPLAYER_MESSAGE_H

#include "MessageTypes.h"

namespace poler::net {
    struct MsgHeader {
        MessageTypes type{};
        uint32_t size = 0;
    };

    struct Message {
        MsgHeader header{};

    };
}

#endif //CHESSMULTIPLAYER_MESSAGE_H
