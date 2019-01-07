// Aristos Athens

//
// Compiler guard
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

//
// Include
//

#include "SDL.h"
#include "SDL_image.h"

#include <string>

//
// Class
//

class GameObject
{
    //
    // Public
    //
    public:
    static inline void init(SDL_Renderer* in_renderer) { renderer = in_renderer; }
    GameObject(const std::string file_name, int x_start, int y_start);
    ~GameObject();

    void update();
    void render();

    //
    // Private
    //
    private:
    static SDL_Renderer* renderer;
    int x;
    int y;
    SDL_Texture* texture;
    SDL_Rect source_rect;
    SDL_Rect dest_rect;
};

#endif // GAME_OBJECT_H