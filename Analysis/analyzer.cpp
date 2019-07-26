#include "analyzer.h"
#include "QDebug"
Analyzer::Analyzer(const QFileInfo &sourceFileInfo) :
    videoFileReader(sourceFileInfo)
{
    masks = SettingKeeper::getInstance()->loadMask();
}

Analyzer::~Analyzer()
{
    this->disconnect();
}

void Analyzer::analyze()
{
    auto countFrame = videoFileReader.getSettings().getCountFrames();
    int intPercent = 0;
    emit progresPercent(intPercent);
    CrownChargeDetector detector(settings);
    for(int frameNumber = 0; frameNumber < countFrame; frameNumber++){
        auto percent = static_cast<double>(frameNumber) / static_cast<double>(countFrame) * 100;
        if (intPercent != std::ceil(percent)){
            intPercent = std::ceil(percent);
            emit progresPercent(intPercent);
        }
        qDebug()<< "FrameNumber:" << frameNumber << "Percent:" << percent << "Int percent:" << std::ceil(percent);
        cv::Mat src = videoFileReader.getCvImage(frameNumber);
        auto monochromeFrame = countorSelection(src);
        auto maskedFrame = applyMask(monochromeFrame);
        auto contours = searchContours(frameNumber, maskedFrame);
        detector.findCrownCharges(contours);
        auto lastCharges = detector.getLastDetectedCharges();
    }
    crownCharges = detector.getDetectedCharges();
    crownCharges.sort([](CrownCharge &first, CrownCharge &second){return first.getFirstFrameNumber() < second.getFirstFrameNumber();});
}

void Analyzer::setSettings(const BranchSettings &value)
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
        if (isFullTrack(crownCharge))
            fragmentInfo.setStatus("Полный трек");
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

cv::Mat Analyzer::binarizationHSV(const cv::Mat &src)
{
    cv::Mat dst, srcGray;
    auto color = contourFilterSetings.color.toHsv();
    cv::cvtColor(src, srcGray, cv::COLOR_BGR2HSV);
    cv::inRange(srcGray, cv::Scalar(color.hue(), color.saturation(), color.value()),
                cv::Scalar(color.hue(), color.saturation(), color.value()), dst);
    return dst;
}

cv::Mat Analyzer::countorSelection(const cv::Mat &src)
{
    switch (contourFilterSetings.mode) {
    case ContourFilterSettings::FilterContourMode::Normal:
        return binarization(src);
    case ContourFilterSettings::FilterContourMode::Colorfull:
        return binarizationHSV(src);
    }
}

void Analyzer::loadContourFilterSettings()
{
    contourFilterSetings = SettingKeeper::getInstance()->loadContourFilterSettings();
}

bool Analyzer::isFullTrack(const CrownCharge &crownCharge)
{
    auto contours = crownCharge.getContours();
    auto firstPoint = cvPoint2QPoint(contours.front().getCenterMass());
    auto lastPoint = cvPoint2QPoint(contours.back().getCenterMass());

    auto frameSize = videoFileReader.getSettings().getQSize();
    double scaleFactor = 0.15;
    QRect fullFrameRect(QPoint(0, 0), QPoint(frameSize.width(), frameSize.height()));

    QPoint partTopLeft = QPoint(static_cast<int>(std::ceil(frameSize.width()*scaleFactor)), static_cast<int>(std::ceil(frameSize.height()*scaleFactor)));
    QPoint partBottomRight = QPoint((frameSize.width() - static_cast<int>(std::ceil(frameSize.width()*scaleFactor))),
                                    (frameSize.height() - static_cast<int>(std::ceil(frameSize.height()*scaleFactor))));
    QRect partFrameRect(partTopLeft, partBottomRight);

    auto isPointOnEdgeFrame = [&fullFrameRect, &partFrameRect](const QPoint &point){
        return fullFrameRect.contains(point) && !partFrameRect.contains(point);
    };

    if (isPointOnEdgeFrame(firstPoint) && isPointOnEdgeFrame(lastPoint))
        return true;
    else
        return false;

}

QPoint Analyzer::cvPoint2QPoint(const cv::Point &point)
{
    return QPoint(point.x, point.y);
}

//bool Analyzer::isPointOnEdgeFrame(const QPoint &point)
//{

//}

cv::Mat Analyzer::applyMask(const cv::Mat &src)
{
    if (masks.empty())
        return src;
    cv::Mat dst;
    src.copyTo(dst);
    for (const auto &rect : masks){
        cv::Point topLeft(rect.toRect().topLeft().x(), rect.toRect().topLeft().y());
        cv::Point bottomRight(rect.toRect().topLeft().x() + rect.toRect().width(), rect.toRect().topLeft().y() + rect.toRect().height());
        cv::rectangle(dst, topLeft,bottomRight, cv::Scalar(0, 0, 0), cv::FILLED);
    }
    return dst;
}


