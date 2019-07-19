#ifndef CONTOURFILTERSETTINGS_H
#define CONTOURFILTERSETTINGS_H
#include <QColor>

struct ContourFilterSettings
{
    enum class FilterContourMode
    {
        Normal,
        Colorfull
    };

    QColor color {Qt::white};
    FilterContourMode mode = FilterContourMode::Normal;
};

#endif // CONTOURFILTERSETTINGS_H
