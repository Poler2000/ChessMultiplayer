#ifndef CHESSMULTIPLAYER_NETEXCEPTION_H
#define CHESSMULTIPLAYER_NETEXCEPTION_H

#include <exception>

namespace poler::net {
    class NetException : public std::exception {
    public:
        explicit NetException(std::string msg) : msg_(std::move(msg)) {}

        [[nodiscard]] const char* what() const noexcept override {
            return msg_.c_str();
        }

        const std::string msg_;
    };
}

#endif //CHESSMULTIPLAYER_NETEXCEPTION_H
