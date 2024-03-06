#ifndef _SCREENOBJABSTRACT_H_
#define _SCREENOBJABSTRACT_H_

#include "../ShapeRectangle.hpp"
#include "../PointInSpaceDS.hpp"
#include "../ScreenObjSerialDS.hpp"

/*
** All instensiable object deceding from ScreenObjAbstract shoudl
** define a static methode acting as a pseudo ctor.
 */
class ScreenObjAbstract {
  protected:
    const unsigned _spriteID;
    PointInSpaceDS _pos; // center position
    const  ShapeRectangle _shape;
    ScreenObjAbstract() noexcept = default; // warning ok never called because only virtual base and abstract (syntactically necessary)
    constexpr ScreenObjAbstract(PointInSpaceDS p, unsigned spriteID, ShapeRectangle shape) noexcept :
        _pos(p), _spriteID(spriteID), _shape(shape) {}
  public:
    bool collideWith(const ScreenObjAbstract& other) const
        {return ShapeRectangle::collide(_pos, _shape, other._pos, other._shape);}
    virtual void updatePos(const float) = 0;
    virtual ~ScreenObjAbstract() noexcept = default;
    auto getSerialize() const {return ScreenObjSerialDS{_pos.x, _pos.y, _spriteID};} // return top corner left
    PointInSpaceDS getPos() const {return _pos;}
};

#endif
