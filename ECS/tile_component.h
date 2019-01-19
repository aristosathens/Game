// Aristos Athens

//
// Compiler guard
//

#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

//
// Include
//

#include "SDL.h"

#include "components.h"

//
// Class
//

class TileComponent : public Component
{
    //
    // Public
    //
    public:
    TileComponent() = default;
    TileComponent(int in_x, int in_y, int in_w, int in_h, int id)
    {
        _ID = id;
        _rect.x = in_x;
        _rect.y = in_y;
        _rect.w = in_w;
        _rect.h = in_h;
    }

    //
    // Private
    //
    private:
    SDL_Rect            _rect;
    int                 _ID;
    TransformComponent* _transform;
    SpriteComponent*    _sprite;
};

#endif // TILE_COMPONENT_H