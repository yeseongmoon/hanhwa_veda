cmake_minimum_required(VERSION 3.10)

project(SHAPE VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/../src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../include)
set(LIB_DIR /opt/homebrew/lib)

add_executable(Shape ${SRC_DIR}/main.cpp ${SRC_DIR}/triangle.cpp
                     ${SRC_DIR}/shape.cpp ${SRC_DIR}/circle.cpp)

target_include_directories(Shape PRIVATE ${INCLUDE_DIR} /opt/homebrew/include)

target_link_directories(Shape PRIVATE ${LIB_DIR})
# target_link_libraries(Tutorial cJSON curl)
