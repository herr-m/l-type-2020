#ifndef _ENNEMYBOSSABSTRACT_H_
#define _ENNEMYBOSSABSTRACT_H_

#include "../EnnemyBaseAbstract.hpp"
#include "../../GameObjAbstract/ScrollObjAbstract.hpp"

class EnnemyBossAbstract : public EnnemyBaseAbstract {
    const double _downOffset;
    bool isToLowestPos() const {return _pos.y >= _downOffset;}
  protected:
    EnnemyBossAbstract(unsigned hp, unsigned d, unsigned score, ProjectilAbstract*(*f)(const PointInSpaceDS&, Dir, float, float),
                       ShootingPatternAbstract* sPat, MovementPatternAbstract* mPat, double downOffset) noexcept :
                            EnnemyBaseAbstract(hp, d, score, f, sPat, mPat), _downOffset(downOffset){}
  public:
    void updatePos(const float elapsedTime) override final
        {if(!isToLowestPos()) ScrollObjAbstract::updatePos(elapsedTime); else MovingObjAbstract::updatePos(elapsedTime);};
    inline virtual ~EnnemyBossAbstract() = 0;
};

EnnemyBossAbstract::~EnnemyBossAbstract() = default;
#endif
