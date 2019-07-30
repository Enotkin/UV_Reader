#ifndef BINARIZATOR_H
#define BINARIZATOR_H

#include "filtersettings.h"
#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"

class Binarizator
{
public:
    Binarizator(FilterSettings settings);

    cv::Mat getImage(const cv::Mat &src);

private:
    FilterSettings settings;
    double thresholdValue = 225;

    cv::Mat binarizationColor(const cv::Mat &src);
    cv::Mat binarizationNormal(const cv::Mat &src);

    std::tuple<cv::Scalar, cv::Scalar> getHsvRanges();
    std::pair<int, int> getRange(int channel, const QPair<int, int> &range);
};

#endif // BINARIZATOR_H
