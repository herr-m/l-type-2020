#ifndef _POWERUPABSTRACT_H_
#define _POWERUPABSTRACT_H_

#include "../GameObjAbstract/ScrollObjAbstract.hpp"
#include "../Timer.hpp"

class FriendShipAbstract;

class PowerUpAbstract : public ScrollObjAbstract {
    Timer _timer;
  protected:
    explicit PowerUpAbstract(Timer t) noexcept : _timer(t) {}
    PowerUpAbstract() = default; // syntitacly necessary
  public:
    // It is the game who make it so you can't take a power up when you already have one otherwise it would change de defaults stats !!
    virtual void saveStats(FriendShipAbstract&) = 0; // should be called before boostFriend
    virtual void boostFriend(FriendShipAbstract&) = 0;
    virtual void restaureFriend(FriendShipAbstract&) = 0;
    void timerMovesOn(const float elapsedTime) {_timer.incTime(elapsedTime);}
    bool isConsumed() const {return _timer.isOver();}
    virtual ~PowerUpAbstract() = default;
};

#endif
