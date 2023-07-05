#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../utils/utils.h"
#include "../game/game.h"
#include <string>

TEST_CASE("GameBoard test cases") {

    //Test gameboard update with empty gameboard
    GameBoard board = create_board(10,10);
    CHECK(get_n_alive_neighbors(board,1,1) == 0);
    CHECK(update_board(board) == board);

    //Testing moving thing
    board[2][0]=1;
    board[2][1]=1;
    board[2][2]=1;

    CHECK(update_board(board) != board);
    CHECK(get_n_alive_neighbors(board,2,1) == 2);


    //Testing still thing
    GameBoard board2 = create_board(10,10);
    board2[0][0]=1;
    board2[0][1]=1;
    board2[1][0]=1;
    board2[1][1]=1;
    CHECK(update_board(board2) == board2);

    //Large test
    GameBoard board3 = create_board(1000,1000);
    board2[1000][1000]=1;
    CHECK(get_n_alive_neighbors(board3,999,999) == 0);


}

TEST_CASE("Boolean test cases") {

    //Can spawn if current positions value is zero and neighbours are exactly 3
    CHECK(can_spawn(0,3) == true);
    CHECK(can_spawn(1,3) == false);
    CHECK(can_spawn(0,4) == false);

    //Is over populated if current value is one and neighbours are more than 3
    CHECK(is_over_populated(1,3) == false);
    CHECK(is_over_populated(0,3) == false);
    CHECK(is_over_populated(0,4) == false);
    CHECK(is_over_populated(1,4) == true);

    //Is under populated if current value is one and neighbours are less than 2
    CHECK(is_under_populated(1,1) == true);
    CHECK(is_under_populated(0,1) == false);
    CHECK(is_under_populated(1,2) == false);

}

TEST_CASE("file read") {

    std::string file = "./data/text.txt";
    GameBoard board = create_board(10,10);
    file_to_board(board,file);
    print_board(board);

}