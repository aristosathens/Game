// Aristos Athens

//
// Compiler guard
//

#ifndef GAME_MAP_H
#define GAME_MAP_H

//
// Include
//

#include "SDL.h"
#include "SDL_image.h"

#include <array>

// #include <string>

//
// Types
//

template<class T, size_t ROW, size_t COL>
using matrix_t = std::array<std::array<T, COL>, ROW>;

enum Terrain
{
    W,
    D,
    G,
};

enum Level
{
    level1,
};

//
// Class
//

class GameMap
{
    //
    // Public
    //
    public:
    GameMap();
    ~GameMap();

    void load_map(Level = level1);
    void render();

    //
    // Private
    //
    private:
    SDL_Rect source;
    SDL_Rect dest;
    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* water;

    matrix_t<Terrain, 20, 25>* map;
};

#endif // GAME_MAP_H