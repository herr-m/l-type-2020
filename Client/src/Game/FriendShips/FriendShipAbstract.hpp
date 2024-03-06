#ifndef _FRIENDSHIP_H_
#define _FRIENDSHIP_H_

#include <memory>

#include "../GameObjAbstract/ScreenObjAbstract.hpp"
#include "../GameObjAbstract/ShootingObjAbstract.hpp"
#include "../GameObjAbstract/HealthObjAbstract.hpp"
#include "../GameObjAbstract/DammageObjAbstract.hpp"
#include "../PowerUp/PowerUpAbstract.hpp"
#include "../FriendShipInfoSerial.hpp"


const unsigned ONLIVELOST = 25, HP = 100, LIVES = 3;

class FriendShipAbstract : public ShootingObjAbstract, public HealthObjAbstract, public DammageObjAbstract{
    friend class ProjectilPowerUpAbstract;
    friend class ShootingPatternPowerUpAbstract;
    friend class SpeedPowerUpAbstract;
    void updatePos(const float) override final {}; // define and forbid use of this funciton (accecibility has changed)
    float _speed;
    std::unique_ptr<PowerUpAbstract> _activePowerUP = nullptr;
    const PointInSpaceDS _spawnPos=_pos; // pos where constructed first
  protected:
    FriendShipAbstract(ProjectilAbstract*(*f)(const PointInSpaceDS&, Dir, float, float), ShootingPatternAbstract* sPat, float speed) :
        ShootingObjAbstract(UP, f, sPat), HealthObjAbstract(HP, LIVES), DammageObjAbstract(ONLIVELOST), _speed(speed) {}
  public:
    void moveUP(const double limUp, const double elapsedTime)
        {double tmp=_pos.y-_speed*elapsedTime; if(tmp>limUp) _pos.y=tmp;}
    void moveDown(const double limDown, const double elapsedTime)
        {double tmp=_pos.y+_speed*elapsedTime; if(tmp<limDown) _pos.y=tmp;}
    void moveLeft(const double limLeft, const double elapsedTime)
        {double tmp=_pos.x-_speed*elapsedTime; if(tmp>limLeft) _pos.x=tmp;}
    void moveRight(const double limRight, const double elapsedTime)
        {double tmp=_pos.x+_speed*elapsedTime; if(tmp<limRight) _pos.x=tmp;}

    void usePowerUP(std::unique_ptr<PowerUpAbstract>& pUP)
        {if(_activePowerUP) _activePowerUP->restaureFriend(*this);
        _activePowerUP = std::move(pUP); _activePowerUP->saveStats(*this); _activePowerUP->boostFriend(*this);}
    bool hasPowerUp() const {return static_cast<bool>(_activePowerUP);}
    bool hasInactivePowerUP() const {return _activePowerUP->isConsumed();}
    void increasePowerUPTimer(const float elapsedTime) {_activePowerUP->timerMovesOn(elapsedTime);}
    void removeUsedPowerUP(){_activePowerUP->restaureFriend(*this); _activePowerUP.reset();}
    void respawn() {_pos=_spawnPos;}
    auto getShipInfo() const {return FriendShipInfoSerial(_health, _numLives, _spriteID);}

    inline virtual ~FriendShipAbstract() noexcept = 0;
};

FriendShipAbstract::~FriendShipAbstract() noexcept = default;
#endif
