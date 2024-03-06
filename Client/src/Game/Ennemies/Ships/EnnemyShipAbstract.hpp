#ifndef _ENNEMYSHIPABSTRACT_H_
#define _ENNEMYSHIPABSTRACT_H_

#include <string>

#include "../EnnemyBaseAbstract.hpp"
#include "../../GameObjAbstract/ScrollObjAbstract.hpp"


class EnnemyShipAbstract : public EnnemyBaseAbstract {
  protected:
    EnnemyShipAbstract(unsigned hp, unsigned d, unsigned score, ProjectilAbstract*(*f)(const PointInSpaceDS&, Dir, float, float),
                        ShootingPatternAbstract* sPat, MovementPatternAbstract* mPat) noexcept :
                            EnnemyBaseAbstract(hp, d, score, f, sPat, mPat) {}
  public:
    void updatePos(const float elapsedTime) final override
      {ScrollObjAbstract::updatePos(elapsedTime); MovingObjAbstract::updatePos(elapsedTime);}
    inline virtual ~EnnemyShipAbstract() noexcept = 0;
};

EnnemyShipAbstract::~EnnemyShipAbstract() noexcept = default;
#endif
