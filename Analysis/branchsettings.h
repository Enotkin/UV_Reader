#ifndef BRANCHSETTINGS_H
#define BRANCHSETTINGS_H

struct BranchSettings{
    BranchSettings() : size(3), lifeTime(5), delta(75) {}
    BranchSettings(int size, int lifeTime, double delta) :
        size(size), lifeTime(lifeTime), delta(delta) {}

    int size;
    int lifeTime;
    double delta;
};

#endif // BRANCHSETTINGS_H
