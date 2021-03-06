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

    ~SpriteComponent()
    {
        TextureManager::destroy_texture(texture);
    }

    void init() override
    {
        transform = &entity->get_component<TransformComponent>();
        source_rect.x = 0;
        source_rect.y = 0;
        source_rect.w = transform->size().x();
        source_rect.h = transform->size().y();

    }

    void set_texture(const std::string& path)
    {
        texture = TextureManager::load_texture(path);
    }

    void update() override
    {
        dest_rect.x = static_cast<int>(transform->position().x());
        dest_rect.y = static_cast<int>(transform->position().y());
        dest_rect.w = transform->size().x() * transform->scale();
        dest_rect.h = transform->size().y() * transform->scale();
    }

    void render() override
    {
        TextureManager::draw(texture, source_rect, dest_rect);
    }

    //
    // Private
    //
    private:
    TransformComponent* transform;
    SDL_Texture*        texture;
    SDL_Rect            source_rect;
    SDL_Rect            dest_rect;
};

#endif // SPRITE_COMPONENT_H