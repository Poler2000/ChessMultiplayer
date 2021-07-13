#ifndef CHESSMULTIPLAYER_CONNECTIONSERVER_H
#define CHESSMULTIPLAYER_CONNECTIONSERVER_H

#include "net/Connection.h"

namespace poler::net {
    class ConnectionServer : public Connection {
    public:
        ConnectionServer(asio::io_context& asioContext, asio::ip::tcp::socket socket, ThreadSafeQueue<Message<MessageTypes>>& qIn)
        : Connection(asioContext, std::move(socket), qIn) {}

        void connectToClient(const int clientId) {
            if (socket_.is_open()) {
                id_ = clientId;
                readMsgHeader();
            }
        }
    };
}

#endif //CHESSMULTIPLAYER_CONNECTIONSERVER_H
