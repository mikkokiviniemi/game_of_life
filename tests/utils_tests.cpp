#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../utils/utils.h"

TEST_CASE("Tests for utils -library's functions") {
    // Empty 3x3 board
    GameBoard test_board{create_board(3,3)};
    std::vector<std::vector<int>> test_board2 = {{0,0,0}, {0,0,0}, {0,0,0}};
    CHECK(test_board == test_board2);
    
    // Board without cells, no alive neighbours
    CHECK(get_n_alive_neighbors(test_board, 1, 1) == 0);

    // Board with cells
    //[0][1][0]
    //[0][1][0]
    //[0][1][0]
    test_board[0][1] = 1;
    test_board[1][1] = 1;
    test_board[2][1] = 1;
    CHECK(get_n_alive_neighbors(test_board, 1, 1) == 2);




}