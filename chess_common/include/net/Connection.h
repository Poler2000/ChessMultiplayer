#ifndef CHESSMULTIPLAYER_CONNECTION_H
#define CHESSMULTIPLAYER_CONNECTION_H

#include <asio.hpp>

#include "Message.h"
#include "MessageTypes.h"
#include "ThreadSafeQueue.h"

namespace poler::net {
    class Connection {
    public:
        Connection(asio::io_context& asioContext, asio::ip::tcp::socket socket, ThreadSafeQueue<Message<MessageTypes>>& qIn)
        : context_(asioContext), socket_(std::move(socket)), inQueue_(qIn) {}

        void disconnect() {
            if (isConnected())
                asio::post(context_, [&]() { socket_.close(); });
        };

        [[nodiscard]] bool isConnected() const {
            return socket_.is_open();
        };

        template<typename T>
        void send(Message<T>& msg) {
            asio::post(context_,
                       [&]() {
                msg.header.senderId = id_;
                outQueue_.push(msg);
                if (!outQueue_.isEmpty()) {
                    writeMsgHeader();
                }
            });
        };

    protected:
        uint32_t id_ = 0;

        ThreadSafeQueue<Message<MessageTypes>>& inQueue_;
        ThreadSafeQueue<Message<MessageTypes>> outQueue_;

        asio::ip::tcp::socket socket_;
        asio::io_context& context_;

        Message<MessageTypes> tmpMsg_;

        void writeMsgHeader() {
            asio::async_write(socket_, asio::buffer(&outQueue_.front().header, sizeof(MsgHeader<MessageTypes>)),
                              [&](std::error_code ec, std::size_t length) {
                                  if (!ec) {
                                      if (outQueue_.front().header.size > 0) {
                                          writeMsgContent();
                                      }
                                      else {
                                          outQueue_.pop();

                                          if (!outQueue_.isEmpty()) {
                                              writeMsgHeader();
                                          }
                                      }
                                  }
                                  else {
                                      disconnect();
                                  }
                              });
        };

        void writeMsgContent() {
            asio::async_write(socket_, asio::buffer(&outQueue_.front().data, outQueue_.front().data.size()),
                              [&](std::error_code ec, std::size_t length) {
                                  if (!ec) {
                                      outQueue_.pop();

                                      if (!outQueue_.isEmpty()) {
                                          writeMsgHeader();
                                      }
                                  }
                                  else {
                                      disconnect();
                                  }
                              });
        };

        void readMsgHeader() {
            asio::async_read(socket_, asio::buffer(&tmpMsg_.header, sizeof(tmpMsg_.header)),
                             [&](std::error_code ec, std::size_t length) {
                                 if (!ec) {
                                     if (tmpMsg_.header.size > 0) {
                                         tmpMsg_.data.resize(tmpMsg_.header.size);
                                         readMsgContent();
                                     }
                                     else {
                                         inQueue_.push(tmpMsg_);
                                         readMsgHeader();
                                     }
                                 }
                                 else {
                                     disconnect();
                                 }
                             });
        };

        void readMsgContent() {
            asio::async_read(socket_, asio::buffer(&tmpMsg_.data, tmpMsg_.header.size),
                             [&](std::error_code ec, std::size_t length) {
                                 if (!ec) {
                                     inQueue_.push(tmpMsg_);
                                     readMsgHeader();
                                 }
                                 else {
                                     disconnect();
                                 }
                             });
        };
    };
    }

#endif //CHESSMULTIPLAYER_CONNECTION_H
