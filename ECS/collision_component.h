// Aristos Athens

//
// Compiler guard
//

//
// Include
//

#include "components.h"

#include "SDL.h"

#include <string>

class CollisionComponent : public Component
{

    //
    // Public
    //
    public:
    CollisionComponent(std::string tag)
    {
        _tag = tag;
    }

    void init() override
    {
        if (!entity->has_component<TransformComponent>()) {
            entity->add_component<TransformComponent>();
        }
        transform = &entity->get_component<TransformComponent>();
    }

    void update() override
    {
        _hitbox.x = static_cast<int>(transform->position().x());
        _hitbox.y = static_cast<int>(transform->position().y());
        _hitbox.w = transform->size().x() * transform->scale();
        _hitbox.h = transform->size().y() * transform->scale();;
    }

    std::string& tag()    { return _tag; }
    SDL_Rect&    hitbox() { return _hitbox; }

    //
    // Private
    //
    private:
    std::string _tag;
    SDL_Rect    _hitbox;

    TransformComponent* transform;
};