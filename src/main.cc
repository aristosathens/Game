// Aristos Athens

#include "game.h"

int main(int argc, char* argv[])
{
    
    const size_t FPS = 60;
    const size_t frame_delay = 1000 / FPS;

    size_t frame_start;
    size_t frame_time;

    Game* game = new Game();
    game->init("Game window",
                "../assets/",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                800,
                640,
                false);

    while (game->running()) {
        frame_start = SDL_GetTicks();
        game->handle_events();
        game->update();
        game->render();

        // Limit framerate
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < frame_delay) {
            SDL_Delay(frame_delay - frame_time);
        }
    }
    
    game->clean();
    return 0;
}