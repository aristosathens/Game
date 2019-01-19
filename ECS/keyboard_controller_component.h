// Aristos Athens

//
// Compiler guard
//

#ifndef KEYBOARD_CONTROLLER_H
#define KEYBOARD_CONTROLLER_H

//
// Include
//

#include "components.h"
#include "src/game.h"

//
// Class
//

class KeyboardControllerComponent : public Component
{
    //
    // Public
    //
    public:
    void init() override
    {
        transform = &entity->get_component<TransformComponent>();
    }

    void update() override
    {
        if (Game::event().type == SDL_KEYDOWN) {
            switch (Game::event().key.keysym.sym) {
                case SDLK_w:
                    transform->velocity().set_y(-1);
                    break;
                case SDLK_a:
                    transform->velocity().set_x(-1);
                    break;
                case SDLK_s:
                    transform->velocity().set_y(1);
                    break;
                case SDLK_d:
                    transform->velocity().set_x(1);
                    break;
            }
        }

        if (Game::event().type == SDL_KEYUP) {
            switch (Game::event().key.keysym.sym) {
                case SDLK_w:
                    transform->velocity().set_y(0);
                    break;
                case SDLK_a:
                    transform->velocity().set_x(0);
                    break;
                case SDLK_s:
                    transform->velocity().set_y(0);
                    break;
                case SDLK_d:
                    transform->velocity().set_x(0);
                    break;
            }
        }
    }

    //
    // Private
    //
    private:
    TransformComponent* transform;

};

#endif // KEYBOARD_CONTROLLER_H