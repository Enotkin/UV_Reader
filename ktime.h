#ifndef KTIME_H
#define KTIME_H

#include <QObject>
#include <QString>

class KTime : public QObject
{
    Q_OBJECT
public:
    KTime(int hours = 0, int minutes = 0, int seconds = 0, int mileseconds = 0 );
    KTime();

    void addHours(int hours);
    void addMinutes(int min);
    void addSeconds (int sec);
    void addMseconds (int msec);

    QString toString();

private:
    int p_hours = 0;
    int p_minutes = 0;
    int p_seconds = 0;
    int p_mileseconds = 0;

    const int MSEC_MAX = 1000;
    const int SEC_MAX = 60;
    const int MIN_MAX = 60;

    void normalization();
    void msecNormalization();
    void secNormalization();
    void minNormalization();

    QString valueToString(const int value);
    QString msecToString();
};

#endif // KTIME_H
