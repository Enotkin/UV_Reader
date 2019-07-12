#ifndef VIDEODATA_H
#define VIDEODATA_H

#include <QString>
#include <QTime>
#include <QFileInfo>
#include <QTimerEvent>
#include <QImage>
#include <memory>
#include <QDebug>
#include <QTimer>
#include "frame.h"
#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"
#include "videosettings.h"


class VideoFileReader : public QObject
{
    Q_OBJECT
public:
    explicit VideoFileReader(const QString &pathToSample, QObject *parent = nullptr);
    explicit VideoFileReader(const QFileInfo &fileInfo, QObject *parent = nullptr);
    ~VideoFileReader();

    QImage getQImage(int numberFrame);
    cv::Mat getCvImage(int numberFrame);
    Frame getFrame(int numberFrame);

    VideoSettings getSettings() const;

private:
    cv::VideoCapture videoCapture;
    QFileInfo p_fileInfo;
    VideoSettings settings;
};

#endif // VIDEODATA_H
