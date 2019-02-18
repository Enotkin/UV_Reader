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

class VideoFileReader : public QObject
{
    Q_OBJECT
public:
    explicit VideoFileReader(const QString &pathToSample, QObject *parent = nullptr);
    explicit VideoFileReader(const QFileInfo &fileInfo, QObject *parent = nullptr);
    ~VideoFileReader();

    QImage getFrame(int numberFrame);
    bool isOpen() const;
    int getCountFrames() const;
    int getCurrentFrameNumber() const;
    void setCurrentFrameNumber(int value);
    double getTime() const;

private:
    QFileInfo p_fileInfo;
    bool p_fileIsOpen = false;
    std::unique_ptr<cv::VideoCapture> videoCapture;

    QImage getImage();

    bool openDataFile(const QString &pathToFile);
    int countFrame = 0;

    int speedPlay = 40;

};

#endif // VIDEODATA_H
