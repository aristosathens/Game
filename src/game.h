// Aristos Athens

//
// Compiler guard
//

#ifndef GAME_H
#define GAME_H

//
// Include
//

// #include "game_object.h"

#include "SDL.h"
#include "SDL_image.h"

#include <string>

//
// Constants
//

struct Color
{
    int r, g, b;
};

const Color Black = Color {0x00, 0x00, 0x00};
const Color White = Color {0xFF, 0xFF, 0xFF};
const Color Red = Color {0xFF, 0x00, 0x00};
const Color DefaultColor = Black;

//
// Classes
//

class Game
{
    //
    // Public
    //
    public:
    Game();
    ~Game();

    void init(const std::string title,
                const std::string assets_folder,
                size_t x,
                size_t y,
                size_t width,
                size_t height,
                bool full_screen);
    void handle_events();
    void update();
    void render();
    void clean();

    inline bool running() { return is_running; }

    static SDL_Renderer* renderer;

    //
    // Private
    //
    private:
    bool is_running;
    SDL_Window* window;
    std::string assets;

};

#endif // GAME_H