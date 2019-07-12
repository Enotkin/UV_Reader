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

std::vector<Contour> CrownCharge::getContours(int frame)
{
    std::vector<Contour> result;
    std::copy_if(std::begin(contours), std::end(contours), std::back_inserter(result), [frame](const Contour &value){
        return value.getFrameNumber() == frame;
    });
    return result;
}

std::vector<Contour> CrownCharge::getContours()
{
    return std::vector<Contour>{std::begin(contours), std::end(contours)};
}

int CrownCharge::getFirstFrameNumber()
{
    return contours.front().getFrameNumber();
}


