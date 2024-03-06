#ifndef _PROJECTILPOWERUPABSTRACT_H_
#define _PROJECTILPOWERUPABSTRACT_H_

#include "PowerUpAbstract.hpp"
#include "../Projectils/ProjectilAbstract.hpp"
#include "../FriendShips/FriendShipAbstract.hpp"

class ProjectilPowerUpAbstract : virtual public PowerUpAbstract {
    ProjectilAbstract*(*_backedProj)(const PointInSpaceDS&, Dir, float, float);
    ProjectilAbstract*(*const _newProj)(const PointInSpaceDS&, Dir, float, float);
  protected:
    ProjectilPowerUpAbstract(ProjectilAbstract*(*const f)(const PointInSpaceDS&, Dir, float, float)) noexcept : _newProj(f) {}
  public:
    void saveStats(FriendShipAbstract& ship) override {_backedProj = ship._makeProj;}
    void boostFriend(FriendShipAbstract& ship) override {ship._makeProj = _newProj;}
    void restaureFriend(FriendShipAbstract& ship) override {ship._makeProj = _backedProj;}
    inline virtual ~ProjectilPowerUpAbstract() = 0; // inline for linker purpose
};
ProjectilPowerUpAbstract::~ProjectilPowerUpAbstract() = default;
#endif
