add_library(TicTacToeLib "Board.h" "Board.cpp" "GameLogic.h" "GameLogic.cpp" "Game.h" "Game.cpp" )
target_include_directories(TicTacToeLib PUBLIC .)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(TicTacToeTests "TicTacToeTests.cpp")
target_link_libraries(TicTacToeTests TicTacToeLib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(TicTacToeTests)
