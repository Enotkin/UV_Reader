#include "analyzer.h"
#include "QDebug"
Analyzer::Analyzer(const QFileInfo &sourceFileInfo) :
    sourceFile(sourceFileInfo.absoluteFilePath().toStdString())
{
    videoFileReader = std::make_unique<VideoFileReader>(sourceFileInfo);
}

void Analyzer::analyze()
{
    auto countFrame = videoFileReader->getSettings().getCountFrames();
    CrownChargeDetector detector(settings);
    for(int frameNumber = 0; frameNumber < countFrame; frameNumber++){
        cv::Mat src = videoFileReader->getCvImage(frameNumber);
        auto monochromeFrame = binarization(src);
        auto maskedFrame = applyMask(monochromeFrame);
        auto contours = searchContours(frameNumber, maskedFrame);
        detector.findCrownCharges(contours);
    }
    crownCharges = detector.getDetectedCharges();
    crownCharges.sort([](CrownCharge &first, CrownCharge &second){return first.getFirstFrameNumber() < second.getFirstFrameNumber();});
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

std::list<Contour> Analyzer::searchContours(int frameNumber, const cv::Mat &img)
{
    std::list<Contour> contours;
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
    cv::Mat srcGray, temp, temp2, dst;
    cv::cvtColor(src, srcGray, cv::COLOR_BGR2GRAY);
    cv::threshold(srcGray, dst, thresholdValue, 255, cv::THRESH_BINARY);
    return dst;
}

cv::Mat Analyzer::applyMask(const cv::Mat &src)
{
    cv::Mat dst = src;
    for (const auto &rect : masks)
        cv::rectangle(dst, cv::Point(rect.topLeft().x(), rect.topLeft().y()),
                      cv::Point(rect.topLeft().x() + rect.width(), rect.topLeft().y() + rect.height()),
                      cv::Scalar(0, 0, 0), cv::FILLED);
    return dst;
}

