cmake_minimum_required(VERSION 3.10)
project(ChessMultiplayer)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(../vendor/asio/asio/include)

add_library(chessCommon INTERFACE)
target_include_directories(chessCommon INTERFACE include/)

# TODO rm later
#add_executable(common main.cpp include/net/ThreadSafeQueue.h include/net/MessageTypes.h include/net/Message.h include/net/Connection.h include/net/ConnectionClient.h include/net/NetException.h)
#target_link_libraries(common )