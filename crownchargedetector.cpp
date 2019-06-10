#include "crownchargedetector.h"

CrownChargeDetector::CrownChargeDetector()
{

}


void CrownChargeDetector::searchCrownCharges(const std::list<Contour> &contours)
{
    if (suspectCrownCharges.empty()){
        for(const auto &contour : contours){
            suspectCrownCharges.emplace_back(contour);
            suspectCrownCharges.back().setSettings(suspetctSettings);
        }
    } else {
        insertContours(contours);
        for (const auto &suspectCrownCharge : suspectCrownCharges) {
            if (suspectCrownCharge.isConfirmedCharge())
                detectedCharges.push_back(suspectCrownCharge.getCrownCharge());
        }
        suspectCrownCharges.remove_if([](const auto &suspectCrownCharge){
            return suspectCrownCharge.isNoise() || suspectCrownCharge.isConfirmedCharge();
        });
    }
}


void CrownChargeDetector::insertContours(const std::list<Contour> &contours)
{
    std::list<Contour> contourWithoutPair;
    for (auto const &contour : contours) {
        bool pairFound = false;
        for (auto &suspectCrownCharge : suspectCrownCharges)
            pairFound |= suspectCrownCharge.tryAddContour(contour);
        if (!pairFound){
            contourWithoutPair.push_back(contour);
        }
    }

    for (auto &suspectCrownCharge : suspectCrownCharges) {
        suspectCrownCharge.endRound();
    }

    for (const auto &contour : contourWithoutPair){
        suspectCrownCharges.emplace_back(contour);
        suspectCrownCharges.back().setSettings(suspetctSettings);
    }
}

void CrownChargeDetector::nextRound()
{
//    for (auto &suspectCrownCharge : suspectCrownCharges) {
//        suspectCrownCharge.endRound();
//    }
}

void CrownChargeDetector::clearBuffer()
{
    if (!suspectCrownCharges.empty()){
        suspectCrownCharges.clear();
    }
}

std::list<CrownCharge> CrownChargeDetector::getDetectedCharges() const
{
    return detectedCharges;
}

void CrownChargeDetector::setSettings(SuspectCrownChargeSettings settings)
{
    suspetctSettings = settings;
}
