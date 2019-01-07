// Aristos Athens

//
// Compiler guard
//

#ifndef COMPONENT_POSITION_H
#define COMPONENT_POSITION_H

//
// Include
//

#include "ECS.h"

//
// Class
//

class PositionComponent : public Component
{
    //
    // Public
    //
    public:
    int x() const { return x_pos; }
    int y() const { return y_pos; }

    void init() override
    {
        set_position(0, 0);
    }

    void update() override
    {
        ++x_pos;
        ++y_pos;
    }

    void set_position(int in_x, int in_y)
    {
        x_pos = in_x;
        y_pos = in_y;
    }

    //
    // Private
    //
    private:
    int x_pos;
    int y_pos;
};

#endif // COMPONENT_POSITION_H