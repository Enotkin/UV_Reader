#include "rectitembuilder.h"

RectItemBuilder::RectItemBuilder(QPointF startPoint) : startPoint(startPoint)
{
    item = new QGraphicsRectItem();
}

void RectItemBuilder::setPoint(const QPointF &point)
{
    QRect newRect;
    if (!isXLower(point) && !isYlower(point)) { //4 четверть
        newRect.setTopLeft(startPoint.toPoint());
        newRect.setBottomRight(point.toPoint());
    }
    if (isXLower(point) && isYlower(point)) { //2 четверть
        newRect.setTopLeft(point.toPoint());
        newRect.setBottomRight(startPoint.toPoint());
    }
    if (!isXLower(point) && isYlower(point)) { //1 четверть
        newRect.setTopRight(point.toPoint());
        newRect.setBottomLeft(startPoint.toPoint());
    }
    if (isXLower(point) && !isYlower(point)) { //3 четверть
        newRect.setTopRight(startPoint.toPoint());
        newRect.setBottomLeft(point.toPoint());
    }
    item->setRect(newRect);
}

QRectF RectItemBuilder::getRectF() const
{
    return item->rect();
}

QGraphicsRectItem *RectItemBuilder::getItem() const
{
    return item;
}

bool RectItemBuilder::isXLower(const QPointF &point) const
{
    return point.x() < startPoint.x() ? true : false;
}

bool RectItemBuilder::isYlower(const QPointF &point) const
{
    return point.y() < startPoint.y() ? true : false;
}
