// Aristos Athens

//
// Compiler guard
//

#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

//
// Include
//

#include "components.h"
#include "util/vector.h"


//
// Classes
//

class TransformComponent : public Component
{
    //
    // Public
    //
    public:
    TransformComponent() :
        _scale(1.0),
        _size(DEFAULT_TRANSFORM_WIDTH, DEFAULT_TRANSFORM_HEIGHT, DEFAULT_TRANSFORM_DEPTH),
        _position(0, 0, 0),
        _velocity(0, 0, 0)
        {}

    double&   scale()    { return _scale;    }
    Vector3D& size()     { return _size;     }
    Vector3D& position() { return _position; }
    Vector3D& velocity() { return _velocity; }

    void update() override
    {
        _position.step(_velocity);
    }

    //
    // Private
    //
    private:
    double   _scale;
    Vector3D _size;
    Vector3D _position;
    Vector3D _velocity;
};

#endif // TRANSFORM_COMPONENT_H