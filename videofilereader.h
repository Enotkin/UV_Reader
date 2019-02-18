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

    bool isOpen() const;
    void start();
    void stop();
    int coutFrames() const;
    QImage getPreview();


    bool isPlaying() const;

public slots:
    void setFrame(int frameNumber);

signals:
    void newImageReady(QImage image, int count);
    void fileEnded();

protected:
    void timerEvent(QTimerEvent* event) override;

private:
    QFileInfo p_fileInfo;
    QTimer timer;
    bool p_fileIsOpen = false;
    std::unique_ptr<cv::VideoCapture> videoCapture;

    QImage getImage();
    void goToBeginningFile();
    bool isEndOfFile();

    bool openDataFile(const QString &pathToFile);
    bool p_isPlaying = false;
    int countFrame = 0;
    int speedPlay = 40;

};

#endif // VIDEODATA_H
