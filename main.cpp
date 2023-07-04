#include "utils/utils.h"
#include <iostream>
#include <array>
#include <vector>
#include "game/game.h"



int main(int argc, char const *argv[])
{

    GameBoard  board = create_board(300, 300);

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