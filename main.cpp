#include "utils/utils.h"
#include "game/game.h"
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <filesystem>
#include <fstream>
#include <algorithm>


namespace fs = std::filesystem;


// CMD option messages
const std::array<std::string, 2> CMD_OPTIONS{"-p",
                                             "-s"};

// CMD help messages
const std::array<std::string, 2> CMD_HELP{"-p  [string]  path to pattern",
                                          "-s  [int int] Game layout size"};


// Messages
const std::string ERROR_SIZE = "Invalid size! Size must be atleast 3x3 and less than 640x640. Using default values";
const std::string NO_ARGS_MESSAGE = "No args supplied. Using default size of 50x50.";


// Get size from cmd args. Convert string to int
std::vector<int> cmd_get_size(char** begin){
    std::vector<int> size {0,0};
    try{
        for (int i = 0; i < 2; i++){
            size[i] = std::stoi(*(begin + i));
        }
    }

    catch(std::invalid_argument){}
    return size;
}

// Check if user defined board size is valid
bool is_valid_size(std::vector<int>& size){
    int w = size[0];
    int h = size[1];
    return (w >= 3 && w < SCREEN_WIDTH) && (h >= 3 && h < SCREEN_HEIGHT);
}


// Find option location
const std::string* findOption(const std::string* begin, const std::string* end, std::string query){
    return std::find(begin, end, query);
}


// handle commands here (eq. check if following args are qualifiers needed)
void handleOptions(char** begin, char** end, const std::string& option, GameBoard& board){

    // calculate how many arguments follow this option
    int dist = std::distance(begin, end);
    
    // size
    if (option == CMD_OPTIONS[1] && dist >= 2){
        // check if two numbers follow
        std::vector<int> size = unpack_size(begin, end);
        // two numbers found after -s
        if (size.size() != 2){
            print_msg(ERROR_SIZE);
        }
        // init board with user defined size
        board = create_board(size[0], size[1]);
    }
    // path
    else if(option == CMD_OPTIONS[0] && dist >= 1){
        // check if valid path
        if (!fs::exists(*begin)){
            std::cout << "File not found!\n";
        }
        // init board with 
        std::string filepath = *begin;
        file_to_board(board, filepath);

    }
}



int main(int argc, char* argv[])
{

    GameBoard  board = create_board(50, 50);

    char** begin = argv + 1;
    char** end = (argv + argc);


    // no args
    if (argc > 1){
        
         // find matching loc (location of argument end() if not found)
        for (auto it = begin; it != end; it++){
            const std::string* loc = findOption(CMD_OPTIONS.begin(), CMD_OPTIONS.end(), *it);

            // find args following this option eq. (-s int int)
            handleOptions(it + 1, end, *loc, board);
        } 
    }else {
        print_msg(NO_ARGS_MESSAGE);
    }

    // Print command line help to terminal.
    std::cout << "These are the command line options" << "\n";
    print_msg("Set size before loading from a file");
    for (auto &&i : CMD_HELP){
        std::cout << i << "\n";
    }

    //GUI
    Game game {board};
    game.run(); 
      
    return 0;
}