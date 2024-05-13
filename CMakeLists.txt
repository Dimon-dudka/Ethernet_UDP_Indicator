cmake_minimum_required(VERSION 3.5)

project(Ethernet_UDP_Indicator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)

if(QT_FOUND)
    message("QT found")
else()
    message(FATAL_ERROR "Cannot find QT")
endif()

set(HEADERS
        #${CMAKE_SOURCE_DIR}/main_server/main_server.h
)

set(SOURCES
        main.cpp
)

add_executable(Ethernet_UDP_Indicator ${SOURCES} ${HEADERS})

#target_include_directories(Ethernet_UDP_Indicator)

target_link_libraries(Ethernet_UDP_Indicator
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    PRIVATE Qt${QT_VERSION_MAJOR}::Network
)
