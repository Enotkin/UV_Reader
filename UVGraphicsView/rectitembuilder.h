#ifndef QRECTBUILDER_H
#define QRECTBUILDER_H

#include <QRect>
#include <QPoint>


class QRectBuilder
{
public:
    QRectBuilder(QPoint startPoint = QPoint());
    void setPoint(const QPoint &point);
    void setStartPoint(const QPoint &point);
    void clear();
    QRect getRect() const;


private:
    QPoint startPoint;
    QRect rect;

    bool isXLower(const QPoint &point) const;
    bool isYlower(const QPoint &point) const;
};

#endif // QRECTBUILDER_H
