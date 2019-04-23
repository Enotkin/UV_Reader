#ifndef CROWNCHARGE_H
#define CROWNCHARGE_H
#include <vector>
#include <list>

#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"

using Contour = std::vector<cv::Point>;

class CrownCharge
{
public:
    CrownCharge();
    CrownCharge(const Contour &starContour);
    bool tryAddContour(const Contour &newContour);
    bool isTimeToDie() const;

    int getLifeTime() const;
    void setLifeTime(int value);

    double getDelta() const;
    void setDelta(double value);

private:
    std::list<Contour> contours;
    int lifeTime = 5;
    double delta = 25.0;
    int countToDie = lifeTime;
    cv::Point getCenterMassContour(const Contour &contour) const;
    double distanceBetweenTwoPoints(const cv::Point &first, const cv::Point &second) const;
};

#endif // CROWNCHARGE_H
