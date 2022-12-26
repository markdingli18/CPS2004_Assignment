cmake_minimum_required(VERSION 3.21)
project(Village_War_Game)

set(CMAKE_CXX_STANDARD 14)

set(HEADERS header.h attack.h do_actions.h)
set(MAIN main.cpp welcome_message.cpp)
set(FILES map.cpp troops.cpp buildings.cpp villages.cpp resources.cpp stop_game.cpp take_turn.cpp)

add_executable(Village_War_Game ${HEADERS} ${MAIN} ${FILES})