cmake_minimum_required(VERSION 3.13)

make_directory(build/bin)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(jexplorer)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(jexplorer src/main.cpp src/io.cpp src/window.cpp src/MenuWindow.cpp src/TerminalWindow.cpp src/TextWindow.cpp)
target_include_directories(jexplorer PUBLIC include ${ncurses_INCLUDE_DIR})
target_link_libraries(jexplorer ${CURSES_LIBRARIES})