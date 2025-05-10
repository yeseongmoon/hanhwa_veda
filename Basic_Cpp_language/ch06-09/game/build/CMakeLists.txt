cmake_minimum_required(VERSION 3.10)

project(Game VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/../src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../inc)

add_executable(Game ${SRC_DIR}/main.cpp ${SRC_DIR}/player.cpp
                    ${SRC_DIR}/game.cpp)

target_include_directories(Game PRIVATE ${INCLUDE_DIR} /opt/homebrew/include)
target_link_directories(Game PRIVATE ${LIB_DIR})
