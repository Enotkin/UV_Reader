#ifndef CROWNCHARGEDETECTOR_H
#define CROWNCHARGEDETECTOR_H

#include "contour.h"
#include <set>
#include <algorithm>
#include "branch.h"
#include "crowncharge.h"
#include "branchselector.h"


class CrownChargeDetector
{
public:
    CrownChargeDetector();
    CrownChargeDetector(const BranchSettings &settings);
    ~CrownChargeDetector();

    void findCrownCharges(std::list<Contour> &contours);
    std::list<CrownCharge> getDetectedCharges() const;
    void setSettings(BranchSettings settings);
    
    std::list<CrownCharge> getLastDetectedCharges() const;

private:
    std::list<CrownCharge> lastDetectedCharges;
    std::list<CrownCharge> detectedCharges;
    std::list<Branch> branches;
    BranchSettings suspetctSettings;

    std::list<BranchSelector> createSelectors(const std::list<Contour> &contours);
    void branchDistribution(std::list<BranchSelector> &selectorList, std::list<Branch> &branchList);
    void copyConfirmedCharges(const std::list<Branch> &branches);

    bool isConfirmed(const Branch &branch);

};

#endif // CROWNCHARGEDETECTOR_H
