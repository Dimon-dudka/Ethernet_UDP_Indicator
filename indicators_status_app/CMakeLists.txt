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
    ${CMAKE_SOURCE_DIR}/Basic_Types.h
    ${CMAKE_SOURCE_DIR}/widget_manager/widget_manager.h
    ${CMAKE_SOURCE_DIR}/start_menu/start_menu.h
    ${CMAKE_SOURCE_DIR}/network_data/network_data.h
    ${CMAKE_SOURCE_DIR}/new_ip_menu/new_ip_menu.h
    ${CMAKE_SOURCE_DIR}/workspace_menu/workspace_menu.h
    ${CMAKE_SOURCE_DIR}/indicators_local_data/indicators_local_data.h
)

set(SOURCES
    main.cpp
    ${CMAKE_SOURCE_DIR}/widget_manager/widget_manager.cpp
    ${CMAKE_SOURCE_DIR}/start_menu/start_menu.cpp
    ${CMAKE_SOURCE_DIR}/network_data/network_data.cpp
    ${CMAKE_SOURCE_DIR}/new_ip_menu/new_ip_menu.cpp
    ${CMAKE_SOURCE_DIR}/workspace_menu/workspace_menu.cpp
    ${CMAKE_SOURCE_DIR}/indicators_local_data/indicators_local_data.cpp
)

add_executable(Ethernet_UDP_Indicator ${SOURCES} ${HEADERS})

target_include_directories(Ethernet_UDP_Indicator
    PUBLIC ${CMAKE_SOURCE_DIR}
    PUBLIC ${CMAKE_SOURCE_DIR}/widget_manager
    PUBLIC ${CMAKE_SOURCE_DIR}/start_menu
    PUBLIC ${CMAKE_SOURCE_DIR}/network_data
    PUBLIC ${CMAKE_SOURCE_DIR}/new_ip_menu
    PUBLIC ${CMAKE_SOURCE_DIR}/workspace_menu
    PUBLIC ${CMAKE_SOURCE_DIR}/indicators_local_data
)

target_link_libraries(Ethernet_UDP_Indicator
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    PRIVATE Qt${QT_VERSION_MAJOR}::Network
)
