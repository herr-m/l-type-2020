#ifndef _BASICPROJ_H_
#define _BASICPROJ_H_

#include "ProjectilAbstract.hpp"
#include "../MovementPatterns/AllMovementPattern.hpp"

class BasicProj final : public ProjectilAbstract {
    BasicProj(PointInSpaceDS p, Dir dir, float vY, float vX) noexcept :
        ScreenObjAbstract(p, 3, {2, 2}), ProjectilAbstract(new MovementPatternNull(), 50, dir, vY, vX, 70.f) {};
  public:
    static ProjectilAbstract* makeToPos(const PointInSpaceDS& p, Dir dir, float vY, float vX) {return new BasicProj(p, dir, vY, vX);}
};

class ProjSinus final : public ProjectilAbstract{
    ProjSinus(PointInSpaceDS p, Dir dir, float vY, float vX) noexcept :
        ScreenObjAbstract(p, 3, {2, 2}), ProjectilAbstract(new MovementPatternVerticalSinus(5), 50, dir, vY, vX, 50.f) {};
  public:
    static ProjectilAbstract* makeToPos(const PointInSpaceDS& p, Dir dir, float vY, float vX) {return new ProjSinus(p, dir, vY, vX);}
};

class ProjBasic2 final : public ProjectilAbstract {
  ProjBasic2(PointInSpaceDS p, Dir dir, float vY, float vX) noexcept :
      ScreenObjAbstract(p, 3, {2, 2}), ProjectilAbstract(new MovementPatternEnemy1(), 50, dir ,vY,vX, 60.f) {};
public:
  static ProjectilAbstract* makeToPos(const PointInSpaceDS& p, Dir dir, float vY, float vX) {return new ProjBasic2(p,dir ,vY,vX);}};

class ProjBasic3 final : public ProjectilAbstract {
  ProjBasic3(PointInSpaceDS p, Dir dir, float vY, float vX) noexcept :
    ScreenObjAbstract(p, 3, {3, 1}), ProjectilAbstract(new MovementPatternEnemy3(), 250,dir,vY,vX, 30.f) {};
public:
static ProjectilAbstract* makeToPos(const PointInSpaceDS& p, Dir dir, float vY, float vX) {return new ProjBasic3(p,dir ,vY,vX);}};


class ProjSinus2 final : public ProjectilAbstract {
  ProjSinus2(PointInSpaceDS p, Dir dir, float vY, float vX) noexcept :
    ScreenObjAbstract(p, 3, {2, 2}), ProjectilAbstract(new MovementPatternVerticalSinus(1.5), 30,dir,vY,vX, 120.f) {};
public:
static ProjectilAbstract* makeToPos(const PointInSpaceDS& p, Dir dir, float vY, float vX) {return new ProjSinus2(p,dir,vY,vX);}};

class ProjBasic5 final : public ProjectilAbstract {
  ProjBasic5(PointInSpaceDS p , Dir dir, float vY, float vX) noexcept :
ScreenObjAbstract(p, 3, {2, 2}), ProjectilAbstract(new MovementPatternEnemy4, 80,dir,vY,vX, 80.f) {};
public:
static ProjectilAbstract* makeToPos(const PointInSpaceDS& p, Dir dir, float vY, float vX) {return new ProjBasic5(p,dir,vY,vX);}};

class ProjBasic6 final : public ProjectilAbstract {
  ProjBasic6(PointInSpaceDS p, Dir dir, float vY, float vX ) noexcept :
ScreenObjAbstract(p, 3, {2, 2}), ProjectilAbstract(new MovementPatternEnemy5, 90,dir,vY,vX, 90.f) {};
public:
static ProjectilAbstract* makeToPos(const PointInSpaceDS& p, Dir dir, float vY, float vX) {return new ProjBasic6(p,dir,vY,vX);}};

class ProjZic final : public ProjectilAbstract {
  ProjZic(PointInSpaceDS p ,Dir dir , float vY, float vX ) noexcept :
  ScreenObjAbstract(p, 3, {2, 2}), ProjectilAbstract(new MovementPatternZigZac, 90,dir,vY,vX, 90.f) {};
public:
static ProjectilAbstract* makeToPos(const PointInSpaceDS& p, Dir dir, float vY, float vX) {return new ProjZic(p,dir,vY,vX);}};




#endif
