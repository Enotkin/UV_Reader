#ifndef FRAGMENTINFO_H
#define FRAGMENTINFO_H

#include <QString>
#include <QPair>
#include <QTime>

using FrameRange = QPair<int,int>;
using TimeRange = QPair<QTime, QTime>;
using PillarRange = QPair<QString, QString>;

class FragmentInfo
{
public:
    FragmentInfo(int frameRange, QString pillarRange,
                 QTime time, QString status);
    FragmentInfo(FrameRange frameRange, PillarRange pillarRange,
                 TimeRange timeRange, QString status);
    FragmentInfo();

    bool isEmpty() const;
    operator bool() const;

    bool isVideoFragment() const;

    FrameRange getFrameRange() const;

    PillarRange getPillarRange() const;

    TimeRange getTime() const;

    QString getStatus() const;

    int getFrameNumberReport() const;

private:
    bool empty = true;
    FrameRange frameRange {0,0};
    PillarRange pillarRange {QString(), QString()};
    TimeRange time {QTime(), QTime()};
    QString status = QString();
    int frameNumberReport = 0;

    int average(FrameRange range);
};

#endif // FRAGMENTINFO_H
