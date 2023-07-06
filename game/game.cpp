#include "game.h"
#include "../utils/utils.h"
#include <iostream>
#include <string>
#include <ctime>
#include <SDL2/SDL.h>



// Initialize gameboard size 
Game::Game(GameBoard board) : gameboard(board), org_gameboard(board),
                              GRID_HEIGHT(board.size()), GRID_WIDTH(board[0].size()){};



// Loads .bmp image
bool Game::load_texture(std::string path){

    // To draw a image we need to create a temporary surface object.
	SDL_Surface* loaded_surface = SDL_LoadBMP(path.c_str());

	if(loaded_surface == nullptr){
		std::cerr << "Unable to load image." << IMG_GetError() << "\n";
        return false;
	}

    //Create texture from surface pixels
    info_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if(info_texture == nullptr){
        std::cerr << "Unable to create texture." << SDL_GetError() << "\n";
        return false;
    }

    // Setup infoview as a square in the middle of the screen
    infoview.x = (SCREEN_WIDTH - loaded_surface->w) / 2;
    infoview.y = (SCREEN_HEIGHT - loaded_surface->h) / 2;
    infoview.w = loaded_surface->w;
    infoview.h = loaded_surface->h;

    // Remove temporary loaded surface
    SDL_FreeSurface(loaded_surface);

	return true;
}

// Draw texture to screen
void Game::render_info(){
    // Render texture to screen
    SDL_RenderSetViewport(renderer, &infoview);
    SDL_RenderCopy(renderer, info_texture, NULL, NULL);
    // Reset renderer back to whole window
    SDL_RenderSetViewport(renderer, NULL);
    // Draw image
    SDL_RenderPresent(renderer);
}

// Start the game
void Game::run()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return;
    }

    // Create Window
    window = SDL_CreateWindow("Conway's Game of Life",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (window == nullptr){
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        close();
        return;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr){
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        close();
        return;
    }

    // Prepare texture for showing info
    if (!load_texture(info_path)){
        close();
        return;
    }

    // create grid to draw into
    create_grid();

    running = true;
    game_loop();
}

/* 
Loop while program is alive.
Delay changes to make it visually pleasing to user. 

while true:
    before = time before updates
    make updates to game
    after = time after updates

    diff = time elapsed during updates
    if diff < designed frame show time
        delay remaining time (freeze image to screen)
 */
void Game::game_loop()
{
    // init vars;
    Uint32 before;
    Uint32 after;

    while (running){
        before = SDL_GetTicks();

        // game control
        get_key_press();
        handle_game_state();
        
        // delay if frame ready too early
        after = SDL_GetTicks();
        int diff = after - before;
        if (diff < FRAME_TIME_MS)
        {
            SDL_Delay(FRAME_TIME_MS - diff);
        }
    }

}

 /*
 Handles user interactions

If info is to be shown: set game to pause and show info.
Else if game is paused and info is not shown: show gameboard. If user has chosen to reset 'level' -> update gameboard to starting state.
Else: make normal update and render it to screen.
*/
void Game::handle_game_state(){
    if(info_shown){
        is_paused = true;
        render_info();
    }
    else if (is_paused && !info_shown){
        if (do_reset){update_grid();}
        render_grid();
    }
    else{
        update_grid();
        render_grid();
    }
}

// Handle key input events
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
                    reset_board_random(gameboard);
                    org_gameboard = gameboard;
                    break;
                
                // show info
                case SDLK_i:
                    info_shown = !info_shown;
                    break;
            }
        }
    }
}

// update backend board using utils lib
void Game::update_grid()
{
    gameboard = update_board(gameboard);

    // Reset gameboard to starting state
    if (do_reset){
        gameboard = org_gameboard;
        do_reset = false;
    }
}


/* 
Create grid only once and update it elsewhere.

Window width and height cant always be divided equally.
Some cells must be bigger than others.
If cells would be equal size padding would result.
If remainder size is not divided among as many cells as possible, some cells would be visually bigger than others.
 */
void Game::create_grid(){

    // This is magical function, don't change anything!
    int w = SCREEN_WIDTH / GRID_WIDTH;
    int h = SCREEN_HEIGHT / GRID_HEIGHT;
    int padw = SCREEN_WIDTH % GRID_WIDTH;
    int padh = SCREEN_HEIGHT % GRID_HEIGHT;

    int cur_y {0};
    for (size_t y = 0; y < gameboard.size(); y++){
        std::vector<SDL_Rect> row;

        int cur_x {0};
        int row_pad {padw};
        int height {h + (padh > 0)};

        for (size_t x = 0; x < gameboard[0].size(); x++){
            SDL_Rect rect;

            rect.x = cur_x;
            rect.y = cur_y;
            rect.w = w + (row_pad > 0);
            rect.h = height;

            cur_x += rect.w;
            row_pad--;
            row.push_back(rect);
        }
        cur_y += height;
        padh--;

        gamegraphic.push_back(row);
    }
}

 
//Color all cells in the layout based on backend gameboard.
void Game::render_grid()
{
    // Set render to color all cells to dark gray.
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    // Set render color 'golden'
    SDL_SetRenderDrawColor(renderer, 255, 204, 0, 255);

    // Color all alive cells
    for (size_t y = 0; y < gameboard.size(); y++){
        for (size_t x = 0; x < gameboard[0].size(); x++){

            if (gameboard[y][x] == 1){
                SDL_Rect& rect = gamegraphic[y][x];
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }  
    // Update Game
    SDL_RenderPresent(renderer);
}


// Cleanup before exiting
void Game::close()
{
	// free loaded image
	SDL_DestroyTexture(info_texture);
	info_texture = nullptr;

	// destroy renderer	
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

    // close window
    SDL_DestroyWindow(window);
	window = nullptr;

    // cleanup sdl subsystems
    SDL_Quit();
}