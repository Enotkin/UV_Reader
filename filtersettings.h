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
    struct CoefficientHsv {
        QPair<int, int> hue {15, 15};
        QPair<int, int> saturation {10, 10};
        QPair<int, int> value {10, 10};
    };

    QColor color {Qt::white};
    FilterType mode = FilterType::Normal;
    double thresholdValue = 225;
    CoefficientHsv coefficientHsv;
};

#endif // CONTOURFILTERSETTINGS_H
