#include "suspectcrowncharge.h"

SuspectCrownCharge::SuspectCrownCharge(const Contour &starContour, int lifeTime, double delta, size_t chargeSize)
    : contours{starContour}, realChargeSize(chargeSize), lifeTime(lifeTime), delta(delta)
{

}

bool SuspectCrownCharge::tryAddContour(const Contour &newContour)
{
    if (contours.empty()){
        contours.push_back(newContour);
        return true;
    }
    auto newContourCenterMass = newContour.getCenterMass();
    auto lastContourCenterMass = contours.back().getCenterMass();

    if (distanceBetweenTwoPoints(newContourCenterMass, lastContourCenterMass) < delta) {
        pairFounded = true;
        contours.push_back(newContour);
        return pairFounded;
    } else {
        return false;
    }
}

void SuspectCrownCharge::setSettings(SuspectCrownChargeSettings settings)
{
    lifeTime = settings.lifeTime;
    delta = settings.delta;
    realChargeSize = settings.size;
}

CrownCharge SuspectCrownCharge::getCrownCharge() const
{
    return CrownCharge(contours);
}

bool SuspectCrownCharge::isConfirmedCharge() const
{
    return (contours.size() >= realChargeSize) && (countToDie <= 0);
}

bool SuspectCrownCharge::isNoise() const
{
    return (contours.size() < realChargeSize) && (countToDie <= 0);
}

void SuspectCrownCharge::endRound()
{
    if (pairFounded)
        countToDie = lifeTime;
    else
        countToDie--;
    pairFounded = false;
}

double SuspectCrownCharge::distanceBetweenTwoPoints(const cv::Point &first, const cv::Point &second) const
{
    return cv::norm(first - second);
}
