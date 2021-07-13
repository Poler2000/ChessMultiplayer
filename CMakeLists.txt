cmake_minimum_required(VERSION 3.10)
project(ChessMultiplayer)

set(CMAKE_CXX_STANDARD 17)

include_directories(chessCommon/include)
include_directories(../vendor/asio/asio/include)

add_subdirectory("${PROJECT_SOURCE_DIR}/server" "${PROJECT_SOURCE_DIR}/server/server_output")
add_subdirectory("${PROJECT_SOURCE_DIR}/client" "${PROJECT_SOURCE_DIR}/client/client_output")
add_subdirectory("${PROJECT_SOURCE_DIR}/chess_common" "${PROJECT_SOURCE_DIR}/chess_common/chess_common_output")
