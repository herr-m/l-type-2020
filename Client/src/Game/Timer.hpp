#ifndef _TIMER_H_
#define _TIMER_H_

#include <cstddef> // std::size_t

class Timer final {
    static constexpr const double _dt=1;
    const double _timerLimit;
    double _time{};
  public:
    constexpr Timer(std::size_t duration) noexcept : _timerLimit(duration) {}
    void incTime(const float elapsedTime) {_time+=_dt*elapsedTime;}
    void reset() {_time=0;}
    bool isOver() const {return _time >= _timerLimit;}
};

#endif
