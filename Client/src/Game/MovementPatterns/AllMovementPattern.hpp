#ifndef _ENNEMYMOVEMNTPATTER_H_
#define _ENNEMYMOVEMNTPATTER_H_

#include "MovementPatternAbstract.hpp"
#include "../PointInSpaceDS.hpp"

#include <math.h>

class MovementPatternEnemyAbstract : public MovementPatternAbstract {};


class MovementPatternEnemy1 final: public MovementPatternEnemyAbstract{
    public:
    void modifyPosition(PointInSpaceDS& p, const float elapsedTime) override {
        // engendre un déplacement maximal de 10 vers la droite sur l'axe des x pour 1 vers le bas sur l'axe y
        // on peut reproduire le même patterne avec p.x -= au lieu de += pour changer le sens du déplacement (patterne 2)
        // si x = y = 0 au départ, on atteint x = 52 en y = 100
        p.x += 20.f * elapsedTime;
        }
};

class MovementPatternEnemy2 final : public MovementPatternEnemyAbstract{
    public:
    void modifyPosition(PointInSpaceDS& p, const float elapsedTime) override {
        // engendre un déplacement maximal de 10 vers la droite sur l'axe des x pour 1 vers le bas sur l'axe y
        // on peut reproduire le même patterne avec p.x -= au lieu de += pour changer le sens du déplacement (patterne 2)
        // si x = y = 0 au départ, on atteint x = 52 en y = 100
        p.x -= 20.f * elapsedTime;
    }
};

class MovementPatternEnemy3 final : public MovementPatternEnemyAbstract
{
    public:
    void modifyPosition(PointInSpaceDS& p, const float elapsedTime) override {
        p.x = p.y * elapsedTime * 100.f;

    }
};

class MovementPatternEnemy4 final : public MovementPatternEnemyAbstract
{
    public:
    void modifyPosition(PointInSpaceDS& p, const float elapsedTime) override {p.x += 20.f * elapsedTime;}
};

class MovementPatternEnemy5 final : public MovementPatternEnemyAbstract
{
    public:
    void modifyPosition(PointInSpaceDS& p, const float elapsedTime) override {p.x -= 20.f * elapsedTime;}
};


class MovementPatternZigZac  final : public MovementPatternEnemyAbstract{
public:
  void modifyPosition(PointInSpaceDS& p, const float elapsedTime) override {
    if (p.y<=13 && p.x<=75 ){
      p.x+=20.f * elapsedTime;
    }
    else {p.x-=20.f * elapsedTime;}
}};

class MovementPatternZigZacCCorrect  final : public MovementPatternEnemyAbstract{
public:
  void modifyPosition(PointInSpaceDS& p, const float elapsedTime) override {
    static_cast<int>(p.y) % 20 < 10 ? p.x+= 20.f * elapsedTime : p.x-= 20.f * elapsedTime;
}};

class MovementPatternNull final : public MovementPatternEnemyAbstract
{
    // on accepte le warning pour param non utilisés, ce patterne sert juste à avoir un patterne qui ne fait rien.
    void modifyPosition(PointInSpaceDS& p, const float elapsedTime) override {}
};

class MovementPatternVerticalSinus final : public MovementPatternEnemyAbstract{
    const double _amp;
  public:
    MovementPatternVerticalSinus(double amp) : MovementPatternEnemyAbstract(), _amp(amp) {}
        void modifyPosition(PointInSpaceDS& p, const float elapsedTime) override {p.x += _amp*sin(_amp*p.y*10) * elapsedTime;}
};

class MovementPatternLatteralMove : public MovementPatternEnemyAbstract {
    constexpr static const float _speed = 10;
    constexpr static const float _screenWidthMax = 100;
    constexpr static const float _screenWidthMin = 0;
    bool _isGoingRight = true;
    static void _moveRight(PointInSpaceDS& p, const float elapsedTime) {p.x+=_speed*elapsedTime;}
    static void _moveLeft(PointInSpaceDS& p, const float elapsedTime) {p.x-=_speed*elapsedTime;}
  public:
    void modifyPosition(PointInSpaceDS& p, const float elapsedTime) override {
        if(_isGoingRight) {_moveRight(p, elapsedTime); if(p.x>=_screenWidthMax) _isGoingRight=false;}
        else{_moveLeft(p, elapsedTime); if(p.x<=_screenWidthMin) _isGoingRight=true;}
    }
};

class MovementPatternLatteralSinus final : public MovementPatternLatteralMove {
    const double _amp;
    const double _yPos;
  public:
    MovementPatternLatteralSinus(double amp, double yPos) : MovementPatternLatteralMove(), _amp(amp), _yPos(yPos) {}
    void modifyPosition(PointInSpaceDS& p, const float elapsedTime) override
        {MovementPatternLatteralMove::modifyPosition(p, elapsedTime);}
};

#endif
