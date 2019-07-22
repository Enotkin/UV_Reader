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
#include "settingkeeper.h"
#include "contourfiltersettings.h"

class Analyzer
{
public:
    Analyzer(const QFileInfo &sourceFileInfo);
    void analyze();
    void setSettings(const BranchSettings &value);
    std::list<FragmentInfo> getFragments();

private:
    VideoFileReader videoFileReader;
    std::list<CrownCharge> crownCharges;
    std::list<Contour> searchContours(int frameNumber, const cv::Mat &img);
    Masks masks;
    BranchSettings settings;

    ContourFilterSettings contourFilterSetings;
    double thresholdValue = 225;

    cv::Mat binarization(const cv::Mat &src);
    cv::Mat applyMask(const cv::Mat &src);
    cv::Mat binarizationHSV(const cv::Mat &src);
    cv::Mat countorSelection(const cv::Mat &src);
    void loadContourFilterSettings();
};

#endif // ANALYZER_H
