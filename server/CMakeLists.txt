cmake_minimum_required(VERSION 3.10)
project(ChessMultiplayer)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "--pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization
    -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast
    -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5
    -Wswitch-default -Wundef -Werror -Wno-unused -pthread")
include_directories(include)

add_executable(server app/main.cpp ../chess_common/include/net/Message.h ../chess_common/include/net/MessageTypes.h)