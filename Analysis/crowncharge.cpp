#include "crowncharge.h"

CrownCharge::CrownCharge()
{

}

CrownCharge::CrownCharge(const std::list<Contour> &contours) : contours(contours)
{

}

bool CrownCharge::isEmpty() const
{
    return contours.empty();
}

QPair<int, int> CrownCharge::getRange() const
{
    return QPair<int, int>(contours.front().getFrameNumber(),
                           contours.back().getFrameNumber());
}

std::vector<Contour> CrownCharge::getContours(int frame) const
{
    std::vector<Contour> result;
    std::copy_if(std::begin(contours), std::end(contours), std::back_inserter(result), [frame](const Contour &value){
        return value.getFrameNumber() == frame;
    });
    return result;
}

std::vector<Contour> CrownCharge::getContours() const
{
    return std::vector<Contour>{std::begin(contours), std::end(contours)};
}

int CrownCharge::getFirstFrameNumber()
{
    return contours.front().getFrameNumber();
}


