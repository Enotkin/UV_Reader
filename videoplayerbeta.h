#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QFileInfo>
#include <memory>
#include <functional>

#include "fragmentinfo.h"
#include "videofilereader.h"
#include "videosettings.h"
#include "uvgraphicsview.h"

class VideoPlayerBETA : public QObject
{
    Q_OBJECT
public:
    explicit VideoPlayerBETA(QObject *parent = nullptr);

    void setView(const std::function<void(const QImage&)> &displayImage);

    void setSoureceFile(const QFileInfo &value);

    void playFragment(FragmentInfo fragment);

    void play();

    void stop();

    void pause();

    void reset();

signals:
    void updateVideoInfo(double, int);

public slots:

private:
    void setFrame(const int frameNumber);

    int timerSpeed = 40;
    int stopFrame = 0;
    int startFrame = 0;
    QTimer timer;
    std::unique_ptr<VideoFileReader> videoFileReader;
    std::function<void(const QImage&)> displayFrame;
    UvGraphicsView *view = nullptr;
    FragmentInfo fragmentInfo;
    QFileInfo soureceFile;

};

#endif // VIDEOPLAYER_H
