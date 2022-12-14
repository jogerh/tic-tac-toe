cmake_minimum_required(VERSION 3.16)
project(tic-tac-toe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(apptic-tac-toe
    main.cpp
)

qt_add_qml_module(apptic-tac-toe
    URI tictactoe
    VERSION 1.0
    QML_FILES main.qml TicTacToeUi/Board.qml
    SOURCES GameModel.h GameModel.cpp
)

set_target_properties(apptic-tac-toe PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apptic-tac-toe
    PRIVATE Qt6::Quick TicTacToeLib)

install(TARGETS apptic-tac-toe
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

add_subdirectory(TicTacToeLib)
