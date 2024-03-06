#ifndef _POINTINSPACE_H_
#define _POINTINSPACE_H_

struct PointInSpaceDS final {
    double x, y;
    constexpr PointInSpaceDS(double x, double y) noexcept : x(x), y(y) {}
};

#endif
