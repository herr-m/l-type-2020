#ifndef _MOVINGOBJABSTRACT_H_
#define _MOVINGOBJABSTRACT_H_

#include "ScreenObjAbstract.hpp"
#include "../MovementPatterns/MovementPatternAbstract.hpp"

#include <memory>

class MovingObjAbstract : virtual public ScreenObjAbstract {
    const std::unique_ptr<MovementPatternAbstract> _mPat;
  protected:
    MovingObjAbstract(MovementPatternAbstract* mPat) : _mPat(mPat) {}
  public:
    void updatePos(const float elapsedTime) override {_mPat->modifyPosition(_pos, elapsedTime);}
    inline virtual ~MovingObjAbstract() = 0;
};

MovingObjAbstract::~MovingObjAbstract() = default;
#endif
