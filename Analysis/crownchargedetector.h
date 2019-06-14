#ifndef CROWNCHARGEDETECTOR_H
#define CROWNCHARGEDETECTOR_H

#include "contour.h"
#include <set>
#include <algorithm>
#include "suspectcrowncharge.h"
#include "crowncharge.h"
#include "brancheselector.h"

class CrownChargeDetector
{
public:
    CrownChargeDetector();

    void searchCrownCharges(std::list<Contour> &contours);
    void findCrownCharges(std::list<Contour> &contours);

    void clearBuffer();

    std::list<CrownCharge> getDetectedCharges() const;
    void setSettings(SuspectCrownChargeSettings settings);
    
private:
    std::list<CrownCharge> detectedCharges;

    std::list<SuspectCrownCharge> suspectCrownCharges;

//    std::set<Co

    SuspectCrownChargeSettings suspetctSettings;
    
    void insertContours(const std::list<Contour> &contours);
    void nextRound();
};

#endif // CROWNCHARGEDETECTOR_H
