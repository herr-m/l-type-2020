
#ifndef _ALLENNEMYBOSS_H_
#define _ALLENNEMYBOSS_H_

#include "EnnemyBossAbstract.hpp"
#include "../../Projectils/AllProj.hpp"
#include "../../ShootingPatterns/AllShootingPattern.hpp"
#include "../../MovementPatterns/AllMovementPattern.hpp"

class BossBasic final : public EnnemyBossAbstract {
    BossBasic(PointInSpaceDS p) noexcept :
        ScreenObjAbstract(p, 13, {6, 32}),
        EnnemyBossAbstract(3000, 500, 1000, BasicProj::makeToPos, new ShootingPatternTripleShot(), new MovementPatternLatteralMove(), 20) {}
  public:
        static EnnemyBaseAbstract* makeToPos(const PointInSpaceDS& p) {return new BossBasic(p);}
};

class BossStaticSun final : public EnnemyBossAbstract {
    BossStaticSun(PointInSpaceDS p) noexcept :
        ScreenObjAbstract(p, 14, {6, 32}),
        EnnemyBossAbstract(3000, 500, 1000, BasicProj::makeToPos, new ShootingPatternSun(), new MovementPatternNull(), 50) {}
  public:
        static EnnemyBaseAbstract* makeToPos(const PointInSpaceDS& p) {return new BossStaticSun(p);}
};

class BossOP final : public EnnemyBossAbstract {
    BossOP(PointInSpaceDS p) noexcept :
        ScreenObjAbstract(p, 15, {6, 32}),
        EnnemyBossAbstract(3000, 500, 1000, BasicProj::makeToPos, new ShootingPatternSun(), new MovementPatternLatteralMove(), 50) {}
  public:
        static EnnemyBaseAbstract* makeToPos(const PointInSpaceDS& p) {return new BossOP(p);}
};

#endif
