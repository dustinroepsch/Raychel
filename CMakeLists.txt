cmake_minimum_required(VERSION 3.9)

project (Raychel)

set(CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -g")

add_executable (Raychel src/main.cpp src/Level/level.cpp src/Level/Tiles/simpletilemap.cpp src/game.cpp)

find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(Raychel ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()



set_property(TARGET Raychel PROPERTY CXX_STANDARD 11)
