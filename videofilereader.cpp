#include "videofilereader.h"

VideoFileReader::VideoFileReader(const QString &pathToSample, QObject *parent): QObject(parent), p_fileInfo(pathToSample)
{
    openDataFile(p_fileInfo.absoluteFilePath());
    settingsCreating();
}

VideoFileReader::VideoFileReader(const QFileInfo &fileInfo, QObject *parent): QObject(parent), p_fileInfo(fileInfo)
{
    openDataFile(p_fileInfo.absoluteFilePath());
    settingsCreating();
}

VideoFileReader::~VideoFileReader()
{
    videoCapture->release();
}

bool VideoFileReader::isOpen() const
{
    return videoCapture->isOpened();
}

int VideoFileReader::getCurrentFrameNumber() const
{
    return static_cast<int>(videoCapture->get(cv::CAP_PROP_POS_FRAMES));
}

void VideoFileReader::setCurrentFrameNumber(int value)
{
    videoCapture->set(cv::CAP_PROP_POS_FRAMES, value);
}

double VideoFileReader::getTime() const
{
    return  static_cast<double>(videoCapture->get(cv::CAP_PROP_POS_MSEC));
}

VideoSettings VideoFileReader::getSettings() const
{
    return settings;
}

cv::VideoCapture *VideoFileReader::getVideoCapture() const
{
    return videoCapture.get();
}

QFileInfo VideoFileReader::getP_fileInfo() const
{
    return p_fileInfo;
}

void VideoFileReader::settingsCreating()
{
    int curretnPosition = static_cast<int>(videoCapture->get(cv::CAP_PROP_POS_FRAMES));
    videoCapture->set(cv::CAP_PROP_POS_AVI_RATIO, 1);
    settings.setDuration(videoCapture->get(cv::CAP_PROP_POS_MSEC));
    videoCapture->set(cv::CAP_PROP_POS_FRAMES, curretnPosition);

    settings.setSize(cv::Size(static_cast<int>(videoCapture->get(cv::CAP_PROP_FRAME_WIDTH)),
                              static_cast<int>(videoCapture->get(cv::CAP_PROP_FRAME_HEIGHT))));
    settings.setCodec(static_cast<int>(videoCapture->get(cv::CAP_PROP_FOURCC)));
    settings.setFrameRate(videoCapture->get(cv::CAP_PROP_FPS));
    settings.setCountFrames(static_cast<int>(videoCapture->get(cv::CAP_PROP_FRAME_COUNT)));
}

QImage VideoFileReader::getFrame(int numberFrame)
{
    if (numberFrame <= settings.getCountFrames()){
        videoCapture->set(cv::CAP_PROP_POS_FRAMES, static_cast<double>(numberFrame));
        cv::Mat frame;
        videoCapture->read(frame);
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

cv::Mat VideoFileReader::getMatFrame(int numberFrame)
{
    return cv::Mat();
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
    return videoCapture->isOpened();
}

