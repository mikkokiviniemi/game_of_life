#if !defined(UTILS)
#define UTILS

#include <vector>
#include <string>
#include <array>
#include <iostream>

using GameBoard = std::vector<std::vector<int>>;



// print keys to user
template<size_t S>
void print_help(const std::array<std::string, S> list, std::string msg){
    std::cout << msg << "\n";
    for (auto &&i : list){
        std::cout << i << "\n";
    }
    std::cout << "\n";
}


// Random between, hidden from main view
namespace rndBtw{int randomBetween(int min, int max);};

void print_msg(const std::string&);

GameBoard create_board(int width, int height);

void print_board(const GameBoard &board);

int get_n_alive_neighbors(const GameBoard &board, int cur_cell_row, int cur_cell_col);

bool can_spawn(int cur_pos_value, int n_neighbours);

bool is_over_populated(int cur_pos_value, int n_neighbours);

bool is_under_populated(int cur_pos_value, int n_neighbours);

GameBoard update_board(const GameBoard &current_board);

void file_to_board(GameBoard &current_board, std::string& file_name);

std::vector<int> unpack_size(char **begin, char **end);

#endif // UTILS
