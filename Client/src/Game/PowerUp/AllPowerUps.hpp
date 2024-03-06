#ifndef _ALLPOWERUPS_H_
#define _ALLPOWERUPS_H_

#include "ProjectilPowerUpAbstract.hpp"
#include "ShootingPatternPowerUpAbstract.hpp"
#include "ProjAndShootingPatPowerUpAbstract.hpp"
#include "SpeedPowerUpAbstract.hpp"
#include "../ShootingPatterns/AllShootingPattern.hpp"
#include "../Projectils/AllProj.hpp"
#include "../PointInSpaceDS.hpp"

class TripleShotPUP final : public ShootingPatternPowerUpAbstract {
    TripleShotPUP(PointInSpaceDS p) noexcept :
      ScreenObjAbstract(p, 8, {2,2}), PowerUpAbstract(10), ShootingPatternPowerUpAbstract(new ShootingPatternTripleShot()) {}
  public:
    static PowerUpAbstract* makeToPos(const PointInSpaceDS& p) {return new TripleShotPUP(p);}
};

class TripleShotProjSinPUP final : public ProjAndShootingPatPowerUpAbstract {
    TripleShotProjSinPUP(PointInSpaceDS p) noexcept :
      ScreenObjAbstract(p, 8, {2,2}), PowerUpAbstract(10), ProjAndShootingPatPowerUpAbstract(ProjSinus::makeToPos, new ShootingPatternTripleShot()) {}
  public:
    static PowerUpAbstract* makeToPos(const PointInSpaceDS& p) {return new TripleShotProjSinPUP(p);}
};

class SunShotPUP final : public ShootingPatternPowerUpAbstract{
  SunShotPUP(PointInSpaceDS p) noexcept :
    ScreenObjAbstract(p, 8, {2,2}), PowerUpAbstract(7), ShootingPatternPowerUpAbstract(new ShootingPatternSun()) {}
public:
static PowerUpAbstract* makeToPos(const PointInSpaceDS& p) {return new SunShotPUP(p);}
};

class SunShotProjSinPUP final : public ProjAndShootingPatPowerUpAbstract {
    SunShotProjSinPUP(PointInSpaceDS p) noexcept :
      ScreenObjAbstract(p, 8, {2,2}), PowerUpAbstract(7), ProjAndShootingPatPowerUpAbstract(ProjSinus::makeToPos, new ShootingPatternSun()) {}
  public:
    static PowerUpAbstract* makeToPos(const PointInSpaceDS& p) {return new SunShotProjSinPUP(p);}
};

class SpeedShipPUP final : public SpeedPowerUpAbstract{
    SpeedShipPUP(PointInSpaceDS p ) noexcept : ScreenObjAbstract(p,8,{1,1}),PowerUpAbstract(18),SpeedPowerUpAbstract(45){}
  public:
    static PowerUpAbstract* makeToPos(const PointInSpaceDS& p) {return new SpeedShipPUP(p) ; }
};

class ProjSinPUP final :public ProjectilPowerUpAbstract{
  ProjSinPUP(PointInSpaceDS p ) noexcept : ScreenObjAbstract(p,8,{3,3}),PowerUpAbstract(10),ProjectilPowerUpAbstract( ProjSinus::makeToPos) {}
public:
  static PowerUpAbstract* makeToPos(const PointInSpaceDS& p ) {return new ProjSinPUP(p) ; }
};



#endif
