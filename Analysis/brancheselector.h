#ifndef BRANCHESELECTOR_H
#define BRANCHESELECTOR_H
#include <functional>

#include "contour.h"
#include "suspectcrowncharge.h"


class BrancheSelector
{
public:
    BrancheSelector(const Contour &contour);
    void addBranche(std::reference_wrapper<SuspectCrownCharge> newBranche);


private:
    Contour contour;
    std::vector<std::reference_wrapper<SuspectCrownCharge>> branches;
};

#endif // BRANCHESELECTOR_H
