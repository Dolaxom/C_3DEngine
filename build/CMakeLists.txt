cmake_minimum_required(VERSION 3.5)

project(s21_calc VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "~/Qt/6.4.0/gcc_64")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    ../src/main.cpp
    ../src/qt/mainwindow.cpp
    ../src/qt/mainwindow.h
    ../src/qt/mainwindow.ui
##    ../src/engine/s21_camera.c 
##    ../src/engine/s21_camera.h 
    ../src/engine/s21_engine.h 
    ../src/engine/s21_mesh.c 
    ../src/engine/s21_mesh.h 
    ../src/engine/math/s21_engine_math.c 
    ../src/engine/math/s21_engine_math.h 
    ../src/engine/math/s21_matrix4x4.c 
    ../src/engine/math/s21_matrix4x4.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(C_3DEngine
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(C_3DEngine
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(C_3DEngine PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(C_3DEngine PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS C_3DEngine
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(C_3DEngine)
endif()
