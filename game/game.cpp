#include "game.h"
#include <iostream>
#include <string>
#include <ctime>
#include <SDL2/SDL.h>


// Initialize gameboard size 
Game::Game(GameBoard board) : gameboard(board), org_gameboard(board),
                              GRID_HEIGHT(board.size()), GRID_WIDTH(board[0].size()){};



void Game::run()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

    // Create Window
    window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

    running = true;
    gameLoop();
}


void Game::gameLoop()
{
    Uint32 before, second = SDL_GetTicks(), after;
    int frame_time, frames = 0;

    while (running)
    {
        before = SDL_GetTicks();

        get_key_press();
        update();
        render();
        
        frames++;
        after = SDL_GetTicks();
        frame_time = after - before;

        if (after - second >= 1000)
        {
            frames = 0;
            second = after;
        }

        if (FRAME_RATE > frame_time)
        {
            SDL_Delay(FRAME_RATE - frame_time);
        }
    }

}


void Game::get_key_press()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT){running = false;}
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
                // quit
                case SDLK_ESCAPE:
                    running = false;
                    break;

                // restart
                case SDLK_RETURN:
                    do_reset = true;
                    break;

                // pause
                case SDLK_SPACE:
                    is_paused = !is_paused;
                    break;

                // random init
                case SDLK_r:
                    reset_board_random();
                    org_gameboard = gameboard;
                    break;
            }
        }
    }
}

void Game::update()
{
    // update board using utils lib
    if (!is_paused){
        this->gameboard = update_board(this->gameboard);
    }
    if (do_reset){
        gameboard = org_gameboard;
        do_reset = false;
    }
}


void Game::reset_board_random(){
    for (size_t row = 0; row < gameboard.size(); row++)
    {
        for (size_t col = 0; col < gameboard[0].size(); col++)
        {
            if(rndBtw::randomBetween(0, 1)){
                gameboard[row][col] = 1;
            }
        }
        
    }
}

void Game::render()
{
    SDL_FRect rect;
    rect.w = static_cast<float>(SCREEN_WIDTH) / GRID_WIDTH;
    rect.h = static_cast<float>(SCREEN_WIDTH) / GRID_HEIGHT;

    // Clear screen and set all as non alive cells
    SDL_SetRenderDrawColor(renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(renderer);

    // Render cell color alive
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xCC, 0x00, 0xFF);

    // Color all alive cells
    for (size_t y = 0; y < gameboard.size(); y++){
        for (size_t x = 0; x < gameboard[0].size(); x++){
            if (gameboard[y][x] == 1){
                rect.x = x * rect.w;
                rect.y = y * rect.h;
                SDL_RenderFillRectF(renderer, &rect);
            }
        }
    }  
    // Update Screen
    SDL_RenderPresent(renderer);
}


void Game::close()
{
    // Close Window and cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();
}