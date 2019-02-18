#include "videofilereader.h"

VideoFileReader::VideoFileReader(const QString &pathToSample, QObject *parent): p_fileInfo(pathToSample)
{
    p_fileIsOpen = openDataFile(p_fileInfo.absoluteFilePath());
}

VideoFileReader::VideoFileReader(const QFileInfo &fileInfo, QObject *parent): p_fileInfo(fileInfo)
{
    p_fileIsOpen = openDataFile(p_fileInfo.absoluteFilePath());
}

VideoFileReader::~VideoFileReader()
{
    videoCapture->release();
}

bool VideoFileReader::isOpen() const
{
    return p_fileIsOpen;
}

int VideoFileReader::getCountFrames() const
{
    return static_cast<int>(videoCapture->get(cv::CAP_PROP_FRAME_COUNT));
}

int VideoFileReader::getCurrentFrameNumber() const
{
    return  static_cast<int>(videoCapture->get(cv::CAP_PROP_POS_FRAMES));
}

void VideoFileReader::setCurrentFrameNumber(int value)
{
    videoCapture->set(cv::CAP_PROP_POS_FRAMES, value);
}

double VideoFileReader::getTime() const
{
    return  static_cast<double>(videoCapture->get(cv::CAP_PROP_POS_MSEC));
}

QImage VideoFileReader::getFrame(int numberFrame)
{
    if (numberFrame <= this->getCountFrames()){
        videoCapture->set(cv::CAP_PROP_POS_FRAMES, static_cast<double>(numberFrame));
        return getImage().copy();
    } else {
        return QImage();
    }
}

QImage VideoFileReader::getImage()
{
    cv::Mat frame;
    videoCapture->read(frame);
    if (frame.empty()) {
        return QImage();
    }
    QImage image(static_cast<uchar*>(frame.data),
                 frame.cols, frame.rows, QImage::Format_RGB888);
    return image;
}

bool VideoFileReader::openDataFile(const QString &pathToFile)
{
    videoCapture = std::make_unique<cv::VideoCapture>(pathToFile.toStdString());
    videoCapture->set(cv::CAP_PROP_POS_AVI_RATIO, 0.0);
    countFrame = static_cast<int>(videoCapture->get(cv::CAP_PROP_FRAME_COUNT));
    this->startTimer(speedPlay);
    return videoCapture->isOpened();
}
