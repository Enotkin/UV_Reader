#ifndef FRAGMENTINFO_H
#define FRAGMENTINFO_H

#include <QString>
#include <QMetaType>
#include <QPair>
#include <QTime>

#include <memory>

#include "crowncharge.h"

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
    QString getFrameRangeString() const;

    PillarRange getPillarRange() const;
    QString getPillarRangeString() const;

    TimeRange getTime() const;
    QString getTimeString() const;

    QString getStatus() const;
    void setStatus(const QString &value);

    int getFrameNumberReport() const;

    CrownCharge getCrownCharge() const;
    void setCrownCharge(const CrownCharge &value);

private:
    bool empty = true;
    FrameRange frameRange {0,0};
    PillarRange pillarRange {QString(), QString()};
    TimeRange time {QTime(), QTime()};
    QString status = QString();
    int frameNumberReport = 0;
    CrownCharge crownCharge;
    int average(FrameRange range);
};


Q_DECLARE_METATYPE(FragmentInfo);

#endif // FRAGMENTINFO_H
