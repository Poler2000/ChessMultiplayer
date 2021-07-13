cmake_minimum_required(VERSION 3.10)
project(ChessMultiplayer)

set(CMAKE_CXX_STANDARD 17)
#SET(CMAKE_CXX_FLAGS "--pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization
#    -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast
#    -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5
#    -Wswitch-default -Wundef -Werror -Wno-unused -pthread")

include_directories(../vendor/cpp_utils/include)
include_directories(include)
include_directories(../chess_common/include)
include_directories(../chess_common)
include_directories(../vendor/asio/asio/include)

add_executable(server app/main.cpp src/net/CommunicationCentre.cpp include/net/CommunicationCentre.h include/net/ConnectionServer.h)
target_link_libraries(server CppUtils)
target_link_libraries(server chessCommon)