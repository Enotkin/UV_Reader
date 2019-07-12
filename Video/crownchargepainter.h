#ifndef CROWNCHARGEPAINTER_H
#define CROWNCHARGEPAINTER_H

#include "fragmentinfo.h"
#include "frame.h"
#include <QImage>

class CrownChargePainter
{
public:
    CrownChargePainter(const FragmentInfo &fragment);

    Frame getTrackFrame(const Frame &frame);


private:
    FragmentInfo fragment;
    std::vector<cv::Point> track;

    void drawTrack(cv::Mat &imageMat);
};

#endif // CROWNCHARGEPAINTER_H
