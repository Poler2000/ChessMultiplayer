#ifndef CHESSMULTIPLAYER_CONNECTIONCLIENT_H
#define CHESSMULTIPLAYER_CONNECTIONCLIENT_H

#include "Connection.h"

namespace poler::net {
        class ConnectionClient : public Connection {
            void connectToServer(const asio::ip::tcp::resolver::results_type& endpoints) {
                asio::async_connect(
                        socket_, endpoints, [&](std::error_code ec, asio::ip::tcp::endpoint endpoint) {
                            if (!ec) {
                                readMsgHeader();
                            }
                        });
            }
        };
    }

#endif //CHESSMULTIPLAYER_CONNECTIONCLIENT_H
