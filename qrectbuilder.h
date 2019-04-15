#ifndef QRECTBUILDER_H
#define QRECTBUILDER_H

#include <QRect>
#include <QPoint>


class QRectBuilder
{
public:
    QRectBuilder(QPoint startPoint);
    void addPoint(const QPoint &point);

    QRect getRect() const;

private:
    QPoint startPoint;
    QPoint topLeft;
    QPoint bottomRight;
    QRect rect;

    bool isXLower(const QPoint &point) const;
    bool isYlower(const QPoint &point) const;
};

#endif // QRECTBUILDER_H
