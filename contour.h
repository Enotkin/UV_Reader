#ifndef CONTOUR_H
#define CONTOUR_H

#include <QPoint>

#include "opencv2/video.hpp"
#include "opencv2/highgui.hpp"

class Contour
{
public:
    Contour(int frameNumber, const std::vector<cv::Point> &contour);

    std::vector<cv::Point> getContour() const;

    double getArea() const;

    QPoint getQPointCenterMass() const;

    cv::Point getCenterMass() const;

    int getFrameNumber() const;

private:
    std::vector<cv::Point> contour;
    cv::Moments moments;
    double contourArea;
    size_t frameNumber;
};

#endif // CONTOUR_H
