#ifndef _GAMEOBJCONTAINERDS_H_
#define _GAMEOBJCONTAINERDS_H_

#include <list>
#include <memory>

#include "Projectils/ProjectilAbstract.hpp"
#include "Ennemies/EnnemyBaseAbstract.hpp"
#include "PowerUp/PowerUpAbstract.hpp"
#include "FriendShips/FriendShipAbstract.hpp"

struct GameObjContainerDS final {
    std::list<std::unique_ptr<EnnemyBaseAbstract>> ennemies{};
    std::list<std::unique_ptr<ProjectilAbstract>> ennemyProj{};
    std::list<std::unique_ptr<ProjectilAbstract>> friendProj{};
    std::list<std::unique_ptr<PowerUpAbstract>> powerUp{};
    std::list<std::unique_ptr<FriendShipAbstract>> friends{};

    GameObjContainerDS() noexcept = default;
    GameObjContainerDS(const GameObjContainerDS&) = delete;
    GameObjContainerDS(GameObjContainerDS&&) = delete;
    GameObjContainerDS& operator=(const GameObjContainerDS&) = delete;
    GameObjContainerDS& operator=(GameObjContainerDS&&) = delete;
};

#endif
