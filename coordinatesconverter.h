#ifndef COORDINATESCONVERTER_H
#define COORDINATESCONVERTER_H

#include <QSize>
#include <QPoint>

class CoordinatesConverter
{
public:
    CoordinatesConverter();

    void setDerivedCoordinates(const QSize &value);

    void setSourceCoordinates(const QSize &value);

    QPoint source2Derived(const QPoint &point);

    QPoint derived2Source(const QPoint &point);

private:
    QSize derivedCoordinates;
    QSize sourceCoordinates;
};

#endif // COORDINATESCONVERTER_H
