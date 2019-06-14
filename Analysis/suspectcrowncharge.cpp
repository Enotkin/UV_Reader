#include "suspectcrowncharge.h"

SuspectCrownCharge::SuspectCrownCharge(const Contour &starContour, int lifeTime, double delta, size_t chargeSize)
    : contours{starContour}, realChargeSize(chargeSize), lifeTime(lifeTime), delta(delta) {}

SuspectCrownCharge::SuspectCrownCharge(const Contour &startContour, const SuspectCrownChargeSettings &settings)
    : contours{startContour}, realChargeSize(settings.size), lifeTime(settings.lifeTime), delta(settings.delta) {}

bool SuspectCrownCharge::tryAddContour(const Contour &newContour)
{
    if (checkCompatibility(newContour)) {
        pairFounded = true;
        contours.push_back(newContour);
        return pairFounded;
    } else {
        return false;
    }
}

bool SuspectCrownCharge::checkCompatibility(const Contour &newContour) const
{
    return distanceBetweenPoints(newContour.getCenterMass(), contours.back().getCenterMass()) < delta ? true : false;
}

void SuspectCrownCharge::addContour(const Contour &newContour)
{
    contours.push_back(newContour);
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

int SuspectCrownCharge::getSize() const
{
    return contours.size();
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
    if (!tempContours.empty()){
        auto maxContour = *std::max_element(std::begin(tempContours), std::end(tempContours), [](const auto &first, const auto &second){
                             return first.getArea() < second.getArea();});
        contours.push_back(maxContour);
        countToDie = lifeTime;
    } else {
       countToDie--;
    }
    tempContours.clear();
}

double SuspectCrownCharge::distanceBetweenPoints(const cv::Point &first, const cv::Point &second) const
{
    return cv::norm(first - second);
}
