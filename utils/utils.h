#if !defined(UTILS)
#define UTILS

#include <vector>
#include <string>
#include <array>
#include <iostream>

using GameBoard = std::vector<std::vector<int>>;


// Random between, hidden from main view
namespace rndBtw{int randomBetween(int min, int max);};

GameBoard create_board(int width, int height);

GameBoard update_board(const GameBoard &current_board);

void reset_board_random(GameBoard& gameboard);

void print_msg(const std::string&);

void file_to_board(GameBoard &current_board, std::string& file_name);

bool can_spawn(int cur_pos_value, int n_neighbours);

bool is_over_populated(int cur_pos_value, int n_neighbours);

bool is_under_populated(int cur_pos_value, int n_neighbours);

int get_n_alive_neighbors(const GameBoard &board, int cur_cell_row, int cur_cell_col);

std::vector<int> unpack_size(char **begin, char **end);

#endif // UTILS
