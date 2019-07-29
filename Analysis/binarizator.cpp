#include "binarizator.h"

Binarizator::Binarizator(FilterSettings settings) : settings(settings) {}

cv::Mat Binarizator::getImage(const cv::Mat &src)
{
    switch (settings.mode) {
    case FilterType::Normal:
        return binarizationNormal(src);
    case FilterType::Colorfull:
        return binarizationColor(src);
    }
}

cv::Mat Binarizator::binarizationColor(const cv::Mat &src)
{
    cv::Mat dst, srcGray;
    auto color = settings.color.toHsv();
    cv::cvtColor(src, srcGray, cv::COLOR_BGR2HSV);
    cv::inRange(srcGray, cv::Scalar(color.hue(), color.saturation(), color.value()),
                cv::Scalar(color.hue(), color.saturation(), color.value()), dst);
    return dst;
}

cv::Mat Binarizator::binarizationNormal(const cv::Mat &src)
{
    cv::Mat srcGray, temp, temp2, dst;
    cv::cvtColor(src, srcGray, cv::COLOR_BGR2GRAY);
    cv::threshold(srcGray, dst, thresholdValue, 255, cv::THRESH_BINARY);
    return dst;
}
