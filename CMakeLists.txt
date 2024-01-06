cmake_minimum_required(VERSION 3.5.0)
project(tennis-court VERSION 0.1.0 LANGUAGES C CXX)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME}
        ${SRC_DIR}/Common.cpp
        ${SRC_DIR}/FileUtils.cpp
        ${SRC_DIR}/CommandsManagement.cpp
        ${SRC_DIR}/ATP.cpp
        ${SRC_DIR}/main.cpp
)

target_include_directories(tennis-court PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
)