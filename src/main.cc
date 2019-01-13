// Aristos Athens

#include "game.h"
#include "util/print.h"
#include "util/vector.h"

int main(int argc, char* argv[])
{
    
    Vector v({1.0, 2.0});
    Vector v2({3.0, 4.0});
    Vector v3({5.0, 6.0});
    v += v2;
    println(v);
    println(v + v2 + v3);

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