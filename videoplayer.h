#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QFileInfo>
#include <memory>

#include "fragmentinfo.h"
#include "videofilereader.h"
#include "videosettings.h"

class VideoPlayer : public QObject
{
    Q_OBJECT
public:
    explicit VideoPlayer(QObject *parent = nullptr);

    void setSoureceFile(const QFileInfo &value);

    void playFragment(FragmentInfo fragment);

    void start();

    void stop();

    void pause();

    void returnSourceVideo();

signals:

public slots:

private:
    std::unique_ptr<VideoFileReader> videoFileReader;
    FragmentInfo fragmentInfo;
    QFileInfo soureceFile;

};

#endif // VIDEOPLAYER_H
