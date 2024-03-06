#ifndef _SCROLLOBJABSTRACT_H_
#define _SCROLLOBJABSTRACT_H_

#include "ScreenObjAbstract.hpp"


class ScrollObjAbstract : virtual public ScreenObjAbstract  {
    constexpr const static double _scrollSpeed = 5.f;
  public:
    void updatePos(const float elapsedTime) override {_pos.y += _scrollSpeed*elapsedTime;}
    inline virtual ~ScrollObjAbstract() noexcept = 0;
};
ScrollObjAbstract::~ScrollObjAbstract() noexcept = default;

#endif
