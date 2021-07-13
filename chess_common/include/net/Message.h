#ifndef CHESSMULTIPLAYER_MESSAGE_H
#define CHESSMULTIPLAYER_MESSAGE_H

#include <vector>
#include <variant>

#include "NetException.h"

namespace poler::net {
    template <typename MsgType>
    struct MsgHeader {
        MsgType type{};
        uint32_t size = 0;
        uint32_t senderId = 0;
    };

    template <typename MsgType>
    struct Message {
    public:
        MsgHeader<MsgType> header{};
        std::vector<std::pair<std::string, std::variant<int, double, std::string>>> data{};

        template<class T>
        void addField(std::string label, T arg) {
            header.size += label.size() + sizeof(arg);
            data.template emplace_back(std::make_pair(std::move(label), arg));
        }

        [[nodiscard]] bool hasField(const std::string& label) const {
            return std::find_if(data.begin(), data.end(), [&](auto& pair){
                return label == pair.first;
            }) < data.end();
        }

        template<typename T>
        [[nodiscard]] T get(std::string& label) const noexcept(false) {
            for (auto& p : data) {
                if (p.first == label) {
                    try {
                        return std::get<T>(p.second);
                    }
                    catch(std::bad_variant_access& ex) {
                        throw NetException{"Specified type and type of variable found don't match."};
                    }
                }
            }
        }

    private:
    };
}

#endif //CHESSMULTIPLAYER_MESSAGE_H
