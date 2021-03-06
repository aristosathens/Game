// Aristos Athens

//
// Include
//

#include "texture_manager.h"

//
// Static members
//

SDL_Renderer* TextureManager::renderer = nullptr;

//
// Class methods
//

SDL_Texture* TextureManager::load_texture(const std::string file_name)
{
    if (!renderer) {
        throw std::runtime_error("TextureManager renderer is null. Did you forget to call init()?");
    }
    SDL_Surface* temp_surface = IMG_Load(file_name.c_str());
    if (!temp_surface) {
        throw std::runtime_error("Could not load asset: " + file_name + ". Check for typos.");
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
    SDL_FreeSurface(temp_surface);
    return texture;
}

void TextureManager::destroy_texture(SDL_Texture* texture)
{
    SDL_DestroyTexture(texture);
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect dest)
{
    if (!renderer) {
        throw std::runtime_error("TextureManager renderer is null. Did you forget to call init()?");
    }
    SDL_RenderCopy(renderer, texture, &source, &dest);
}
