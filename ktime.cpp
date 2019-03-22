#include "ktime.h"

KTime::KTime(int hours, int minutes, int seconds, int mileseconds)
       : p_hours(hours), p_minutes(minutes), p_seconds(seconds), p_mileseconds(mileseconds)
{
    normalization();
}


void KTime::addHours(int hours)
{
    p_hours += hours;
}

void KTime::addMinutes(int min)
{
    p_minutes += min;
    normalization();
}

void KTime::addSeconds(int sec)
{
    p_seconds = sec;
    normalization();
}

void KTime::addMseconds(int msec)
{
    p_mileseconds = msec;
    normalization();
}

QString KTime::toString()
{
    QString result = QString("%1:%2:%3")
            .arg(valueToString(p_hours))
            .arg(valueToString(p_minutes))
            .arg(valueToString(p_seconds));
    return result;
}

void KTime::normalization()
{
    msecNormalization();
    secNormalization();
    minNormalization();
}

void KTime::msecNormalization()
{
    while (p_mileseconds >= MSEC_MAX){
        p_seconds++;
        p_mileseconds -= MSEC_MAX;
    }
}

void KTime::secNormalization()
{
    while (p_seconds >= SEC_MAX){
        p_minutes++;
        p_seconds -= SEC_MAX;
    }
}

void KTime::minNormalization()
{
    while (p_minutes >= MIN_MAX){
        p_hours++;
        p_minutes -= MIN_MAX;
    }
}

QString KTime::valueToString(const int value)
{
    QString result;
    if (value <= 0){
       result.append("00");
    } else if (value < 10) {
        result.append("0" + QString::number(value));
    } else {
        result.append(QString::number(value));
    }
    return result;
}

