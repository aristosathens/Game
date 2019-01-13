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
// Class
//

class TransformComponent : public Component
{
    //
    // Public
    //
    public:
    TransformComponent() :
        position(3)
        {}
    TransformComponent(double in_x, double in_y, double in_z = 0) :
        position({in_x, in_y, in_z})
        {}

    double x() const { return position[0]; }
    double y() const { return position[1]; }
    double z() const { return position[2]; }
    void set_x(double in_x) { position[0] = in_x; }
    void set_y(double in_y) { position[1] = in_y; }
    void set_z(double in_z) { position[2] = in_z; }
    void step_x(double step) { set_x(x() + step); }
    void step_y(double step) { set_y(y() + step); }
    void step_z(double step) { set_z(z() + step); }

    void set_position(double in_x, double in_y, double in_z)
    {
        set_x(in_x);
        set_y(in_y);
        set_z(in_z);
    }

    void step_position(double x_step, double y_step, double z_step)
    {
        step_x(x_step);
        step_y(y_step);
        step_z(z_step);
    }

    void update() override
    {
        step_position(1, 1, 0);
    }

    //
    // Private
    //
    private:
    Vector position;
};

#endif // TRANSFORM_COMPONENT_H