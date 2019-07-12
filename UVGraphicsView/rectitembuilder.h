#ifndef QRECTBUILDER_H
#define QRECTBUILDER_H

#include <QRect>
#include <QPoint>
#include <QGraphicsRectItem>


class RectItemBuilder
{
public:
    RectItemBuilder(QPointF startPoint = QPointF());
    void setPoint(const QPointF &point);
    QRectF getRectF() const;
    QGraphicsRectItem *getItem() const;

private:
    QPointF startPoint;
    QGraphicsRectItem *item = nullptr;

    bool isXLower(const QPointF &point) const;
    bool isYlower(const QPointF &point) const;
};

#endif // QRECTBUILDER_H
