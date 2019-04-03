#ifndef VIDEOFILEWRITER_H
#define VIDEOFILEWRITER_H

#include <QVector>
#include <QDebug>
#include <memory>
#include <QFileInfo>
#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"
#include "videofilereader.h"
#include "videosettings.h"

class VideoFileWriter
{
public:
    VideoFileWriter(const QFileInfo fileName, std::shared_ptr<VideoFileReader> videoReader);
    VideoFileWriter(const QFileInfo &pathToDir, VideoSettings settings);
    VideoFileWriter(const QString &pathToDir, VideoSettings settings);
    ~VideoFileWriter();
    void fn(int value);
private:
    std::unique_ptr<cv::VideoWriter> outputVideo;
    QFileInfo fileInfo;
    VideoSettings settings;

    QString getFullName();
};

#endif // VIDEOFILEWRITER_H
