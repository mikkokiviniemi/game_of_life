#include "utils/utils.h"
#include <iostream>
#include <array>
#include <vector>
#include "game/game.h"



int main(int argc, char* argv[])
{

    std::string arg1 = argv[1];
    int width = std::stoi(arg1);
    std::string arg2 = argv[2];
    int height = std::stoi(arg1);
    

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