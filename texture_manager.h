// Aristos Athens

//
// Compiler guard
//

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

//
// Include
//

#include "SDL.h"
#include "SDL_image.h"

#include <string>
#include <stdexcept>

//
// Class
//

class TextureManager
{
    public:
    static inline void init(SDL_Renderer* in_renderer) { renderer = in_renderer; }
    static SDL_Texture* load_texture(const std::string file_name);
    static void draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect dest);

    private:
    static SDL_Renderer* renderer;
};

//
// End compiler guard
//

#endif // TEXTURE_MANAGER_H