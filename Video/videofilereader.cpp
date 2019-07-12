#include "videofilereader.h"

VideoFileReader::VideoFileReader(const QString &pathToSample, QObject *parent):
    QObject(parent),
    videoCapture(pathToSample.toStdString()),
    p_fileInfo(pathToSample) ,
    settings(p_fileInfo) {}

VideoFileReader::VideoFileReader(const QFileInfo &fileInfo, QObject *parent):
    QObject(parent),
    videoCapture(fileInfo.absoluteFilePath().toStdString()),
    p_fileInfo(fileInfo),
    settings(p_fileInfo) {}

VideoFileReader::~VideoFileReader()
{
    videoCapture.release();
}

QImage VideoFileReader::getQImage(int numberFrame)
{
    if (numberFrame <= settings.getCountFrames()){
        videoCapture.set(cv::CAP_PROP_POS_FRAMES, static_cast<double>(numberFrame));
        cv::Mat frame;
        videoCapture.read(frame);
        if (frame.empty()) {
            return QImage();
        }
        QImage image(static_cast<uchar*>(frame.data),
                     frame.cols, frame.rows, QImage::Format_RGB888);
        return image.copy();
    } else {
        return QImage();
    }
}

cv::Mat VideoFileReader::getCvImage(int numberFrame)
{
    if (numberFrame <= settings.getCountFrames()){
        videoCapture.set(cv::CAP_PROP_POS_FRAMES, static_cast<double>(numberFrame));
        cv::Mat frame;
        videoCapture.read(frame);
        if (frame.empty()) {
            return cv::Mat();
        }
        return frame;
    } else {
        return cv::Mat();
    }
}

Frame VideoFileReader::getFrame(int numberFrame)
{
    return Frame(getCvImage(numberFrame), numberFrame, static_cast<double>(videoCapture.get(cv::CAP_PROP_POS_MSEC)));
}

VideoSettings VideoFileReader::getSettings() const
{
    return settings;
}



