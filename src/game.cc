// Aristos Athens

//
// Include
//

#include "game.h"

#include "ECS/components.h"
#include "ECS/collision.h"
#include "util/print.h"
#include "game_map.h"
#include "texture_manager.h"

//
// Globals
//

Manager  manager;
GameMap* map;
auto&    player(manager.add_entity());
auto&    wall(manager.add_entity());

//
// Game class static members
//

SDL_Renderer* Game::renderer = nullptr;
SDL_Event     Game::game_event;

//
// Game class methods
//

// Game class constructor
Game::Game()
{

}


// Game class destructor
Game::~Game()
{

}

void Game::init(const std::string title,
                const std::string assets_folder,
                size_t x, size_t y,
                size_t width, size_t height,
                bool full_screen)
{
    assets = assets_folder;

    // Generate SDL flags
    int flags = 0;
    if (full_screen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // Set up SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw std::runtime_error("SDL initialization failed.");
    }
    println("SDL initialized.");

    // Set up SDL window
    window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
    if (!window) {
        throw std::runtime_error("Could not create SDL window.");
    }
    println("Created SDL window.");

    // Set up SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        throw std::runtime_error("Could not create SDL renderer.");
    }
    SDL_SetRenderDrawColor(renderer, White.r, White.g, White.b, 255);
    println("Created SDL renderer.");

    // Set up TextureManager
    TextureManager::init(renderer);

    // Generate map
    map = new GameMap();
    map->load_map(level1);

    // ECS
    player.add_component<TransformComponent>();
    player.get_component<TransformComponent>().velocity().set(1, 1, 0);
    player.add_component<SpriteComponent>(assets + "main_player.png");
    player.add_component<KeyboardControllerComponent>();

    is_running = true;
}

void Game::handle_events()
{
    SDL_PollEvent(&game_event);
    switch (game_event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
    }
}

void Game::update()
{
    manager.refresh();
    manager.update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    map->render();
    manager.render();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    println("Game cleaned.");
}