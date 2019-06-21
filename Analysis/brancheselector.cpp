#include "brancheselector.h"
#include <QtDebug>

BrancheSelector::BrancheSelector(const Contour &contour) : contour(contour)
{
}

void BrancheSelector::addBranche(BrancheRef newBranche)
{
    branches.push_back(newBranche);
}

void BrancheSelector::selectionBranch()
{
    brancheSort();
    for (auto &branche : branches) {
        if(!branche.get().isPairFound()){
            branche.get().addContour(contour);
            selectingEnd = true;
            break;
        }
    }
}

void BrancheSelector::brancheSort()
{
    auto cmpBrancheArea = [](const BrancheRef &l, const BrancheRef &r){
        return l.get().getAverageArea() > r.get().getAverageArea();};

    if (auto [min, max] = std::minmax_element(branches.begin(), branches.end(), branchesCmp(std::less<int>{})) ; min == max){
        branches.sort(cmpBrancheArea);
    } else {
        branches.sort(branchesCmp(std::greater<int>{}));
    }
}

bool BrancheSelector::isSelectingEnd() const
{
    return selectingEnd;
}

std::list<BrancheRef> BrancheSelector::getBranches() const
{
    return branches;
}

Contour BrancheSelector::getContour() const
{
    return contour;
}
