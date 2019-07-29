#ifndef CONTOURFILTERSETTINGS_H
#define CONTOURFILTERSETTINGS_H
#include <QColor>

enum class FilterType
{
    Normal,
    Colorfull
};

struct FilterSettings
{
    QColor color {Qt::white};
    FilterType mode = FilterType::Normal;
};

#endif // CONTOURFILTERSETTINGS_H
