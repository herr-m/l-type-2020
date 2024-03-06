#ifndef _WORLD_H_
#define _WORLD_H_

#include <stack>
#include <memory>
#include <cstddef> //std::size_t
#include <stack>

#include "DataBaseSpawnDS.hpp"
#include "Ennemies/EnnemyBaseAbstract.hpp"
#include "PointInSpaceDS.hpp"


class World final{
    constexpr static const double _deltaPos = 10.f;
    std::unique_ptr<std::stack<DataBaseSpawnDS>> _spawnContainer = std::make_unique<std::stack<DataBaseSpawnDS>>();
  public:
    double _worldPos = 0;
    World() = default;
    World(std::stack<DataBaseSpawnDS>* stack) noexcept : _spawnContainer(stack) {}
    void addElement(const DataBaseSpawnDS e) {_spawnContainer->push(e);}
    void worldMoveOn(const float& elapsedTime) {if(!allSpawned()) _worldPos += _deltaPos * elapsedTime;}
    bool timeHasCome() const {return !allSpawned()? _spawnContainer->top().triggerPos <= _worldPos : false;}
    bool allSpawned() const {return _spawnContainer->empty();}
    DataBaseSpawnDS popAndReturnNext() {auto tmp = _spawnContainer->top(); _spawnContainer->pop(); return tmp;}
    World(World&& other) noexcept :
        _worldPos(other._worldPos) , _spawnContainer(std::move(other._spawnContainer))  {}
    World(const World& other) :
        _worldPos(other._worldPos), _spawnContainer(new std::stack<DataBaseSpawnDS>(*other._spawnContainer)) {}
    World& operator=(const World& other)
        {_worldPos=other._worldPos; _spawnContainer.reset(new std::stack<DataBaseSpawnDS>(*other._spawnContainer)); return *this;}
    World& operator=(World&& other) noexcept
        {_worldPos=other._worldPos; _spawnContainer.reset(std::move(other._spawnContainer).release()); return *this;}
    ~World() = default;
};
#endif
