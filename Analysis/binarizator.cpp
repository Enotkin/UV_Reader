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
    auto [lowHsv, hightHsv] = getHsvRanges();
    cv::cvtColor(src, srcGray, cv::COLOR_BGR2HSV);
    cv::inRange(srcGray, lowHsv, hightHsv, dst);
    return dst;
}

cv::Mat Binarizator::binarizationNormal(const cv::Mat &src)
{
    cv::Mat srcGray, temp, temp2, dst;
    cv::cvtColor(src, srcGray, cv::COLOR_BGR2GRAY);
    cv::threshold(srcGray, dst, thresholdValue, 255, cv::THRESH_BINARY);
    return dst;
}

std::tuple<cv::Scalar, cv::Scalar> Binarizator::getHsvRanges()
{
    auto color = settings.color.toHsv();
    auto coefficients = settings.coefficientHsv;
    auto hueRange = getRange(color.hue(), coefficients.hue);
    auto saturation = getRange(color.saturation(), coefficients.saturation);
    auto value = getRange(color.value(), coefficients.value);
    cv::Scalar lowHsv (hueRange.first, saturation.first, value.first);
    cv::Scalar hightHsv (hueRange.second, saturation.second, saturation.second);
    return std::make_tuple(lowHsv, hightHsv);
}

std::pair<int, int> Binarizator::getRange(int channel, const QPair<int, int> &range)
{
    return std::make_pair(channel - range.first, channel + range.second);
}
