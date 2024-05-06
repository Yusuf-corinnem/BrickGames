cmake_minimum_required(VERSION 3.5)

project(Snake_QT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

cmake_path(GET CMAKE_SOURCE_DIR PARENT_PATH TEMP_DIR)
cmake_path(GET TEMP_DIR PARENT_PATH TEMP_DIR)
cmake_path(GET TEMP_DIR PARENT_PATH THREE_LEVELS_UP)
add_compile_definitions("THREE_LEVELS_UP=${THREE_LEVELS_UP}")

file(GLOB_RECURSE PROJECT_SOURCES
    *.cpp
    resources/resources.qrc
)

file(GLOB_RECURSE PROJECT_HEADERS
    *.h
    ${THREE_LEVELS_UP}/brick_game/snake/*.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Snake_QT
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Snake_QT APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Snake_QT SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Snake_QT
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Snake_QT PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Snake_QT PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Snake_QT)
endif()
