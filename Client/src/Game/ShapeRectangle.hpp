#ifndef _SHAPERECTANGLE_H_
#define _SHAPERECTANGLE_H_

#include "PointInSpaceDS.hpp"

class ShapeRectangle final {
   const double _height, _width;
  public:
    double getMinX(const double CenterX) const {return CenterX - _width/2;}
    double getMaxX(const double CenterX) const {return CenterX + _width/2;}
    double getMaxY(const double CenterY) const {return CenterY + _height/2;}
    double getMinY(const double CenterY) const {return CenterY - _height/2;}

    constexpr ShapeRectangle(double h, double w) noexcept : _height(h), _width(w) {}

    static bool collide(const PointInSpaceDS& pos1, const ShapeRectangle& rect1, const PointInSpaceDS& pos2, const ShapeRectangle& rect2)
        {return rect1.getMinX(pos1.x) <= rect2.getMaxX(pos2.x) && rect1.getMaxX(pos1.x) >= rect2.getMinX(pos2.x) &&
                rect1.getMinY(pos1.y) <= rect2.getMaxY(pos2.y) && rect1.getMaxY(pos1.y) >= rect2.getMinY(pos2.y);}
};

#endif
