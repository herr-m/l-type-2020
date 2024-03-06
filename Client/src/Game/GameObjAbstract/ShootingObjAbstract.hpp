#ifndef _SHOOTINGOBJABSTRACT_H_
#define _SHOOTINGOBJABSTRACT_H_

#include "ScreenObjAbstract.hpp"
#include "../Projectils/ProjectilAbstract.hpp"
#include "../ShootingPatterns/ShootingPatternAbstract.hpp"
#include <list>
#include <memory>


class ShootingObjAbstract : virtual public ScreenObjAbstract {
    const Dir _dir;
  protected:
    ProjectilAbstract*(*_makeProj)(const PointInSpaceDS&, Dir, float, float);
    std::unique_ptr<ShootingPatternAbstract>  _sPat;

    ShootingObjAbstract(Dir dir, ProjectilAbstract*(*f)(const PointInSpaceDS&, Dir, float, float), ShootingPatternAbstract* sPat) noexcept :
      _dir(dir), _makeProj(f), _sPat(sPat) {}
  public:
    // Use the shooting pattern to compute a list of projectile (make proj)
    void shootOnContainer(std::list<std::unique_ptr<ProjectilAbstract>>& lProj) const
      {if(_sPat->isTimeToShoot()){lProj.merge(_sPat->getBullets(_makeProj, _dir, _pos, _shape)); _sPat->resetTimer();}}
    void incShootingTimer(const float elapsedTime) {_sPat->incTimer(elapsedTime);}
    virtual ~ShootingObjAbstract() = default;
};

#endif
