#ifndef UVGRAPHICSVIEW_H
#define UVGRAPHICSVIEW_H

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>
#include <QTime>

#include <forward_list>
#include <memory>

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

    QList<QRect> getMaskRect() const;

    void clearMasks();

protected:
    void mousePressEvent(QMouseEvent *event) override final;
    void mouseMoveEvent(QMouseEvent *event) override final;
    void mouseReleaseEvent(QMouseEvent *event) override final;
    void paintEvent(QPaintEvent *event) override final;

private:
//    QList<QRect> rects;
    QList<QGraphicsRectItem*> rectItems;
    QGraphicsRectItem *currentRectItem = nullptr;
    std::unique_ptr<QGraphicsPixmapItem> imageItem;
    QRectBuilder rectBuilder;
    QGraphicsScene scene;
    bool editMode = false;
    bool resizeMode = true;


    QSize size = {0, 0};
    QPoint topLeft;
    QPoint bottomRight;

    bool sceneBorderCheck(const QPoint &point) const;

};

#endif // UVGRAPHICSVIEW_H
