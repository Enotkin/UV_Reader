#include "uvgraphicsview.h"

UvGraphicsView::UvGraphicsView(QWidget *parent)
{
    Q_UNUSED(parent);
    this->setScene(&scene);
    imageItem = new QGraphicsPixmapItem();
    scene.addItem(imageItem);
    imageRect = scene.itemsBoundingRect().toRect();
}

UvGraphicsView::~UvGraphicsView()
{
    delete imageItem;
}

//TODO добавить проверку на вхождение прямоугольника в область изображения
void UvGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (!editMode)
        return;
    rectBuilder = new QRectBuilder(this->mapToScene(event->pos()).toPoint());
    workingRectItem = new QGraphicsRectItem();
    workingRectItem->setBrush(QBrush(QColor(0, 0, 255), Qt::Dense6Pattern));
    scene.addItem(workingRectItem);
}

void UvGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (!editMode)
        return;
    rectBuilder->addPoint(this->mapToScene(event->pos()).toPoint());
    workingRectItem->setRect(rectBuilder->getRect());
}

void UvGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (!editMode)
        return;
    rectBuilder->addPoint(this->mapToScene(event->pos()).toPoint());
    workingRectItem->setRect(rectBuilder->getRect());
    delete rectBuilder;
}

void UvGraphicsView::paintEvent(QPaintEvent *event)
{
//    if(resizeMode)
//        this->fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
    QGraphicsView::paintEvent(event);
}

bool UvGraphicsView::sceneBorderCheck(const QPoint &point) const
{
    return this->sceneRect().contains(point);
}

bool UvGraphicsView::getResizeMode() const
{
    return resizeMode;
}

void UvGraphicsView::setImage(const QImage &image)
{
    imageItem->setPixmap(QPixmap::fromImage(image));
}

void UvGraphicsView::setEditMode(bool value)
{
    editMode = value;
}

void UvGraphicsView::setResizeMode(bool value)
{
    resizeMode = value;
    if (resizeMode == true)
        this->fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
    this->repaint();
}

