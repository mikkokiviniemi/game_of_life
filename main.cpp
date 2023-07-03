#include <iostream>
#include <array>
#include <vector>


using GameBoard = std::vector<std::vector<int>>;


 /*
    Creates a gameboard and initializes all values with zero.
    row_vector:
        n_rows
        col_vector:
            n_cols
            int
*/ 
GameBoard create_board(int width, int height){
    GameBoard array_2d(height, std::vector<int>(width, 0));
    return array_2d;
}


// print board temporary
void print_board(const GameBoard& board){
    for (auto &&row : board){
        for (auto &&cell : row){
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}



// Calculates the total number of alive neighbors for a specific cell.
int get_n_alive_neighbors(const GameBoard& board, int cur_cell_row, int cur_cell_col){
    int n_alive {0};
    int n_cols = board[0].size();
    int n_rows = board.size();


    // Start from previous row (-1)
    for (int row = -1; row < 2; row++){ 
        // Start from previous col
        for (int col = -1; col < 2; col++){

            int neighbor_row = row + cur_cell_row;
            int neighbor_col = col + cur_cell_col;

            if (neighbor_row >= 0 && neighbor_row < n_rows && neighbor_col >= 0 && neighbor_col < n_cols) {
                n_alive += board[neighbor_row][neighbor_col];
            }
        }
    }
    return n_alive - board[cur_cell_row][cur_cell_col];
}


bool can_spawn(int cur_pos_value, int n_neighbours){
    return cur_pos_value == 0 && n_neighbours == 3;
}

bool is_over_populated(int cur_pos_value, int n_neighbours){
    return cur_pos_value == 1 && n_neighbours > 3;
}

bool is_under_populated(int cur_pos_value, int n_neighbours){
    return cur_pos_value == 1 && n_neighbours < 2;
}




// Updates board based on the rules of Game of Life
GameBoard update(const GameBoard& current_board){

    int n_cols = current_board[0].size();
    int n_rows = current_board.size();

    // create a new board with same size
    GameBoard updated_board = create_board(n_cols, n_rows);

    for (int row = 0; row < n_rows; row++){
        for (int col = 0; col < n_cols; col++){

            int cur_cell_value {current_board[row][col]};

            // logic is based on alive neighbors, count them
            int n_neighbours = get_n_alive_neighbors(current_board, row, col);

            // under or over population
            if (is_under_populated(cur_cell_value, n_neighbours) || is_over_populated(cur_cell_value, n_neighbours)){
                updated_board[row][col] = 0;
            }
            // keep alive or birth a new one
            else if((current_board[row][col] == 1) || can_spawn(cur_cell_value, n_neighbours)){
                updated_board[row][col] = 1;
            }
        }
        
    }
    return updated_board;
}


int main(int argc, char const *argv[])
{
    GameBoard  board = create_board(5,6);

    board[2][0]=1;
    board[2][1]=1;
    board[2][2]=1;
    board[1][2]=1;
    board[0][1]=1;
/*
    board[1][1] = 1;
    board[1][2] = 1;
    board[1][3] = 1;
    board[2][1] = 1;
    board[2][2] = 1;
    board[2][3] = 1;
    board[3][1] = 1;
    board[3][2] = 1;
    board[3][3] = 1;
  */

    for(int i = 0; i < 20; i++){
        print_board(board);
        board = update(board);
        std::cout << "\n";
    }

/*     
    
    std::cout << board.size() << board[0].size();

    std::cout << "\n*** Conway's Game of Life ***\n";
    std::cout << "Conway's Game of Life is a cell simulator program that runs trough evolution's and "
                 "cells react to different rules by showing a state of being alive or dead on a board.\n";
    std::cout << "There are four main rules that each cell follows.\n";
    std::cout << "1. Any live cell with fewer that two live neighbors dies due to under population\n";
    std::cout << "2. Any live cell with more than three live neighbors dies due to overpopulation\n";
    std::cout << "3. Any live cell with two or three live neighbors stays unchanged.\n";
    std::cout << "4. Any dead cell with exactly three live neighbors will come to life.\n";*/
    return 0;
}