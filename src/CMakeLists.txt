cmake_minimum_required(VERSION 3.5)

project(PaperPiano VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)
find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )

set(PROJECT_SOURCES
        main.cpp
        piano.cpp
        piano.h
        piano.ui
        camera.h camera.cpp
        key.h
)

add_library(Camera camera.h camera.cpp)
target_link_libraries(Camera ${OpenCV_LIBS})
target_compile_definitions(Camera PRIVATE UNIT_TEST)

add_library(Key key.h)
target_link_libraries(Key Qt${QT_VERSION_MAJOR}::Widgets Qt5::Multimedia)
target_compile_definitions(Key PRIVATE UNIT_TEST)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PaperPiano
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PaperPiano APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PaperPiano SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PaperPiano
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(PaperPiano PRIVATE ${OpenCV_LIBS} Qt${QT_VERSION_MAJOR}::Widgets Qt5::Multimedia)

set_target_properties(PaperPiano PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS PaperPiano
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PaperPiano)
endif()
