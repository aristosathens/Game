// Aristos Athens

//
// Compiler guard
//

#ifndef ECS_H
#define ECS_H

//
// Include
//

#include "util/print.h"

#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <array>
#include <memory>

//
// Constants
//

const std::size_t max_num_components = 32;

//
// Forward declarations
//

class Component;
class Entity;

//
// Types
//

using componentID_t = std::size_t;
using component_bitset_t = std::bitset<max_num_components>;
using component_array_t = std::array<Component*, max_num_components>;

//
// Helper functions
//

inline
componentID_t get_component_Type_ID()
{
    static componentID_t last_ID = 0;
    return last_ID++;
}

template<typename T> inline
componentID_t get_component_Type_ID() noexcept
{
    static componentID_t typeID = get_component_Type_ID();
    return typeID;
}

//
// Classes
//

class Component
{
    //
    // Public
    //
    public:
    Entity* entity; // reference to owner
    virtual void init()   {}
    virtual void update() {}
    virtual void render() {}
    virtual ~Component()  {}

    // private:
};

// Keeps list of components
class Entity
{
    //
    // Public
    //
    public:
    void update()
    {
        for (auto& component : components) component->update();
    }

    void render()
    {
        for (auto& component : components) component->render();
    }

    inline bool is_active() const
    {
        return active;
    }

    void destroy()
    {
        active = false;
    }

    template<typename T>
    bool has_component() const
    {
        return component_bitset[get_component_Type_ID<T>()];
    }

    template<typename T, typename... TArgs>
    T& add_component(TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> u_ptr {c};
        components.emplace_back(std::move(u_ptr));

        // Component Type ID is index, set it to c.
        component_array[get_component_Type_ID<T>()] = c;

        // Mark this component type as set.
        component_bitset[get_component_Type_ID<T>()] = true;
        c->init();
        return *c;
    }

    // Allows for example: GameObject.get_component<PositionComponent>().set_x_posision(25)
    template<typename T>
    T& get_component() const
    {
        auto ptr(component_array[get_component_Type_ID<T>()]);
        return *static_cast<T*>(ptr);
    }


    //
    // Private
    //
    private:
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    component_array_t component_array;
    component_bitset_t component_bitset;
};

class Manager
{
    //
    // Public
    //
    public:
    void update()
    {
        for (auto& entity : entities) {
            entity->update();
        }
    }

    void render()
    {
        for (auto& entity : entities) {
            entity->render();
        }
    }

    void refresh()
    {
        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
        [](const std::unique_ptr<Entity> &entity)
        {
            return !entity->is_active();
        }),
        std::end(entities));
    }

    Entity& add_entity()
    {
        Entity* e = new Entity();
        std::unique_ptr<Entity> u_ptr {e};
        entities.emplace_back(std::move(u_ptr));
        return *e;
    }

    //
    // Private
    //
    private:
    std::vector<std::unique_ptr<Entity>> entities;
};

#endif // ECS_H