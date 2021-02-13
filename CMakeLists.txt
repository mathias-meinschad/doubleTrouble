cmake_minimum_required(VERSION 3.17)
project(double_trouble)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(
        ${SDL2_INCLUDE_DIRS} 
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIR})

add_executable(double_trouble apps/double_trouble.cpp include/Constants.hpp include/KeyboardHandler.hpp include/SdlHelpers.hpp include/SdlHelpers.cpp include/LevelObject.cpp include/LevelObject.hpp include/Level.cpp include/Level.hpp include/Sprite.cpp include/Sprite.hpp include/CollisionDetection.cpp include/CollisionDetection.h include/Menu.cpp include/Menu.h include/GeneralHelper.cpp include/GeneralHelper.hpp)
target_link_libraries(double_trouble 
        ${SDL2_LIBRARIES} 
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})
