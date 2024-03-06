#ifndef _MOVEMENTPATTERNABSTRACT_H_
#define _MOVEMENTPATTERNABSTRACT_H_

class PointInSpaceDS;
class MovementPatternAbstract {
  public:
    virtual void modifyPosition(PointInSpaceDS& p, const float elapsedTime) = 0;
    inline virtual ~MovementPatternAbstract() = 0;
};

MovementPatternAbstract::~MovementPatternAbstract() = default;
#endif
