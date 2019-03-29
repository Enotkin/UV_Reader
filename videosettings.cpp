#include "videosettings.h"

VideoSettings::VideoSettings(const int countFrames,
                             const cv::Size &size,
                             const int codec,
                             const double duration,
                             const double frameRate)
    : countFrames(countFrames),
      size(size),
      codec(codec),
      duration(duration),
      frameRate(frameRate)

{

}

int VideoSettings::getCountFrames() const
{
    return countFrames;
}

void VideoSettings::setCountFrames(int value)
{
    countFrames = value;
}

cv::Size VideoSettings::getSize() const
{
    return size;
}

void VideoSettings::setSize(const cv::Size &value)
{
    size = value;
}

QSize VideoSettings::getQSize() const
{
    return QSize(size.width, size.height);
}

void VideoSettings::setQSize(const QSize &value)
{
    size.width = value.width();
    size.height = value.height();
}

int VideoSettings::getCodec() const
{
    return codec;
}

void VideoSettings::setCodec(int value)
{
    codec = value;
}

double VideoSettings::getDuration() const
{
    return duration;
}

void VideoSettings::setDuration(double value)
{
    duration = value;
}

double VideoSettings::getFrameRate() const
{
    return frameRate;
}

void VideoSettings::setFrameRate(double value)
{
    frameRate = value;
}
