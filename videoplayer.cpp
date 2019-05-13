#include "videoplayer.h"

VideoPlayer::VideoPlayer(QObject *parent) : QObject(parent)
{

}

void VideoPlayer::setSoureceFile(const QFileInfo &value)
{
    soureceFile = value;
}
