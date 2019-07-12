#ifndef ANALYZER_H
#define ANALYZER_H
#include <QFileInfo>
#include <QRect>
#include <filesystem>
#include <memory>

#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"
#include "crownchargedetector.h"
#include "crowncharge.h"
#include "fragmentinfo.h"
#include "videofilereader.h"

class Analyzer
{
public:
    Analyzer(const QFileInfo &sourceFileInfo);
    void analyze();
    void setMask(QList<QRect> value);
    void setSettings(const SuspectCrownChargeSettings &value);
    std::list<FragmentInfo> getFragments();

private:
    std::unique_ptr<VideoFileReader> videoFileReader;
    std::list<CrownCharge> crownCharges;
    std::list<QRect> masks;
    std::filesystem::path sourceFile;
    std::list<Contour> searchContours(int frameNumber, const cv::Mat &img);
    SuspectCrownChargeSettings settings;
    double thresholdValue = 225;

    cv::Mat binarization(const cv::Mat &src);
    cv::Mat applyMask(const cv::Mat &src);

};

#endif // ANALYZER_H
