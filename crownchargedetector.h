#ifndef CROWNCHARGEDETECTOR_H
#define CROWNCHARGEDETECTOR_H

#include "contour.h"
#include <set>
#include "suspectcrowncharge.h"
#include "crowncharge.h"

class CrownChargeDetector
{
public:
    CrownChargeDetector();

    void searchCrownCharges(const std::list<Contour> &contours);

    void clearBuffer();

    std::list<CrownCharge> getDetectedCharges() const;
    void setSettings(SuspectCrownChargeSettings settings);
    
private:
    std::list<CrownCharge> detectedCharges;

    std::list<SuspectCrownCharge> suspectCrownCharges;

    std::set<SuspectCrownCharge> setSuspectCrownCharges;
//    std::set<Co

    SuspectCrownChargeSettings suspetctSettings;
    
    void insertContours(const std::list<Contour> &contours);
    void nextRound();
};

#endif // CROWNCHARGEDETECTOR_H
