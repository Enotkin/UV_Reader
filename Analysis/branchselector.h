#ifndef BRANCHESELECTOR_H
#define BRANCHESELECTOR_H
#include <functional>

#include "contour.h"
#include "branch.h"

using BrancheRef = std::reference_wrapper<Branch>;

class BranchSelector
{
public:
    BranchSelector(const Contour &contour);
    void addBranche(BrancheRef newBranche);
    void selectionBranch();
    Contour getContour() const;

    bool isSelectingEnd() const;

    std::list<BrancheRef> getBranches() const;

private:
    Contour contour;
    std::list<BrancheRef> branches;
    void branchSort();
    bool selectingEnd = false;
    template<class Comparator>
    constexpr auto branchesCmp(Comparator cmp){
        return [cmp](const BrancheRef &l, const BrancheRef &r){
            return cmp(l.get().length(), r.get().length());
        };
    }

};

#endif // BRANCHESELECTOR_H
