#ifndef _SHOOTINGPATTERNABSTRACT_H_
#define _SHOOTINGPATTERNABSTRACT_H_

#include <list>
#include <memory>

#include "../PointInSpaceDS.hpp"
#include "../Projectils/ProjectilAbstract.hpp"
#include  "../ShapeRectangle.hpp"
#include "../Timer.hpp"

class ShootingPatternAbstract {
    Timer _timer;
  public:
    ShootingPatternAbstract(Timer delay) noexcept : _timer(delay) {}
    /*
    ** This methode defienes the shooting patter. It uses the position and the shape of the calling object to compute the starting point
    ** of the projectil. This starting point is given to the function pointer makeProj.
    ** "givenDir" should use as it is to set the direction  of the projectile if needed (most of the time)
    ** A list of pointer of all intialized projectiles is then returned.
     */
    virtual std::list<std::unique_ptr<ProjectilAbstract>> getBullets(ProjectilAbstract*(*const makeProj)(const PointInSpaceDS&, Dir, float, float),
                                                                     Dir givenDir, const PointInSpaceDS& objPos, const ShapeRectangle& shapeObj) const = 0;
    bool isTimeToShoot() const {return _timer.isOver();}
    void incTimer(const float elapsedTime) {_timer.incTime(elapsedTime);}
    void resetTimer() {_timer.reset();}
};

#endif
