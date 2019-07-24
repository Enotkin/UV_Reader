#ifndef CROWNCHARGE_H
#define CROWNCHARGE_H
#include <vector>
#include <list>

#include <QPair>

#include "contour.h"
#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"


class CrownCharge
{
public:
    CrownCharge();
    CrownCharge(const std::list<Contour> &contours);
    bool isEmpty() const;
    QPair<int, int> getRange() const;
    std::vector<Contour> getContours(int number) const;
    std::vector<Contour> getContours() const;
    int getFirstFrameNumber();

    //TODO ХОЧУ ЧТОБЫ ДИАПАЗОН БЫЛ ИТЕРАБЕЛЬНЫМ
    
private:
    std::list<Contour> contours;
};

#endif // CROWNCHARGE_H
