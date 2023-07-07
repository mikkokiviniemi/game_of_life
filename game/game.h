#if !defined(GAME)
#define GAME

#include "../utils/utils.h"
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


// Window size
const int SCREEN_WIDTH   = 640;
const int SCREEN_HEIGHT  = 640;


// Graphical version of the layout
using GameBoardGraphic = std::vector<std::vector<SDL_Rect>>;


// Make a state that sets the colorinng mode
// Set state with a key h
// when state is coloring
//  listen mouse clicks
//  calculate cell based on mouse position
//  if cell is alive: color it empty : otherwise color it alive
// when coloring pause the program and render individual cell only


// Make a save of the current program when pressed s





/* 
Class that handles running the Game of Life.
Uses SDL for graphics backend.

Features:
    - Random layout initalization           - r
    - Pausing the program                   - space
    - Replay previous round                 - Enter/Return
    - Shows game instructions               - i

    - User defined layout initalization     - cmd -p [string path to pattern] 
    - User defined size                     - cmd -s [int int]

Use:
    Game game {GameBoard (from backend)};
    game.run();

Workflow:
    Init game
    while true:
        Listen and handle key input.
        Update backend layout.
        Update graphical layout based on backend layout.
        Show layout.
    Release resources.

 */
class Game
{
public:

    // run Game instance
    void run();

    // Game constructor
    Game(GameBoard);
    
private:
    // holds backend board vectors
    GameBoard gameboard;
    GameBoard org_gameboard;

    // graphical version of the board
    GameBoardGraphic gamegraphic;

    // program running states
    bool running        {false};
    bool is_paused      {false};
    bool do_reset       {false};
    bool info_shown     {true};
    bool do_pattern     {false};

    // time one frame shows on the screen
    const int FRAME_TIME_MS = 100;

    // game board size
    const int GRID_WIDTH  = 50;
    const int GRID_HEIGHT = 50;

    std::string info_path = {"./resources/conway_info.bmp"};

    // SDL features 
    SDL_Window * window = nullptr;
    SDL_Renderer * renderer = nullptr;

    // Viewport to info
    SDL_Rect infoview;

    // Info texture
    SDL_Texture* info_texture = nullptr;

    // game main loop
    void game_loop();
    // handles user interaction 
    void handle_game_state();
    // Fetches update from backend
    void update_grid();
    // Draws the board to screen
    void render_grid();
    // Listens key events
    void get_key_press();
    // Hand color fills a cell 
    void hand_color_cell();
    // quits the program
    void close();
    // Initializes board layout
    void create_grid();
    // clears cur graphical board
    void clear_board();
    // Draws info box to screen
    void render_info();
    // Loads image to texture
    bool load_texture(std::string path);
    // Get cell from mouse coordinates
    std::pair<int, int> cell_from_coord(int x, int y);
};


#endif

