#if !defined(UTILS)
#define UTILS

#include <vector>
#include <string>

using GameBoard = std::vector<std::vector<int>>;


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



#endif // UTILS
