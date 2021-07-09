#ifndef CHESSMULTIPLAYER_MESSAGETYPES_H
#define CHESSMULTIPLAYER_MESSAGETYPES_H

enum class MessageTypes : uint32_t {
    ClientHello,
    ValidationData,
    ValidationResponse,
    ClientAccept,

    DisconnectRequest,
    NewGameRequest,
    JoinGameRequest,
    JoinAsSpectatorRequest,
    MoveRequest,

    GameState,
    GameStopped,
};

#endif //CHESSMULTIPLAYER_MESSAGETYPES_H
