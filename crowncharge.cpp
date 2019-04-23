#include "crowncharge.h"

CrownCharge::CrownCharge()
{

}

CrownCharge::CrownCharge(const Contour &starContour) : contours{starContour}
{

}

bool CrownCharge::tryAddContour(const Contour &newContour)
{
    if (contours.empty()){
        contours.push_back(newContour);
        return true;
    }
    auto newContourCenterMass = getCenterMassContour(newContour);
    auto lastContourCenterMass = getCenterMassContour(contours.back());

    if (distanceBetweenTwoPoints(newContourCenterMass, lastContourCenterMass) < 10) {
        countToDie = lifeTime;
        contours.push_back(newContour);
        return true;
    } else {
        countToDie--;
        return false;
    }
}

bool CrownCharge::isTimeToDie() const
{
    return countToDie <= 0 ? true : false;
}

int CrownCharge::getLifeTime() const
{
    return lifeTime;
}

void CrownCharge::setLifeTime(int value)
{
    lifeTime = value;
}

double CrownCharge::getDelta() const
{
    return delta;
}

void CrownCharge::setDelta(double value)
{
    delta = value;
}

cv::Point CrownCharge::getCenterMassContour(const Contour &contour) const
{
    auto moment = cv::moments(contour);
    cv::Point centerMass(static_cast<int>(moment.m10/moment.m00),
                         static_cast<int>(moment.m01/ moment.m00));
    return centerMass;
}

double CrownCharge::distanceBetweenTwoPoints(const cv::Point &first, const cv::Point &second) const
{
    return cv::norm(first - second);
}
