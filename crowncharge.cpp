#include "crowncharge.h"

CrownCharge::CrownCharge()
{

}

CrownCharge::CrownCharge(const std::list<Contour> &contours) : contours(contours)
{

}

bool CrownCharge::isEmpty()
{
    return contours.empty();
}

QPair<int, int> CrownCharge::getRange()
{
    return QPair<int, int>(contours.front().getFrameNumber(),
                           contours.back().getFrameNumber());
}


