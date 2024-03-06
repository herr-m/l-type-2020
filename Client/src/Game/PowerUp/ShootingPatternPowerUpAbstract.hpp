#ifndef _SHOOTINGPATTERNPOWERUPABSTRACT_H_
#define _SHOOTINGPATTERNPOWERUPABSTRACT_H_

#include "PowerUpAbstract.hpp"
#include "../Projectils/ProjectilAbstract.hpp"
#include "../FriendShips/FriendShipAbstract.hpp"
#include <memory>

class ShootingPatternPowerUpAbstract : virtual public PowerUpAbstract {
    std::unique_ptr<ShootingPatternAbstract> _backedSpat;
    std::unique_ptr<ShootingPatternAbstract> _newSpat;
  protected:
    ShootingPatternPowerUpAbstract(ShootingPatternAbstract* sPat) noexcept : _newSpat(sPat) {}
  public:
    //carefull here you could have undefined behaviours or crash if used in the wrong order !!
    void saveStats(FriendShipAbstract& ship) override {_backedSpat = std::move(ship._sPat);}
    void boostFriend(FriendShipAbstract& ship) override {ship._sPat = std::move(_newSpat);}
    void restaureFriend(FriendShipAbstract& ship) override {ship._sPat = std::move(_backedSpat);}
    inline virtual ~ShootingPatternPowerUpAbstract() = 0; // inline for linker purpose (force to be abstract)
};
ShootingPatternPowerUpAbstract::~ShootingPatternPowerUpAbstract() = default;
#endif
