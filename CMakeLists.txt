cmake_minimum_required(VERSION 3.5)

project(GraphsManager LANGUAGES CXX)

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

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        matrixwindow.cpp
        matrixwindow.h
        matrixwindow.ui
        incidmatrix.cpp
        incidmatrix.h
        incidmatrix.ui
        adj_listwindow.cpp
        adj_listwindow.h
        adj_listwindow.ui
        multrepreswindow.cpp
        multrepreswindow.h
        multrepreswindow.ui
        propertieswindow.cpp
        propertieswindow.h
        propertieswindow.ui
        dataclass.cpp
        dataclass.h
        Bigtestdata.h
        Datafile.cpp
        Datafile.h
        resources.qrc
        GraphLibrary/clique.cpp GraphLibrary/clique.h GraphLibrary/cliquepar.cpp GraphLibrary/timer.cpp GraphLibrary/timer.h GraphLibrary/dfcycle.cpp
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GraphsManager
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(GraphsManager SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(GraphsManager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

add_subdirectory(GraphLibrary)
target_link_libraries(GraphsManager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
