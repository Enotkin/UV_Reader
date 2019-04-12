#include "uvgraphicsview.h"

UvGraphicsView::UvGraphicsView(QWidget *parent)
{
    Q_UNUSED(parent);

}

void UvGraphicsView::mousePressEvent(QMouseEvent *event)
{
//    qDebug()<<"Pressed"<<event->pos()<<this->mapToScene(event->pos());
}

void UvGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    qDebug()<< this->mapToScene(event->pos());
}

void UvGraphicsView::paintEvent(QPaintEvent *event)
{
    if (this->scene() && resizeMode){
        this->fitInView(this->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
        qDebug()<< resizeMode;
    }
    QGraphicsView::paintEvent(event);
}

bool UvGraphicsView::getResizeMode() const
{
    return resizeMode;
}

void UvGraphicsView::setEditMode(bool value)
{
    editMode = value;
}

void UvGraphicsView::setResizeMode(bool value)
{
    resizeMode = value;
}
