#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../utils/utils.h"
//#include "../game/game.cpp"

TEST_CASE("Tests for utils -library's functions") {
    GameBoard board_empty{create_board(3,3)};
    std::vector<std::vector<int>> board_also_empty{{0,0,0}, {0,0,0}, {0,0,0}};
    std::vector<std::vector<int>> board_vertical_blinker{{0,1,0}, {0,1,0}, {0,1,0}};
    std::vector<std::vector<int>> board_horizontal_blinker{{0,0,0}, {1,1,1}, {0,0,0}};
    
    SUBCASE("random number generator works") {
        int random_num{rndBtw::randomBetween(1, 100)};    
        CHECK((random_num >= 1));
        CHECK((random_num <= 100));
    }

    SUBCASE("check that board is created (empty 3x3 board)") {
        CHECK(board_empty == board_also_empty);
        CHECK(board_empty != board_vertical_blinker);
    }

    SUBCASE("check that number of alived neighbours are calculated correctly") {
        // Board without cells, no alive neighbours
        CHECK(get_n_alive_neighbors(board_empty, 1, 1) == 0);

        /* Board with cells
        [0][1][0]
        [0][1][0]
        [0][1][0]
        */

        // "row 0, col 0, two neighbours alive" etc.
        CHECK(get_n_alive_neighbors(board_vertical_blinker, 0, 0) == 2);  
        CHECK(get_n_alive_neighbors(board_vertical_blinker, 1, 0) == 3);
        CHECK(get_n_alive_neighbors(board_vertical_blinker, 1, 1) == 2);
        CHECK(get_n_alive_neighbors(board_vertical_blinker, 2, 2) == 2);
    }

    SUBCASE("check the boolean functions are working") {
        // A new cell can be born if there are exactly three alive neighbours
        CHECK(can_spawn(0, 3) == true);  // No living cell at the current position, three neighbours
        CHECK(can_spawn(0, 2) == false);  
        CHECK(can_spawn(0, 1) == false);
        CHECK(can_spawn(0, 0) == false);
        CHECK(can_spawn(1, 3) == false);  //there is already cell at the current position

        // The old cell is destroyed if there are over three neighbours
        CHECK(is_over_populated(1, 4) == true);  // There is a cell at the curr.position, four neighb.
        CHECK(is_over_populated(1, 3) == false);
        CHECK(is_over_populated(1, 1) == false);
        CHECK(is_over_populated(0, 4) == false);  // There is no cell at the current position

        // The old cell is destroyed if there are less than two neighbours
        CHECK(is_under_populated(1, 1) == true);  
        CHECK(is_under_populated(1, 0) == true);
        CHECK(is_under_populated(1, 2) == false);
        CHECK(is_under_populated(1, 3) == false);
        CHECK(is_under_populated(0, 1) == false);
    }

    SUBCASE("Check that the board updates correctly") {
        /*
            [0][1][0]       [0][0][0]
            [0][1][0]   =>  [1][1][1]
            [0][1][0]       [0][0][0]

            Vertical blinker turns/updates to horizontal
        */
        std::vector<std::vector<int>> board_wannebe_horizontal_blinker = update_board(board_vertical_blinker);
        CHECK(board_wannebe_horizontal_blinker == board_horizontal_blinker);
        CHECK(board_wannebe_horizontal_blinker != board_empty);
    }
}