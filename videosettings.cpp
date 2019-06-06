#include "videosettings.h"

VideoSettings::VideoSettings(const QFileInfo &file)
{
    initialization(file);
}

void VideoSettings::initialization(const QFileInfo &file)
{
    cv::VideoCapture video(file.absoluteFilePath().toStdString());
    video.set(cv::CAP_PROP_POS_AVI_RATIO, 1);
    duration = video.get(cv::CAP_PROP_POS_MSEC);
    size = cv::Size(static_cast<int>(video.get(cv::CAP_PROP_FRAME_WIDTH)),
                    static_cast<int>(video.get(cv::CAP_PROP_FRAME_HEIGHT)));
    codec = static_cast<int>(video.get(cv::CAP_PROP_FOURCC));
    frameRate = video.get(cv::CAP_PROP_FPS);
    countFrames = static_cast<int>(video.get(cv::CAP_PROP_FRAME_COUNT));
    full = true;
}

int VideoSettings::getCountFrames() const
{
    return countFrames;
}

cv::Size VideoSettings::getSize() const
{
    return size;
}

QSize VideoSettings::getQSize() const
{
    return QSize(size.width, size.height);
}

int VideoSettings::getCodec() const
{
    return codec;
}

double VideoSettings::getDuration() const
{
    return duration;
}

double VideoSettings::getFrameRate() const
{
    return frameRate;
}

bool VideoSettings::isEmpty() const
{
    return full;
}

VideoSettings::operator bool() const
{
    return isEmpty();
}
