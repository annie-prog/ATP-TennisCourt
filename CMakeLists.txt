cmake_minimum_required(VERSION 3.5.0)
project(tennis-court VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.7 
)
FetchContent_MakeAvailable(catch2)

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
    ${catch2_SOURCE_DIR}/single_include
)

target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2)

enable_testing()
add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME})