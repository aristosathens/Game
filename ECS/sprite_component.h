// Aristos Athens

//
// Compiler guard
//

#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

//
// Include
//

#include "components.h"
#include "src/texture_manager.h"

#include "SDL.h"


//
// Class
//

class SpriteComponent : public Component
{
    //
    // Public
    //
    public:
    SpriteComponent() = default;
    SpriteComponent(const std::string& path)
    {
        set_texture(path);
    }

    void init() override
    {
        position = &entity->get_component<PositionComponent>();
        source_rect.x = 0;
        source_rect.y = 0;
        source_rect.w = DEFAULT_SOURCE_RECT_WIDTH;
        source_rect.h = DEFAULT_SOURCE_RECT_HEIGHT;
        dest_rect.w = DEFAULT_DEST_RECT_WIDTH;
        dest_rect.h = DEFAULT_DEST_RECT_HEIGHT;
    }

    void set_texture(const std::string& path)
    {
        texture = TextureManager::load_texture(path);
    }

    void update() override
    {
        dest_rect.x = position->x();
        dest_rect.y = position->y();
    }

    void render() override
    {
        TextureManager::draw(texture, source_rect, dest_rect);
    }

    //
    // Private
    //
    private:
    PositionComponent* position;
    SDL_Texture* texture;
    SDL_Rect source_rect;
    SDL_Rect dest_rect;
};

#endif // SPRITE_COMPONENT_H