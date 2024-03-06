#ifndef _SPEEDPOWERUPABSTRACT_H_
#define _SPEEDPOWERUPABSTRACT_H_

#include "../Projectils/ProjectilAbstract.hpp"
#include "../FriendShips/FriendShipAbstract.hpp"

class SpeedPowerUpAbstract : virtual public PowerUpAbstract {
    float _backedSpeed;
    const float _newSpeed;
  protected:
    SpeedPowerUpAbstract(float speed) noexcept : _newSpeed(speed) {}
  public:
    void saveStats(FriendShipAbstract& ship) override {_backedSpeed = ship._speed;}
    void boostFriend(FriendShipAbstract& ship) override {ship._speed = _newSpeed;}
    void restaureFriend(FriendShipAbstract& ship) override {ship._speed = _backedSpeed;}
    inline virtual ~SpeedPowerUpAbstract() = 0; // inline for linker purpose (force to be abstract)
};
SpeedPowerUpAbstract::~SpeedPowerUpAbstract() = default;
#endif
