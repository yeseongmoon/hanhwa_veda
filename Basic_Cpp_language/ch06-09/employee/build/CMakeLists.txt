cmake_minimum_required(VERSION 3.10)
project(EMPLOYEE VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/../src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../include)

add_executable(
  Employee
  ${SRC_DIR}/employee_main.cpp ${SRC_DIR}/employee.cpp ${SRC_DIR}/regular.cpp
  ${SRC_DIR}/manager.cpp ${SRC_DIR}/temporary.cpp ${SRC_DIR}/sales.cpp)

target_include_directories(Employee PRIVATE ${INCLUDE_DIR})
