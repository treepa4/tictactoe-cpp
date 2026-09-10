cmake_minimum_required(VERSION 3.11)
project(tictactoe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

include(FetchContent)
FetchContent_Declare(
    raylib_cpp
    GIT_REPOSITORY git@github.com:RobLoach/raylib-cpp.git
    GIT_TAG v5.0.2
)

FetchContent_MakeAvailable(raylib_cpp)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} raylib raylib_cpp)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/src/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)