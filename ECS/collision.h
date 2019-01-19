// Aristos Athens

//
// Compiler guard
//

#ifndef COLLISION_H
#define COLLISION_H

//
// Class
//

class Collision
{
    //
    // Public
    //
    public:

    // Axis aligned bounding box
    static bool AABB (const SDL_Rect& a, const SDL_Rect& b)
    {
        if (a.x + a.w >= b.x &&
            b.x + b.w >= a.x &&
            a.y + a.h >= b.y &&
            b.y + b.h >= a.y
        ) {
            return true;
        } else {
            return false;
        }
    }
};

#endif // COLLISION_H