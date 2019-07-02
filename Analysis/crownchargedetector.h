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
    CrownChargeDetector(const SuspectCrownChargeSettings &settings);
    ~CrownChargeDetector();

    void findCrownCharges(std::list<Contour> &contours);
    std::list<CrownCharge> getDetectedCharges() const;
    void setSettings(SuspectCrownChargeSettings settings);
    
private:
    std::list<CrownCharge> detectedCharges;
    std::list<SuspectCrownCharge> suspectCrownCharges;
    SuspectCrownChargeSettings suspetctSettings;
};

#endif // CROWNCHARGEDETECTOR_H
