find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

set(CMAKE_AUTOMOC ON)

qt_add_executable(TicTacToeApp
    main.cpp
)

qt_add_qml_module(TicTacToeApp
    URI tictactoe
    VERSION 1.0
    QML_FILES TicTacToeUi/LevelComboBox.qml main.qml TicTacToeUi/Board.qml
    SOURCES GameModel.h GameModel.cpp
)

set_target_properties(TicTacToeApp PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(TicTacToeApp
    PRIVATE Qt6::Quick TicTacToeLib)

install(TARGETS TicTacToeApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
