#ifndef VIDEOSETTINGS_H
#define VIDEOSETTINGS_H
#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"
#include <QSize>
#include <QFileInfo>

class VideoSettings
{
public:
    VideoSettings(const QFileInfo &file);

    int getCountFrames() const;

    cv::Size getSize() const;

    QSize getQSize() const;

    int getCodec() const;

    double getDuration() const;

    double getFrameRate() const;

    bool isEmpty() const;
    operator bool() const;

private:
    int countFrames = 0;
    cv::Size size = {0, 0};
    int codec = 0;
    double duration = 0;
    double frameRate = 0;
    bool full = false;

    void initialization(const QFileInfo &file);
};

#endif // VIDEOSETTINGS_H
