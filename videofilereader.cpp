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

void VideoFileReader::start()
{
    if (isEndOfFile())
        goToBeginningFile();
    p_isPlaying = true;
}

void VideoFileReader::stop()
{
    p_isPlaying = false;
}

int VideoFileReader::coutFrames() const
{
    return static_cast<int>(videoCapture->get(cv::CAP_PROP_FRAME_COUNT));
}

QImage VideoFileReader::getPreview()
{
    QImage preview;
    if (videoCapture->isOpened()){
        int currentNumberFrame = static_cast<int>(videoCapture->get(cv::CAP_PROP_POS_FRAMES));
        goToBeginningFile();
        preview = getImage().copy();
        videoCapture->set(cv::CAP_PROP_POS_FRAMES, currentNumberFrame);
    }
    return preview;
}

void VideoFileReader::setFrame(int frameNumber)
{
    if (frameNumber < this->coutFrames()){
        videoCapture->set(cv::CAP_PROP_POS_FRAMES, static_cast<double>(frameNumber));
        emit newImageReady(getImage().copy(), static_cast<int>(videoCapture->get(cv::CAP_PROP_POS_FRAMES)));
    }
}

void VideoFileReader::timerEvent(QTimerEvent *event)
{
    if (p_isPlaying){
        emit newImageReady(getImage().copy(), static_cast<int>(videoCapture->get(cv::CAP_PROP_POS_FRAMES)));
    }
    if (isEndOfFile()){
        p_isPlaying = false;
        emit fileEnded();
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

bool VideoFileReader::isPlaying() const
{
    return p_isPlaying;
}

void VideoFileReader::goToBeginningFile()
{
    videoCapture->set(cv::CAP_PROP_POS_FRAMES, 1);
}

bool VideoFileReader::isEndOfFile()
{
    return static_cast<int>(videoCapture->get(cv::CAP_PROP_POS_FRAMES)) == static_cast<int>(videoCapture->get(cv::CAP_PROP_FRAME_COUNT));
}
