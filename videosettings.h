#ifndef VIDEOSETTINGS_H
#define VIDEOSETTINGS_H
#include "opencv2/highgui.hpp"
#include <QSize>


class VideoSettings
{
public:
    VideoSettings(const int countFrames,
                  const cv::Size &size,
                  const int codec,
                  const double duration,
                  const double frameRate);
    VideoSettings(){}

    int getCountFrames() const;
    void setCountFrames(int value);

    cv::Size getSize() const;
    void setSize(const cv::Size &value);

    QSize getQSize() const;
    void setQSize(const QSize &value);

    int getCodec() const;
    void setCodec(int value);

    double getDuration() const;
    void setDuration(double value);

    double getFrameRate() const;
    void setFrameRate(double value);

private:
    int countFrames = 0;
    cv::Size size = {0, 0};
    int codec = 0;
    double duration = 0;
    double frameRate = 0;

};

#endif // VIDEOSETTINGS_H
