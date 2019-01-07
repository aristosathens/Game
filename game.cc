// Aristos Athens

//
// Include
//

#include "game.h"

#include "ECS/components.h"

#include "util.h"
#include "game_map.h"
#include "texture_manager.h"

//
// Globals
//

// GameObject* player;
// GameMap* map;

Manager manager;
auto& newPlayer(manager.add_entity());

//
// Game class static members
//

SDL_Renderer* Game::renderer = nullptr;

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

    // Set up GameObjects
    // GameObject::init(renderer);

    // Set up textures
    assets = assets_folder;

    // player = new GameObject(assets + "main_player.png", 0, 0);
    // map = new GameMap();
    // map->load_map(level1);

    newPlayer.add_component<PositionComponent>();

    is_running = true;
}

void Game::handle_events()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:  // Later we will make closing the window generate an SDL_Quit event.
            is_running = false;
            break;
        default:
            break;
    }
}

void Game::update()
{
    // player->update();
    manager.update();
    print("Player position x: ");
    print(newPlayer.get_component<PositionComponent>().x());
    print(" y: ");
    println(newPlayer.get_component<PositionComponent>().y());
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // Add stuff to render here.
    // Whatever get's rendered first is in the background.

    // map->render();
    // player->render();
    manager.draw();

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    println("Game cleaned.");
}