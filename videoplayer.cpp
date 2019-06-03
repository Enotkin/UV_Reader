#include "videoplayer.h"

VideoPlayer::VideoPlayer(QObject *parent) : QObject(parent)
{
    connect(&timer, &QTimer::timeout, this, [this](){
        this->setFrame(this->videoFileReader->getCurrentFrameNumber());});

}

void VideoPlayer::setView(const std::function<void (const QImage &)> &displayImage)
{
    if (!displayFrame)
        displayFrame = displayImage;
    return;
}

void VideoPlayer::setSoureceFile(const QFileInfo &value)
{
    soureceFile = value;
    videoFileReader = std::make_unique<VideoFileReader>(soureceFile);
    startFrame = 0;
    stopFrame = videoFileReader->getSettings().getCountFrames();
}

void VideoPlayer::playFragment(FragmentInfo fragment)
{
    if (fragment.getFrameRange().second <= videoFileReader->getSettings().getCountFrames())
        stopFrame = fragment.getFrameRange().second;
    startFrame = fragment.getFrameRange().first;
    videoFileReader->setCurrentFrameNumber(startFrame);
    play();
}

void VideoPlayer::play()
{
    if(!timer.isActive())
        timer.start(timerSpeed);
}

void VideoPlayer::stop()
{
    pause();
    videoFileReader->setCurrentFrameNumber(startFrame);
    //TODO Отмытываение на начало.
}

void VideoPlayer::pause()
{
    if (timer.isActive())
        timer.stop();
}

void VideoPlayer::reset()
{
    stop();
    startFrame = 0;
    stopFrame = videoFileReader->getSettings().getCountFrames();
    setFrame(startFrame);
}

void VideoPlayer::setFrame(const int frameNumber)
{
    if (!videoFileReader || !displayFrame)
        return;
    auto changeFrame = [&](int frame){
        displayFrame(videoFileReader->getFrame(frame));
        emit updateVideoInfo(videoFileReader->getTime(), frame);};
    frameNumber != stopFrame ? changeFrame(frameNumber) : changeFrame(startFrame);
}
