#ifndef _PROJECTIL_H_
#define _PROJECTIL_H_

#include "../GameObjAbstract/MovingObjAbstract.hpp"
#include "../GameObjAbstract/DammageObjAbstract.hpp"

#include <memory>
#include <iostream>

enum Dir {UP=-1, DOWN=1};

class ProjectilAbstract : public MovingObjAbstract, public DammageObjAbstract {
    const Dir _dir;
    const float _velX, _velY;
    const float _speed;
    void followVelocity(const float elapsedTime) {_pos.x += _velX*elapsedTime*_speed; _pos.y += _velY*elapsedTime*_dir*_speed;}
  protected:
    ProjectilAbstract(MovementPatternAbstract* mPat, unsigned d, Dir dir, float vX, float vY, float speed) :
        MovingObjAbstract(mPat), DammageObjAbstract(d), _dir(dir), _velX(vX), _velY(vY), _speed(speed){}
  public:
    void updatePos(const float elapsedTime) override final {followVelocity(elapsedTime); MovingObjAbstract::updatePos(elapsedTime);}
    inline virtual ~ProjectilAbstract() = 0;
};

ProjectilAbstract::~ProjectilAbstract() = default;
#endif
