#include "utils.h"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <array>


// print to console
void print_msg(const std::string& msg){
    std::cout << msg << "\n";
}

// Random values between min & max
namespace rndBtw{

    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    
    // randon range int
    int randomBetween(int min, int max){
        std::uniform_int_distribution<int> distr(min, max);
        return distr(generator);
    }
};


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

// A new cell can be born if there are exactly three alive neighbours
bool can_spawn(int cur_pos_value, int n_neighbours){
    return cur_pos_value == 0 && n_neighbours == 3;
}
// The old cell is destroyed if there are over three neighbours
bool is_over_populated(int cur_pos_value, int n_neighbours){
    return cur_pos_value == 1 && n_neighbours > 3;
}
// The old cell is destroyed if there are less than two neighbours
bool is_under_populated(int cur_pos_value, int n_neighbours){
    return cur_pos_value == 1 && n_neighbours < 2;
}



// Updates board based on the rules of Game of Life
GameBoard update_board(const GameBoard& current_board){

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


/* 
Gets patterns from txt file to board
Draw patter starting from top left corner.
 */
void file_to_board(GameBoard& current_board, std::string& file_name){

    std::ifstream file_stream(file_name);

    //Check if file can be opened.
    if (!file_stream.is_open()) {
        std::cout << "Failed to open file \n";
        return;
    }

    int n_cols = current_board[0].size();
    int n_rows = current_board.size();

    // create a new board with same size
    GameBoard updated_board = create_board(n_cols, n_rows);

    //Insert to new board from file
    for (int row = 0; row < n_rows; row++){
        std::string line;
        if(std::getline(file_stream, line)){
            for (int col = 0; col < n_cols; col++){
                if(line[col] == '1') {
                    updated_board[row][col] = 1;
                }
                else {
                    updated_board[row][col] = 0;
                }
            }
        }
    }

    //Updates current board
    current_board = updated_board;
    file_stream.close();

}

// Set board values to 0 or 1 randomly
void reset_board_random(GameBoard& gameboard){
    for (size_t row = 0; row < gameboard.size(); row++){
        for (size_t col = 0; col < gameboard[0].size(); col++){
            gameboard[row][col] = rndBtw::randomBetween(0, 1);
        }
    }
}


// Unpack numbers from cmd char* to int vector
std::vector<int> unpack_size(char** begin, char** end){
    std::vector<int> size;
    try{
        for (auto it = begin; it != end; it++){
            size.push_back(std::stoi(*it));
        }
    }
    catch(const std::exception& e){
        return size;
    }

    return size;    
}