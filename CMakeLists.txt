cmake_minimum_required(VERSION 3.5)

project(QtBreakpad LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network)

set(SRC ./handler/QBreakpadHandler.cpp
    ./handler/QBreakpadHandler.h
    ./handler/QBreakpadHttpUploader.cpp
    ./handler/QBreakpadHttpUploader.h
    ./handler/singletone/call_once.h
    ./handler/singletone/singleton.h
    TestThread.cpp
    TestThread.h
    reporter.ui
    reporter.cpp
    reporter.h
    )

set(PROJECT_SOURCES
    main.cpp
    Widget.cpp
    Widget.h
    Widget.ui
    ${SRC}
    ${SRC_INCLUDE}
    )

#include_directories(./3rd/google_breakpad/)
include_directories(./3rd/)
#link_libraries(${PROJECT_SOURCE_DIR}/3rd/google_breakpad/)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtBreakpad
        ${PROJECT_SOURCES}
        )
else()
    if(ANDROID)
        add_library(QtBreakpad SHARED
            ${PROJECT_SOURCES}
            )
    else()
        add_executable(QtBreakpad
            ${PROJECT_SOURCES}
            )
    endif()
endif()

target_link_libraries(QtBreakpad PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  Qt${QT_VERSION_MAJOR}::Network)
if (CMAKE_BUILD_TYPE MATCHES "Release")
    target_link_libraries(QtBreakpad PRIVATE ${PROJECT_SOURCE_DIR}/3rd/google_breakpad/libbreakpad_client.lib)
else()
    target_link_libraries(QtBreakpad PRIVATE ${PROJECT_SOURCE_DIR}/3rd/google_breakpad/libbreakpad_clientd.lib)
endif()
