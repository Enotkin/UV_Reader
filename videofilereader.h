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

    QImage getFrame(int numberFrame);
    bool isOpen() const;
    int getCurrentFrameNumber() const;
    double getTime() const;
    void setCurrentFrameNumber(int value);

    VideoSettings getSettings() const;

    cv::VideoCapture *getVideoCapture() const;

    QFileInfo getP_fileInfo() const;

private:
    std::unique_ptr<cv::VideoCapture> videoCapture;
    QFileInfo p_fileInfo;
    VideoSettings settings;

    QImage getImage();
    void settingsCreating();
    bool openDataFile(const QString &pathToFile);
};

#endif // VIDEODATA_H
