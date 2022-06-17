//
// Created by Jakub Górski on 14/06/2022.
//

#ifndef BATTLESHIPS_GAME_ECS_H
#define BATTLESHIPS_GAME_ECS_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;



inline ComponentID getNewComponentTypeID() {
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitset = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;


class Component {
public:
    Entity * entity;

    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component() {}

};

class Entity {
public:

    Entity(Manager& _manager) : mManager(_manager) {}

    void update() {
        for (auto& c : components) c->update();
    }
    void draw () {
        for (auto& c : components) c->draw();
    }

    bool isActive () const { return active; }
    void destroy() { active = false; }

    bool hasGroup(Group _group){
        return groupBitset[_group];
    }

    void addGroup(Group _group);

    void deleteGroup(Group _group){
        groupBitset[_group] = false;
    }

    template <typename T> bool hasComponent() const {
        return componentBitset[getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs){
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr { c };
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitset[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }

    template <typename T> T& getComponent() const {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

private:
    Manager& mManager;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray{};
    ComponentBitset componentBitset;
    GroupBitset groupBitset;

};

class Manager {
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;
public:
    void update() {
        for (auto& e : entities) e->update();
    }
    void draw() {
        for (auto& e : entities) e->draw();
    }

    // erases inactive entities
    void refresh(){

        for(auto i(0u); i < maxGroups; i++){
            auto& v(groupedEntities[i]);
            v.erase(std::remove_if(v.begin(), v.end(),
               [i](Entity* _entity)
               {
                    return !_entity->isActive() || !_entity->hasGroup(i);
               }), v.end());
        }

        entities.erase(std::remove_if(entities.begin(), entities.end(),
  [](const std::unique_ptr<Entity> &_entity){
            return !_entity->isActive();
        }),entities.end());
    }

    void addToGroup(Entity* _entity, Group _group){
        groupedEntities[_group].emplace_back(_entity);
    }

    std::vector<Entity*>& getGroup(Group _group){
        return groupedEntities[_group];
    }

    Entity& addEntity(){
        auto* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr));
        return *e;
    }

};

#endif //BATTLESHIPS_GAME_ECS_H