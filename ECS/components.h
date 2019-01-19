// Aristos Athens

//
// Compiler guard
//

#ifndef COMPONENTS_H
#define COMPONENTS_H

//
// Constants
//

// const size_t DEFAULT_SOURCE_RECT_WIDTH = 32;
// const size_t DEFAULT_SOURCE_RECT_HEIGHT = 32;
// const size_t DEFAULT_DEST_RECT_WIDTH = 32;
// const size_t DEFAULT_DEST_RECT_HEIGHT = 32;

// TransformComponent
const int DEFAULT_TRANSFORM_WIDTH = 32;
const int DEFAULT_TRANSFORM_HEIGHT = 32;
const int DEFAULT_TRANSFORM_DEPTH = 0;

//
// Include
//

// Entity Component System
#include "ECS.h"

// All components
#include "transform_component.h"
#include "sprite_component.h"
#include "keyboard_controller_component.h"
#include "collision_component.h"
#include "tile_component.h"

#endif // COMPONENTS_H