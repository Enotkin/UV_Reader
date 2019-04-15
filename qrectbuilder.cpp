#include "qrectbuilder.h"

QRectBuilder::QRectBuilder(QPoint startPoint) : startPoint(startPoint), topLeft(startPoint), bottomRight(startPoint)
{

}

void QRectBuilder::addPoint(const QPoint &point)
{
    QRect newRect;
    if (!isXLower(point) && !isYlower(point)) { //4 четверть
        newRect.setTopLeft(startPoint);
        newRect.setBottomRight(point);
    }
    if (isXLower(point) && isYlower(point)) { //2 четверть
        newRect.setTopLeft(point);
        newRect.setBottomRight(startPoint);
    }
    if (!isXLower(point) && isYlower(point)) { //1 четверть
        newRect.setTopRight(point);
        newRect.setBottomLeft(startPoint);
    }
    if (isXLower(point) && !isYlower(point)) { //3 четверть
        newRect.setTopRight(startPoint);
        newRect.setBottomLeft(point);
    }
    rect = newRect;
}

QRect QRectBuilder::getRect() const
{
    return rect;
}

bool QRectBuilder::isXLower(const QPoint &point) const
{
    return point.x() < startPoint.x() ? true : false;
}

bool QRectBuilder::isYlower(const QPoint &point) const
{
    return point.y() < startPoint.y() ? true : false;
}
