cmake_minimum_required(VERSION 3.5)
project(cvKey)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -ldl -lpthread -Wall")

find_package(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
set(PROJECT_SOURCES
         src/main.cpp
         src/camera.cpp
         src/camera.h
         src/PianoKey.h
)
add_executable(cvKey ${PROJECT_SOURCES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS} pthread)