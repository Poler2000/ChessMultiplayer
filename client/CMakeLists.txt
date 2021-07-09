cmake_minimum_required(VERSION 3.10)
project(ChessMultiplayer)

set(CMAKE_CXX_STANDARD 20)

#find_package(wxWidgets REQUIRED COMPONENTS net core base)
#include(${wxWidgets_USE_FILE})
include_directories(include)
add_executable(client src/app/Launcher.cpp src/app/Launcher.cpp include/app/Launcher.h ../chess_common/include/net/Message.h ../chess_common/include/net/MessageTypes.h)
#target_link_libraries(client ${wxWidgets_LIBRARIES})