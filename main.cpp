#include <iostream>
#include <array>
#include <vector>


using GameBoard = std::vector<std::vector<int>>;


/* 
def update(surface, cur, sz):
    // alusta 2d matriisi
    nxt = np.zeros((cur.shape[0], cur.shape[1]))

    // looppaa jokainen solu
    for r, c in np.ndindex(cur.shape):

        // valitsee alueen [n][][]
                           [][c][]
                           [][][n]
        // ja laskee summan eli elossa olevat naapurit - (c elossa)

        num_alive = np.sum(cur[r-1:r+2, c-1:c+2]) - cur[r, c]

        if cur[r, c] == 1 and num_alive < 2 or num_alive > 3:
            col = col_about_to_die
        elif (cur[r, c] == 1 and 2 <= num_alive <= 3) or (cur[r, c] == 0 and num_alive == 3):
            nxt[r, c] = 1
            col = col_alive

        col = col if cur[r, c] == 1 else col_background
        pygame.draw.rect(surface, col, (c*sz, r*sz, sz-1, sz-1))

    return nxt


 */

GameBoard create_board(int width, int height){
    // game board is a vector of (h, w) initialized with zero
    GameBoard array_2d(height, std::vector<int>(width, 0));
    return array_2d;
}


void update(int width, int height){

    // fill with values
    for (size_t i = 0; i < height; i++)
    {
        for (size_t i = 0; i < width; i++)
        {
            /* code */
        }
        
    }
        


}


int main(int argc, char const *argv[])
{
    GameBoard  board = create_board(5,6);
    std::cout << board.size() << board[0].size();

    std::cout << "\n*** Conway's Game of Life ***\n";
    std::cout << "Conway's Game of Life is a cell simulator program that runs trough evolution's and "
                 "cells react to different rules by showing a state of being alive or dead on a board.\n";
    std::cout << "There are four main rules that each cell follows.\n";
    std::cout << "1. Any live cell with fewer that two live neighbors dies due to under population\n";
    std::cout << "2. Any live cell with more than three live neighbors dies due to overpopulation\n";
    std::cout << "3. Any live cell with two or three live neighbors stays unchanged.\n";
    std::cout << "4. Any dead cell with exactly three live neighbors will come to life.\n";
    return 0;
}
