cmake_minimum_required(VERSION 3.17)
project(double_trouble CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIR}
        helpers/include)

add_executable(double_trouble apps/double_trouble.cpp
        helpers/include/CollisionDetection.hpp
        helpers/src/CollisionDetection.cpp
        helpers/include/Constants.hpp
        helpers/include/GeneralHelper.hpp
        helpers/src/GeneralHelper.cpp
        helpers/include/KeyboardHandler.hpp
        helpers/include/Level.hpp
        helpers/src/Level.cpp
        helpers/include/LevelObject.hpp
        helpers/src/LevelObject.cpp
        helpers/include/Menu.hpp
        helpers/src/Menu.cpp
        helpers/include/SdlHelpers.hpp
        helpers/src/SdlHelpers.cpp
        helpers/include/Sprite.hpp
        helpers/src/Sprite.cpp)

target_link_libraries(double_trouble
        ${SDL2_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})
