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
#include "crownchargepainter.h"

class VideoPlayer : public QObject
{
    Q_OBJECT
public:
    explicit VideoPlayer(const QFileInfo &value, QObject *parent = nullptr);

    void setFragment(const FragmentInfo &fragment);

    void play();

    void stop();

    void pause();

    void begin();

    void end();

    void nextFrame();

    void prevFrame();

    void setRepeatMode(bool repeat);

    bool isPlayBackActive();

public slots:
    void setFrame(int frameNumber);

private slots:
    void timerOut();

signals:
    void updateFrame(Frame);

private:
    int timerSpeed = 40;
    int stopFrame = 0;
    int startFrame = 0;
    int currentFrameNumber = 0;
    bool repeatFragment = false;
    QTimer timer;
    std::unique_ptr<CrownChargePainter> crownChargePainter;
    std::unique_ptr<VideoFileReader> videoFileReader;
    std::function<void(const QImage&)> displayFrame;
    FragmentInfo currentFragment;
    QFileInfo soureceVideoFile;

    Frame getFrame(int number);

};

#endif // VIDEOPLAYER_H
