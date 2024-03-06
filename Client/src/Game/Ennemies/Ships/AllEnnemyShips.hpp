#ifndef _ALLENNEMYSHIPS_H_
#define _ALLENNEMYSHIPS_H_

#include "EnnemyShipAbstract.hpp"
#include "../../MovementPatterns/AllMovementPattern.hpp"
#include "../../ShootingPatterns/AllShootingPattern.hpp"
#include "../../Projectils/AllProj.hpp"
#include "../../PointInSpaceDS.hpp"

class BoringShip final : public EnnemyShipAbstract {
    BoringShip(PointInSpaceDS p) :
      ScreenObjAbstract(p, 4, {3,3}),
      EnnemyShipAbstract(100, 10, 50, BasicProj::makeToPos, new ShootingPatternLine() , new MovementPatternNull()) {}
  public:
    static EnnemyBaseAbstract* makeToPos(const PointInSpaceDS& p) {return new BoringShip(p);}
};
class ShipProjSin final : public EnnemyShipAbstract {
    ShipProjSin(PointInSpaceDS p) :
      ScreenObjAbstract(p, 5, {3,3}),
      EnnemyShipAbstract(100, 10, 50,ProjSinus::makeToPos, new ShootingPatternLine() , new MovementPatternNull()) {}
  public:
    static EnnemyBaseAbstract* makeToPos(PointInSpaceDS p) {return new ShipProjSin(p);}
};
class ShipSin final : public EnnemyShipAbstract{
  ShipSin(PointInSpaceDS p) :
    ScreenObjAbstract(p, 6, {3,3}),
    EnnemyShipAbstract(100, 10, 50,BasicProj::makeToPos, new ShootingPatternLine() , new MovementPatternVerticalSinus(200)) {}
public:
  static EnnemyBaseAbstract* makeToPos(PointInSpaceDS p) {return new ShipSin(p);}
};
class ShipSinProjSin final : public EnnemyShipAbstract{
  ShipSinProjSin(PointInSpaceDS p) :
    ScreenObjAbstract(p, 6, {3,3}),
    EnnemyShipAbstract(100, 10, 50,ProjSinus::makeToPos, new ShootingPatternLine() , new MovementPatternVerticalSinus(0.25)) {}
public:
  static EnnemyBaseAbstract* makeToPos(PointInSpaceDS p) {return new ShipSinProjSin(p);}};

class ShipZic final :public EnnemyShipAbstract{
    ShipZic(PointInSpaceDS p) :
      ScreenObjAbstract(p, 5, {3,3}),
      EnnemyShipAbstract(100, 10, 50,BasicProj::makeToPos, new ShootingPatternLine() , new MovementPatternZigZac()) {}
  public:
    static EnnemyBaseAbstract* makeToPos(PointInSpaceDS p) {return new ShipZic(p);}};

class ShipShootingTripleShot final : public EnnemyShipAbstract{    ShipShootingTripleShot(PointInSpaceDS p) :
      ScreenObjAbstract(p, 5, {2,2}),
      EnnemyShipAbstract(50, 10, 50,BasicProj::makeToPos, new ShootingPatternTripleShot() , new MovementPatternNull()) {}
  public:
    static EnnemyBaseAbstract* makeToPos(PointInSpaceDS p) {return new ShipShootingTripleShot(p);}};

class ShipSinShootingTripleShot final :public EnnemyShipAbstract{
    ShipSinShootingTripleShot(PointInSpaceDS p) :
      ScreenObjAbstract(p, 6, {3,3}),
      EnnemyShipAbstract(100, 10, 50,BasicProj::makeToPos, new ShootingPatternTripleShot() , new MovementPatternVerticalSinus(0.25)) {}
  public:
    static EnnemyBaseAbstract* makeToPos(PointInSpaceDS p) {return new ShipSinShootingTripleShot(p);}};
class ShipProjSinShootingTripleShot final : public EnnemyShipAbstract{
    ShipProjSinShootingTripleShot(PointInSpaceDS p) :
      ScreenObjAbstract(p, 7, {3,3}),
      EnnemyShipAbstract(100, 10, 50,BasicProj::makeToPos, new ShootingPatternTripleShot() , new MovementPatternVerticalSinus(0.25)) {}
  public:
    static EnnemyBaseAbstract* makeToPos(PointInSpaceDS p) {return new ShipProjSinShootingTripleShot(p);}};
class ShipZicProjSinShootingTripleShot final : public EnnemyShipAbstract{ ShipZicProjSinShootingTripleShot(PointInSpaceDS p) :
  ScreenObjAbstract(p, 7, {3,3}),
  EnnemyShipAbstract(100, 10, 50,ProjSinus::makeToPos, new ShootingPatternTripleShot() , new MovementPatternZigZac()) {}
public:
static EnnemyBaseAbstract* makeToPos(PointInSpaceDS p) {return new ShipZicProjSinShootingTripleShot(p);}};

class ShipZigZacCorrect final :public EnnemyShipAbstract{
    ShipZigZacCorrect(PointInSpaceDS p) :
      ScreenObjAbstract(p, 4, {3,3}),
      EnnemyShipAbstract(100, 10, 50,BasicProj::makeToPos, new ShootingPatternLine() , new MovementPatternZigZacCCorrect()) {}
  public:
    static EnnemyBaseAbstract* makeToPos(PointInSpaceDS p) {return new ShipZigZacCorrect(p);}};

#endif
