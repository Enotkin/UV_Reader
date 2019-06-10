#ifndef CROWNCHARGEPAINTER_H
#define CROWNCHARGEPAINTER_H

#include "fragmentinfo.h"
#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"
#include <QImage>

class CrownChargePainter
{
public:
    CrownChargePainter(const FragmentInfo &fragment);

    QImage getImage(cv::Mat imageMat, int number);


private:
    FragmentInfo fragment;
    std::vector<cv::Point> track;

    void drawTrack(cv::Mat &imageMat);
};

#endif // CROWNCHARGEPAINTER_H
