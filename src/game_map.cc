// Aristos Athens

//
// Include
//

#include "game_map.h"

#include "texture_manager.h"

#include <typeinfo>

//
// Globals
//

static matrix_t<Terrain, 20, 25> level1_matrix = { {
    {D, D, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {D, D, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, D, D, },
    {W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, D, D, },
} };

//
// GameMap class methods
//

// Construct GameMap object.
GameMap::GameMap()
{
    dirt = TextureManager::load_texture("../assets/dirt.png");
    grass = TextureManager::load_texture("../assets/grass.png");
    water = TextureManager::load_texture("../assets/water.png");
    map = nullptr;

    source.x = 0;
    source.y = 0;
    source.w = 32;
    source.h = 32;
    dest.x = 0;
    dest.y = 0;
    dest.w = 32;
    dest.h = 32;
}

// Destruct GameMap object.
GameMap::~GameMap()
{
    TextureManager::destroy_texture(dirt);
    TextureManager::destroy_texture(grass);
    TextureManager::destroy_texture(water);

}

// Load a level into the GameMap.
void GameMap::load_map(Level level /* = level1 */)
{
    switch (level) {
        case level1:
            map = &level1_matrix;
            break;
    }
}

// Render the map to the screen.
void GameMap::render()
{
    if (map == nullptr) {
        throw std::runtime_error("GameMap map is null. Did you forget to call load_map()?");
    }
    for (size_t i = 0; i < map->size(); ++i) {
        auto& row = (*map)[i];
        for (size_t j = 0; j < row.size(); ++j) {
            auto& tile = row[j];
            dest.x = j * 32;
            dest.y = i * 32;
            switch (tile) {
                case W:
                    TextureManager::draw(water, source, dest);
                    break;
                case D:
                    TextureManager::draw(dirt, source, dest);
                    break;
                case G:
                    TextureManager::draw(grass, source, dest);
                    break;
            }
        }
    }
}