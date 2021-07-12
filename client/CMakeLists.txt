cmake_minimum_required(VERSION 3.10)
project(ChessMultiplayer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
include_directories(../vendor/wxWidgets/include)
include_directories(include)
add_executable(client src/app/Launcher.cpp src/app/Launcher.cpp include/app/Launcher.h ../chess_common/include/net/Message.h ../chess_common/include/net/MessageTypes.h src/chess_gui/MainMenu.cpp include/chess_gui/MainMenu.h)

execute_process(COMMAND "wx-config" "--cxxflags" OUTPUT_VARIABLE WX_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND "wx-config" "--libs" OUTPUT_VARIABLE WX_LINK_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)

separate_arguments(WX_CFLAGS UNIX_COMMAND "${WX_CFLAGS}")
separate_arguments(WX_LINK_CFLAGS UNIX_COMMAND "${WX_LINK_CFLAGS}")
target_compile_options(client PUBLIC ${WX_CFLAGS})
target_link_libraries(client ${WX_LINK_CFLAGS})
