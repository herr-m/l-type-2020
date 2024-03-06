#ifndef _BASESHIP_H_
#define _BASESHIP_H_

#include "FriendShipAbstract.hpp"
#include "../Projectils/AllProj.hpp"
#include "../ShootingPatterns/AllShootingPattern.hpp"
#include "../PointInSpaceDS.hpp"

class BaseShip final : public FriendShipAbstract {
    BaseShip(PointInSpaceDS p, unsigned spriteID) :
        ScreenObjAbstract(p, spriteID, {8,8}), FriendShipAbstract(BasicProj::makeToPos, new ShootingPatternLine(), 25.f) {}
  public:
    static BaseShip* makeToPos(const PointInSpaceDS& p, const unsigned spriteID) {return new BaseShip(p, spriteID);}
    virtual  ~BaseShip() noexcept = default;
};

#endif
