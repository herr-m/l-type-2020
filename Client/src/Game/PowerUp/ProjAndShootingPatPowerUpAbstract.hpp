#ifndef _PROJANDSHOOTINGPATPOWERUPABSTRACT_H_
#define _PROJANDSHOOTINGPATPOWERUPABSTRACT_H_

#include "ProjectilPowerUpAbstract.hpp"
#include "ShootingPatternPowerUpAbstract.hpp"
#include "../PointInSpaceDS.hpp"

class ProjAndShootingPatPowerUpAbstract : public ProjectilPowerUpAbstract, public ShootingPatternPowerUpAbstract{
  protected:
    ProjAndShootingPatPowerUpAbstract(ProjectilAbstract*(*f)(const PointInSpaceDS&, Dir, float, float), ShootingPatternAbstract* sPat) noexcept :
        ProjectilPowerUpAbstract(f), ShootingPatternPowerUpAbstract(sPat) {}
  public:
    void saveStats(FriendShipAbstract &ship) override
        {ProjectilPowerUpAbstract::saveStats(ship); ShootingPatternPowerUpAbstract::saveStats(ship);}
    void boostFriend(FriendShipAbstract &ship) override
        {ProjectilPowerUpAbstract::boostFriend(ship); ShootingPatternPowerUpAbstract::boostFriend(ship);}
    void restaureFriend(FriendShipAbstract &ship) override
        {ProjectilPowerUpAbstract::restaureFriend(ship); ShootingPatternPowerUpAbstract::restaureFriend(ship);}
    inline virtual ~ProjAndShootingPatPowerUpAbstract() = 0; // inline for linker purpose (force abstract)
};

ProjAndShootingPatPowerUpAbstract::~ProjAndShootingPatPowerUpAbstract() = default;

#endif
