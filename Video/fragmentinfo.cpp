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

QString FragmentInfo::getFrameRangeString() const
{
    if (isVideoFragment()) {
        return QString("%1 - %2")
                .arg(frameRange.first)
                .arg(frameRange.second);
    } else {
        return QString::number(frameRange.first);
    }
}

PillarRange FragmentInfo::getPillarRange() const
{
    return pillarRange;
}

QString FragmentInfo::getPillarRangeString() const
{
    if (isVideoFragment()) {
        return QString("%1 - %2")
                .arg(pillarRange.first)
                .arg(pillarRange.second);
    }else {
        return pillarRange.first;
    }
}

TimeRange FragmentInfo::getTime() const
{
    return time;
}

QString FragmentInfo::getTimeString() const
{
    if (isVideoFragment()){
       return QString("%1 - %2")
                .arg(time.first.toString("hh:mm:ss"))
                .arg(time.second.toString("hh:mm:ss"));
    } else {
        return time.first.toString("hh:mm:ss");
    }
}

QString FragmentInfo::getStatus() const
{
    return status;
}

int FragmentInfo::getFrameNumberReport() const
{
    return frameNumberReport;
}

CrownCharge FragmentInfo::getCrownCharge() const
{
    return crownCharge;
}

void FragmentInfo::setCrownCharge(const CrownCharge &value)
{
    crownCharge = value;
    if (frameRange.first == 0 && frameRange.second == 0){
        auto ss = crownCharge.getRange();
        frameRange = ss;
    }
}

void FragmentInfo::setStatus(const QString &value)
{
    status = value;
}

int FragmentInfo::average(FrameRange range)
{
    return static_cast<int>((range.first + range.second)/2);
}
