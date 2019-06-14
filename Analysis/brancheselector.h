#ifndef BRANCHESELECTOR_H
#define BRANCHESELECTOR_H
#include <functional>

#include "contour.h"
#include "suspectcrowncharge.h"

using BrancheRef = std::reference_wrapper<SuspectCrownCharge>;

class BrancheSelector
{
public:
    BrancheSelector(const Contour &contour);
    void addBranche(BrancheRef newBranche);
    void selectionBranch();
    Contour getContour() const;

    bool isSelectingEnd() const;

private:
    Contour contour;
    std::list<BrancheRef> branches;
    void brancheSort();
    bool selectingEnd = false;
    template<class Comparator>
    constexpr auto branchesCmp(Comparator cmp){
        return [cmp](const BrancheRef &l, const BrancheRef &r){
            return cmp(l.get().getSize(), r.get().getSize());
        };
    }

};

#endif // BRANCHESELECTOR_H
