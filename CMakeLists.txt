cmake_minimum_required(VERSION 3.10)
project(albino)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(include)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(albino
        src/action.h
        src/action_queue.cpp
        src/action_queue.h
        src/base.h
        src/battle.cpp
        src/battle.h
        src/detailed_selection_window.cpp
        src/detailed_selection_window.h
        src/entity.cpp
        src/entity.h
        src/event.cpp
        src/event.h
        src/game.cpp
        src/game.h
        src/gettext_window.cpp
        src/gettext_window.h
        src/helper.cpp
        src/helper.h
        src/keys.h
        src/main.cpp
        src/maze.cpp
        src/maze.h
        src/maze_window.cpp
        src/maze_window.h
        src/monster.cpp
        src/monster.h
        src/move_battle.h
        src/player.cpp
        src/player.h
        src/player_class.cpp
        src/player_class.h
        src/player_window.cpp
        src/player_window.h
        src/selection_menu.cpp
        src/selection_menu.h
        src/selection_window.cpp
        src/selection_window.h
        src/system.h
        src/text_buffer.cpp
        src/text_buffer.h
        src/textlog_window.cpp
        src/textlog_window.h
        src/universal.h
        src/window.cpp
        src/window.h
        src/xml_load.cpp
        src/xml_load.h)

add_library(pugixml STATIC IMPORTED)
set_target_properties(pugixml PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libpugixml.a)
target_link_libraries(albino pugixml ${CURSES_LIBRARIES})
