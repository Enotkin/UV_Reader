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
        QPair<int, int> hue {20, 20};
        QPair<int, int> saturation {30,30};
        QPair<int, int> value {30, 30};
    };

    QColor color {Qt::white};
    FilterType mode = FilterType::Normal;
    double thresholdValue = 225;
    CoefficientHsv coefficientHsv;
};

#endif // CONTOURFILTERSETTINGS_H
