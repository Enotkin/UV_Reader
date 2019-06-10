#ifndef SUSPECTCROWNCHARGE_H
#define SUSPECTCROWNCHARGE_H
#include <vector>
#include <list>

#include "contour.h"
#include "crowncharge.h"
#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"

namespace SuspectCrownChargeDefaultParameters {
    static int DefaultLifeTime = 5;
    static double DefaultDelta = 75;
    static size_t DefaultChargeSize = 3;
}

struct SuspectCrownChargeSettings{
    int size;
    int lifeTime;
    double delta;
};

class SuspectCrownCharge
{
public:
    SuspectCrownCharge(const Contour &starContour,
                       int lifeTime = SuspectCrownChargeDefaultParameters::DefaultLifeTime,
                       double delta = SuspectCrownChargeDefaultParameters::DefaultDelta,
                       size_t chargeSize = SuspectCrownChargeDefaultParameters::DefaultChargeSize);
    bool tryAddContour(const Contour &newContour);
    void setSettings(SuspectCrownChargeSettings settings);
    CrownCharge getCrownCharge() const;
    bool isConfirmedCharge() const ;
    bool isNoise() const;

private:
    std::list<Contour> contours;
    size_t realChargeSize = 2;
    int lifeTime = 5;
    double delta = 75;
    int countToDie = lifeTime;
    double distanceBetweenTwoPoints(const cv::Point &first, const cv::Point &second) const;
};

#endif // SUSPECTCROWNCHARGE_H
