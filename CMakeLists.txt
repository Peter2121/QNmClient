cmake_minimum_required(VERSION 3.5)

project(QNmClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Gui Network REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Gui Network REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        nmsocketwindow.cpp
        nmsocketwindow.h
)

#if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#    qt_add_executable(QNmClient
#        MANUAL_FINALIZATION
#        ${PROJECT_SOURCES}
#    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QNmClient APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
#else()
#    if(ANDROID)
#        add_library(QNmClient SHARED
#            ${PROJECT_SOURCES}
#        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    else()
#        add_executable(QNmClient
#            ${PROJECT_SOURCES}
#        )
#    endif()
#endif()

add_executable(QNmClient ${PROJECT_SOURCES})
qt5_use_modules(QNmClient Gui Widgets Core Network)
#target_link_libraries(QNmClient PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core, Qt${QT_VERSION_MAJOR}::Gui, Qt${QT_VERSION_MAJOR}::Network)
#target_link_libraries(QNmClient PRIVATE Qt5::Widgets Qt5::Core, Qt5::Gui, Qt5::Network)

#if(QT_VERSION_MAJOR EQUAL 6)
#    qt_finalize_executable(QNmClient)
#endif()
