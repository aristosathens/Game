// Aristos Athens

/*
 *
 *  DEPRECATED - USE ECS INSTEAD
 * 
 */

//
// Include
//

#include "game_object.h"

#include "texture_manager.h"

//
// GameObject static members
//

SDL_Renderer* GameObject::renderer = nullptr;

//
// GameObject class methods
//

GameObject::GameObject(const std::string file_name, int start_x, int start_y)
{
    texture = TextureManager::load_texture(file_name);
    x = start_x;
    y = start_y;
}

GameObject::~GameObject()
{

}

void GameObject::update()
{
    static size_t count = 0;

    x = count;
    y = count;

    source_rect.x = 0;
    source_rect.y = 0;
    source_rect.w = 32;
    source_rect.h = 32;

    dest_rect.x = x;
    dest_rect.y = y;
    dest_rect.w = source_rect.w;
    dest_rect.h = source_rect.h;

    ++count;
}

void GameObject::render()
{
    if (!renderer) {
        throw std::runtime_error("GameObject renderer is null. Did you forget to call init()?");
    }
    SDL_RenderCopy(renderer, texture, &source_rect, &dest_rect);
}