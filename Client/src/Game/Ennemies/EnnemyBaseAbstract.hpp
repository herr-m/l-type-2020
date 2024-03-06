#ifndef _ENNEMYABSTRACT_H_
#define _ENNEMYABSTRACT_H_

#include <memory>
#include <string>

#include "../PointInSpaceDS.hpp"
#include "../GameObjAbstract/HealthObjAbstract.hpp"
#include "../GameObjAbstract/DammageObjAbstract.hpp"
#include "../GameObjAbstract/ScoreObjAbstract.hpp"
#include "../GameObjAbstract/ShootingObjAbstract.hpp"
#include "../Projectils/ProjectilAbstract.hpp"
#include "../GameObjAbstract/MovingObjAbstract.hpp"
#include "../GameObjAbstract/ScrollObjAbstract.hpp"



class EnnemyBaseAbstract : public HealthObjAbstract, public DammageObjAbstract,
                           public ScoreObjAbstract, public ShootingObjAbstract, public MovingObjAbstract, public ScrollObjAbstract{
  protected:
    EnnemyBaseAbstract(unsigned hp, unsigned d, unsigned score, ProjectilAbstract*(*f)(const PointInSpaceDS&, Dir, float, float),
                       ShootingPatternAbstract* sPat, MovementPatternAbstract* mPat) noexcept :
                          HealthObjAbstract(hp, 1), DammageObjAbstract(d), ScoreObjAbstract(score),
                          ShootingObjAbstract(DOWN, f, sPat), MovingObjAbstract(mPat), ScrollObjAbstract() {}
  public:
    void updatePos(const float elapsedTime) = 0;
    inline virtual ~EnnemyBaseAbstract() noexcept = 0;
};

EnnemyBaseAbstract::~EnnemyBaseAbstract() noexcept = default;
#endif
