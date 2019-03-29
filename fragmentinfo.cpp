#include "fragmentinfo.h"

FragmentInfo::FragmentInfo(int frameNumber, QString pillarName, QTime time, QString status = "Added")
    : empty(false),
      frameRange(frameNumber, frameNumber),
      pillarRange(pillarName, pillarName),
      time (time, time),
      status(status),
      frameNumberReport(average(frameRange)){}

FragmentInfo::FragmentInfo(FrameRange frameRange, PillarRange pillarRange, TimeRange timeRange, QString status = "Added")
    : empty(false),
      frameRange(frameRange),
      pillarRange(pillarRange),
      time(timeRange),
      status(status),
      frameNumberReport(average(frameRange)){}

FragmentInfo::FragmentInfo() : empty(false) {}

bool FragmentInfo::isVideoFragment() const
{
    return (frameRange.first == frameRange.second) ? false : true;
}

bool FragmentInfo::isEmpty() const
{
    return empty;
}

FragmentInfo::operator bool() const
{
    return empty;
}

FrameRange FragmentInfo::getFrameRange() const
{
    return frameRange;
}

PillarRange FragmentInfo::getPillarRange() const
{
    return pillarRange;
}

TimeRange FragmentInfo::getTime() const
{
    return time;
}

QString FragmentInfo::getStatus() const
{
    return status;
}

int FragmentInfo::getFrameNumberReport() const
{
    return frameNumberReport;
}

int FragmentInfo::average(FrameRange range)
{
    return static_cast<int>((range.first + range.second)/2);
}
