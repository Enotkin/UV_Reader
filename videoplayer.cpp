#include "videoplayer.h"

VideoPlayer::VideoPlayer(const QFileInfo &value, QObject *parent) : QObject(parent), soureceVideoFile(value)
{
    videoFileReader = std::make_unique<VideoFileReader>(soureceVideoFile);
    connect(&timer, &QTimer::timeout, this, &VideoPlayer::timerOut);
    startFrame = 0;
    stopFrame = videoFileReader->getSettings().getCountFrames();
}

void VideoPlayer::setFragment(const FragmentInfo &fragment)
{
    pause();

    if (fragment.getFrameRange().second <= videoFileReader->getSettings().getCountFrames())
        stopFrame = fragment.getFrameRange().second;
    else
        stopFrame = videoFileReader->getSettings().getCountFrames();

    startFrame = fragment.getFrameRange().first;
    begin();

    currentFragment = fragment;
    if (fragment.getFrameRange().second == videoFileReader->getSettings().getCountFrames() &&
            fragment.getFrameRange().first == 0) {
        setRepeatMode(false);
    } else {
        setRepeatMode(true);
        play(); //Воспроизвеение по умолчанию
    }
}

void VideoPlayer::setFrame(int frameNumber)
{
    if (!videoFileReader)
        return;
    if (frameNumber != stopFrame){
        emit updateFrame(getFrame(frameNumber), videoFileReader->getTime(), frameNumber);
    } else {
        if (repeatFragment){
            emit updateFrame(getFrame(startFrame), videoFileReader->getTime(), startFrame);
        } else {
            emit updateFrame(getFrame(stopFrame), videoFileReader->getTime(), stopFrame);
            pause();
        }
    }
}

void VideoPlayer::timerOut()
{
    setFrame(videoFileReader->getCurrentFrameNumber());
}

QImage VideoPlayer::getFrame(int number)
{
    CrownChargePainter p(currentFragment);

    return p.getImage(videoFileReader->getMatFrame(number), number);
}

void VideoPlayer::play()
{
    if(!timer.isActive())
        timer.start(timerSpeed);
}

void VideoPlayer::pause()
{
    if (timer.isActive())
        timer.stop();
}

void VideoPlayer::stop()
{
    pause();
    begin();
}

void VideoPlayer::begin()
{
    videoFileReader->setCurrentFrameNumber(startFrame);
    setFrame(startFrame);
}

void VideoPlayer::end()
{
    videoFileReader->setCurrentFrameNumber(stopFrame);
    setFrame(stopFrame);
}

void VideoPlayer::nextFrame()
{
    int frame = videoFileReader->getCurrentFrameNumber();
    setFrame(frame);
}

void VideoPlayer::prevFrame()
{
    int frame = videoFileReader->getCurrentFrameNumber() - 2;
    setFrame(frame);
}

void VideoPlayer::setRepeatMode(bool repeat)
{
    repeatFragment = repeat;
}

bool VideoPlayer::isPlayBackActive()
{
    return timer.isActive();
}


































