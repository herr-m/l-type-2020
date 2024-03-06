#ifndef _SCOREOBJABSTRACT_H_
#define _SCOREOBJABSTRACT_H_

#include "ScreenObjAbstract.hpp"

class ScoreObjAbstract : virtual public ScreenObjAbstract {
    const unsigned _score;
  public:
    ScoreObjAbstract(unsigned score) noexcept : _score(score) {};
    auto getScore() const {return _score;}
    virtual ~ScoreObjAbstract() = default;
};

#endif
