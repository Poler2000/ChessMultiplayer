#ifndef CHESSMULTIPLAYER_COMMUNICATIONCENTRE_H
#define CHESSMULTIPLAYER_COMMUNICATIONCENTRE_H

#include <cstdint>
#include <memory>
#include <deque>
#include <thread>
#include <asio.hpp>
#include <atomic>

#include "net/ThreadSafeQueue.h"
#include "net/Message.h"
#include "net/MessageTypes.h"
#include "net/ConnectionServer.h"
#include "Logger.h"

namespace poler::net {
    class CommunicationCentre {
    public:
        CommunicationCentre(uint16_t port)
            : asioAcceptor_(context_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {}

        virtual ~CommunicationCentre() {
            stop();
        }

        bool init() {
            try {
                listenForConnections();

                threadContext_ = std::thread([this]() { context_.run(); });
            }
            catch (std::exception& ex) {
                utils::Logger::error(ex.what());
                return false;
            }

            utils::Logger::info("Server has started!");
            return true;
        }

        void stop() {
            context_.stop();

            if (threadContext_.joinable()) {
                threadContext_.join();
            }

            utils::Logger::info("Server has stopped!");
        }

        void listenForConnections() {
            asioAcceptor_.async_accept(
                    [this](std::error_code ec, asio::ip::tcp::socket socket) {
                        if (!ec) {
                            auto newConnection =
                                    std::make_shared<ConnectionServer>(context_,
                                                                 std::move(socket), inMsgQueue_);

                            if (onClientConnect(newConnection)) {
                                connections_.push_back(std::move(newConnection));
                                connections_.back()->connectToClient(idCounter_++);
                            }
                            else {
                            }
                        }
                        else {
                            std::cout << "[SERVER] New Connection Error: " << ec.message() << "\n";
                        }

                        listenForConnections();
                    });
        }

        void sendToClient(std::shared_ptr<ConnectionServer> client, Message<MessageTypes>& msg) {
            if (client && client->isConnected()) {
                client->send(msg);
            }
            else {
                onClientDisconnect(client);
                client.reset();

                connections_.erase(
                        std::remove(connections_.begin(), connections_.end(), client), connections_.end());
            }
        }

        void sendToAllClients(Message<MessageTypes>& msg, const std::shared_ptr<ConnectionServer>& ignoreClient = nullptr) {
            bool areThereInvalidClients = false;

            for (auto& client : connections_) {
                if (client && client->isConnected()) {
                    if(client != ignoreClient)
                        client->send(msg);
                }
                else {
                    onClientDisconnect(client);
                    client.reset();

                    areThereInvalidClients = true;
                }
            }

            if (areThereInvalidClients)
                connections_.erase(
                        std::remove(connections_.begin(), connections_.end(), nullptr), connections_.end());
        }

    protected:
        bool onClientConnect(std::shared_ptr<ConnectionServer> client) {
            return true;
        }

        void onClientDisconnect(std::shared_ptr<ConnectionServer> client) {

        }

        void onMessage(std::shared_ptr<ConnectionServer> client, Message<MessageTypes>& msg) {

        }


    protected:
        ThreadSafeQueue<Message<MessageTypes>> inMsgQueue_;

        std::deque<std::shared_ptr<ConnectionServer>> connections_;

        asio::io_context context_;
        std::thread threadContext_;

        asio::ip::tcp::acceptor asioAcceptor_;

        std::atomic_int32_t idCounter_ = 1000;
    };
}

#endif //CHESSMULTIPLAYER_COMMUNICATIONCENTRE_H
