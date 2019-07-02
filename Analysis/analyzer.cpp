#include "analyzer.h"

Analyzer::Analyzer(const QFileInfo &sourceFileInfo) :
    sourceFile(sourceFileInfo.absoluteFilePath().toStdString())
{
    videoCapture = std::make_unique<cv::VideoCapture>(sourceFile.string());
}

void Analyzer::analyze()
{
    videoCapture->set(cv::CAP_PROP_POS_AVI_RATIO, 0);
    auto countFrame = videoCapture->get(cv::CAP_PROP_FRAME_COUNT);
    CrownChargeDetector detector(settings);
    for(size_t frameNumber = 0; frameNumber < countFrame; frameNumber++){
        cv::Mat src;
        videoCapture->read(src);
        auto monochromeFrame = binarization(src);
        auto contours = searchContours(frameNumber, monochromeFrame);
        std::list<Contour> contoursList(contours.begin(), contours.end());
        detector.findCrownCharges(contoursList);
    }
    crownCharges = detector.getDetectedCharges();
}

void Analyzer::setMask(QList<QRect> value)
{
    masks = value.toStdList();
}

void Analyzer::setSettings(const SuspectCrownChargeSettings &value)
{
    settings = value;
}

std::list<FragmentInfo> Analyzer::getFragments()
{
    if (crownCharges.empty())
        return std::list<FragmentInfo>();
    std::list<FragmentInfo> fragments;
    for (const auto &crownCharge : crownCharges) {
        FragmentInfo fragmentInfo;
        fragmentInfo.setCrownCharge(crownCharge);
        fragments.push_back(fragmentInfo);
    }
    return fragments;
}

std::vector<Contour> Analyzer::searchContours(size_t frameNumber, const cv::Mat &img)
{
    std::vector<Contour> contours;
    std::vector<std::vector<cv::Point>> srcContours, dstContours;
    cv::findContours(img, srcContours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    std::copy_if(srcContours.begin(), srcContours.end(), std::back_inserter(dstContours),
                 [](const auto &contour){ return (cv::contourArea(contour, false) > 5.0) ? true : false; });
    for (const auto &contour : dstContours) {
        contours.emplace_back(frameNumber, contour);
    }
    return contours;
}

cv::Mat Analyzer::binarization(const cv::Mat &src)
{
    cv::Mat srcGray, dst;
    cv::cvtColor(src, srcGray, cv::COLOR_BGR2GRAY);
    if(!masks.empty())
        applyMask(srcGray);
    cv::threshold(srcGray, dst, thresholdValue, 255, cv::THRESH_BINARY);
    return dst;
}

void Analyzer::applyMask(cv::Mat &src)
{
    for (const auto &rect : masks)
        cv::rectangle(src, cv::Point(rect.topLeft().x(), rect.topLeft().y()),
                      cv::Point(rect.topLeft().x() + rect.width(), rect.topLeft().y() + rect.height()),
                      cv::Scalar(0, 0, 0), cv::FILLED);
}

