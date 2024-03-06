#ifndef _HEALTHOBJABSTRACT_H_
#define _HEALTHOBJABSTRACT_H_

#include "ScreenObjAbstract.hpp"
#include "DammageObjAbstract.hpp"

class HealthObjAbstract : virtual public ScreenObjAbstract {
    const unsigned _maxHealth;
  protected:
    int _health, _numLives;
    void loseLive() {--_numLives;}
  public:
    HealthObjAbstract(unsigned hp, unsigned numLives) noexcept : _maxHealth(hp), _health(hp), _numLives(numLives) {}
    HealthObjAbstract(unsigned hp, unsigned numLives, double invincibleDelta) noexcept :
        _maxHealth(hp), _health(hp), _numLives(numLives){}
    void takeDammageFrom(const DammageObjAbstract& dObj, float coef)
        {_health -= dObj._dammage*coef; if(_health<=0){loseLive(); _health=_maxHealth;};}
    bool isDead() const {return _numLives <= 0;}
    auto getNumberLives() const {return _numLives;}
    virtual ~HealthObjAbstract() = default;
};

#endif
