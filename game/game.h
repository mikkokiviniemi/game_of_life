#if !defined(GAME)
#define GAME

#include "../utils/utils.h"
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


const int SCREEN_WIDTH   = 640;
const int SCREEN_HEIGHT  = 640;


class Game
{
public:
    void run();
    Game(GameBoard);
    

private:
    GameBoard gameboard;
    GameBoard org_gameboard;

    bool running = false;
    bool is_paused {false};
    bool do_reset {false};
    

    const int FRAME_RATE     = 40;
    const int GRID_WIDTH     = 50;
    const int GRID_HEIGHT    = 50;

    SDL_Window * window = nullptr;
    SDL_Renderer * renderer = nullptr;

    // Viewports to info and game layouts
    SDL_Rect topview;
    SDL_Rect bottomview;


    void gameLoop();
    void render();
    void update();
    void get_key_press();
    void close();
    void reset_board_random();

};


SDL_Rect create_layout(int x, int y, int w, int h);

#endif

