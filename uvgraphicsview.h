#ifndef UVGRAPHICSVIEW_H
#define UVGRAPHICSVIEW_H

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>

#include "qrectbuilder.h"

class UvGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    UvGraphicsView(QWidget *parent);
    ~UvGraphicsView() override;

    void setResizeMode(bool value);

    void setEditMode(bool value);

    bool getResizeMode() const;

    void setImage(const QImage &image);

protected:
    void mousePressEvent(QMouseEvent *event) override final;
    void mouseMoveEvent(QMouseEvent *event) override final;
    void mouseReleaseEvent(QMouseEvent *event) override final;
    void paintEvent(QPaintEvent *event) override final;

private:
    QList<QGraphicsRectItem*> maskRects;
    QGraphicsRectItem *workingRectItem;
    QGraphicsPixmapItem *imageItem;
    QRectBuilder *rectBuilder;
    QRect imageRect;
    QGraphicsScene scene;
    QRect rect;
    bool editMode = true;
    bool resizeMode = false;


    QSize size = {0, 0};
    QPoint topLeft;
    QPoint bottomRight;

    bool sceneBorderCheck(const QPoint &point) const;

};

#endif // UVGRAPHICSVIEW_H
