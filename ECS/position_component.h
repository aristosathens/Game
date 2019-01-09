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
    PositionComponent() : x_pos(0), y_pos(0) {}
    PositionComponent(int in_x, int in_y) : x_pos(in_x), y_pos(in_y) {}

    int x() const { return x_pos; }
    int y() const { return y_pos; }
    void set_x(int in_x) { x_pos = in_x; }
    void set_y(int in_y) { y_pos = in_y; }

    void set_position(int in_x, int in_y)
    {
        x_pos = in_x;
        y_pos = in_y;
    }

    void update() override
    {
        ++x_pos;
        ++y_pos;
    }

    //
    // Private
    //
    private:
    int x_pos;
    int y_pos;
};

#endif // COMPONENT_POSITION_H