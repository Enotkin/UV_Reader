#ifndef SUSPECTCROWNCHARGE_H
#define SUSPECTCROWNCHARGE_H
#include <vector>
#include <list>
#include <numeric>

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
    SuspectCrownCharge (const Contour &startContour, const SuspectCrownChargeSettings &settings);
    bool tryAddContour(const Contour &newContour);

    bool checkCompatibility(const Contour& newContour) const;
    void addContour(const Contour &newContour);

    CrownCharge getCrownCharge() const;
    int getSize() const;
    double getAverageArea() const;
    bool isConfirmedCharge() const ;
    bool isNoise() const;

    void endRound();


    friend bool operator<(const SuspectCrownCharge& l, const SuspectCrownCharge& r){
        return l.getSize() < r.getSize();
    }
    bool isPairFound() const;

    cv::Point getLastPoint() const;

private:
    std::list<Contour> contours;
    std::vector<Contour> tempContours;
    size_t realChargeSize = 2;
    int lifeTime = 5;
    double delta = 10;
    int countToDie = lifeTime;
    double distanceBetweenPoints(const cv::Point &first, const cv::Point &second) const;
    bool pairFound = false;
    cv::Point lastPoint;

};

#endif // SUSPECTCROWNCHARGE_H
