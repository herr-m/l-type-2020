#ifndef _DAMMAGEOBJABSTRACT_H_
#define _DAMMAGEOBJABSTRACT_H_

#include "ScreenObjAbstract.hpp"

class HealthObjAbstract;

class DammageObjAbstract : virtual public ScreenObjAbstract {
    friend HealthObjAbstract;
    const unsigned _dammage;
  public:
    explicit DammageObjAbstract(unsigned d) noexcept : _dammage(d) {}
    virtual ~DammageObjAbstract() = default;

};

#endif
