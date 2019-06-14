#include "crownchargedetector.h"

CrownChargeDetector::CrownChargeDetector()
{

}


void CrownChargeDetector::searchCrownCharges(std::list<Contour> &contours)
{
    contours.sort([](const Contour &a, const Contour &b){ return a.getArea() > b.getArea();});
    if (suspectCrownCharges.empty()){
        for(const auto &contour : contours){
            suspectCrownCharges.emplace_back(contour, suspetctSettings);
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
        suspectCrownCharges.sort([](const SuspectCrownCharge &a, const SuspectCrownCharge &b){ return a.getSize() > b.getSize();});
    }
}

void CrownChargeDetector::findCrownCharges(std::list<Contour> &contours)
{
    contours.sort([](const Contour &a, const Contour &b){ return a.getArea() > b.getArea();});
    if (suspectCrownCharges.empty()){
        for(const auto &contour : contours)
            suspectCrownCharges.emplace_back(contour, suspetctSettings);
        return;
    }
    std::list<BrancheSelector> selectors;
    for (auto &contour : contours) {
        selectors.emplace_back(contour);
    }
    for (auto &selector : selectors)
        for (auto &suspectCrownCharge : suspectCrownCharges)
            if(suspectCrownCharge.checkCompatibility(selector.getContour()))
                selector.addBranche(suspectCrownCharge);
    for (auto &selector : selectors) {
        selector.selectionBranch();

    }

    for (auto &suspectCrownCharge : suspectCrownCharges) {
        suspectCrownCharge.endRound();
    }

    suspectCrownCharges.remove_if([](const auto &suspectCrownCharge){
        return suspectCrownCharge.isNoise() || suspectCrownCharge.isConfirmedCharge();
    });

    for (auto &selector : selectors){
        if (!selector.isSelectingEnd())
            suspectCrownCharges.emplace_back(selector.getContour(), suspetctSettings);
    }

     suspectCrownCharges.sort([](const SuspectCrownCharge &a, const SuspectCrownCharge &b){ return a.getSize() > b.getSize();});


}


void CrownChargeDetector::insertContours(const std::list<Contour> &contours)
{
    std::list<Contour> contourWithoutPair;

//    for (const auto &contour : contours) {
//        bool pairFound = false;
//        for (auto &suspectCrownCharge : suspectCrownCharges) {
//            if (suspectCrownCharge.checkCompatibility(contour)){
//                suspectCrownCharge.addContour(contour);
//                pairFound = true;
//            }
//        }
//    }

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
        suspectCrownCharges.emplace_back(contour, suspetctSettings);
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
