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
    currentFragment = fragment;
    crownChargePainter = std::make_unique<CrownChargePainter>(currentFragment);

    if (fragment.getFrameRange().second <= videoFileReader->getSettings().getCountFrames())
        stopFrame = fragment.getFrameRange().second;
    else
        stopFrame = videoFileReader->getSettings().getCountFrames();

    startFrame = fragment.getFrameRange().first;
    begin();


    if (fragment.getFrameRange().second == videoFileReader->getSettings().getCountFrames() &&
            fragment.getFrameRange().first == 0) {
        setRepeatMode(false);
    } else {
        setRepeatMode(true);
//        play(); //Воспроизвеение по умолчанию
    }
}

void VideoPlayer::setFrame(int frameNumber)
{
    if (!videoFileReader)
        return;
    if (frameNumber != stopFrame){
        emit updateFrame(getFrame(frameNumber));
    } else {
        if (repeatFragment){
            if(timer.isActive()){
                emit updateFrame(getFrame(startFrame));
            }else{}
        } else {
            emit updateFrame(getFrame(stopFrame));
            pause();
        }
    }
}

void VideoPlayer::timerOut()
{
    setFrame(++currentFrameNumber);
}

Frame VideoPlayer::getFrame(int number)
{
    return crownChargePainter->getTrackFrame(videoFileReader->getFrame(number));
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
    currentFrameNumber = startFrame;
    setFrame(startFrame);
}

void VideoPlayer::end()
{
    currentFrameNumber = stopFrame;
    setFrame(stopFrame);
}

void VideoPlayer::nextFrame()
{
    currentFrameNumber++;
    setFrame(currentFrameNumber);
}

void VideoPlayer::prevFrame()
{
    currentFrameNumber--;
    setFrame(currentFrameNumber);
}

void VideoPlayer::setRepeatMode(bool repeat)
{
    repeatFragment = repeat;
}

bool VideoPlayer::isPlayBackActive()
{
    return timer.isActive();
}


































