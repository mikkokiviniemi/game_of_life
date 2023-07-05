#include "utils/utils.h"
#include "game/game.h"
#include <iostream>
#include <array>
#include <vector>
#include <array>
#include <string>


// Key help
const std::array<std::string, 4> HELP {"r        init random setup",
                                       "space    pause",
                                       "enter    restart",
                                       "esc      quit"};

// Messages
const std::string ERROR_MESSAGE = "Invalid size! Size must be atleast 3x3. Using default values";
const std::string NO_ARGS_MESSAGE = "No args supplied. Using default size.";



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


// print keys to user
void print_help(){
    std::cout << "Keys to operate the program\n";
    for (auto &&i : HELP){
        std::cout << i << "\n";
    }
    std::cout << "\n";
}


int main(int argc, char* argv[])
{

    // default size of the board
    int width = 50;
    int height = 50;

    // if args supplied find the size (w,h)
    if (argc == 1){print_msg(NO_ARGS_MESSAGE);}
    else if (argc == 3){
        std::vector<int> size = cmd_get_size(argv + 1);
        if (size[0] >= 3 && size[1] >= 3){
            width = size[0];
            height = size[1];
        }
        else{print_msg(ERROR_MESSAGE);}
    }else {print_msg(ERROR_MESSAGE);}


    std::cout << "Initializing The Game of Life with size "
              << width << "x" << height <<"\n\n";

    print_help();
    GameBoard  board = create_board(width,height);


/*     board[2][0]=1;
    board[2][1]=1;
    board[2][2]=1;
    board[1][2]=1;
    board[0][1]=1;

    board[10][9]=1;
    board[10][10]=1;
    board[10][11]=1; */


    //GUI
    Game game {board};
    game.run();
    
    return 0;
}