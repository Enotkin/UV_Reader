#include "coordinatesconverter.h"

CoordinatesConverter::CoordinatesConverter()
{

}

void CoordinatesConverter::setDerivedCoordinates(const QSize &value)
{
    derivedCoordinates = value;
}

void CoordinatesConverter::setSourceCoordinates(const QSize &value)
{
    sourceCoordinates = value;
}
