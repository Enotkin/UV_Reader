#include "uvgraphicsview.h"

UvGraphicsView::UvGraphicsView(QWidget *parent)
{
    Q_UNUSED(parent);
    this->setScene(&scene);
    imageItem = std::make_unique<QGraphicsPixmapItem>();
    scene.addItem(imageItem.get());
//    this->fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
}

UvGraphicsView::~UvGraphicsView()
{
    this->clearMasks();
    imageItem.release();
}

//TODO добавить проверку на вхождение прямоугольника в область изображения
void UvGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (editMode && event->button() == Qt::LeftButton){
        rectBuilder.setStartPoint(this->mapToScene(event->pos()).toPoint());
        currentRectItem = new QGraphicsRectItem();
        currentRectItem->setBrush(QBrush(QColor(0, 0, 255), Qt::Dense6Pattern));
        scene.addItem(currentRectItem);
    }
}

void UvGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (editMode && currentRectItem) {
        rectBuilder.setPoint(this->mapToScene(event->pos()).toPoint());
        currentRectItem->setRect(rectBuilder.getRect());
    }
}

void UvGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (editMode && event->button() == Qt::LeftButton){
        rectBuilder.setPoint(this->mapToScene(event->pos()).toPoint());
        rectItems.append(currentRectItem);
        currentRectItem = nullptr;
        rectBuilder.clear();
    }
}

void UvGraphicsView::paintEvent(QPaintEvent *event)
{
//    if (resizeMode)
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
    this->fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
}

QList<QRect> UvGraphicsView::getMaskRect() const
{
    QList<QRect> rects;
    for (const auto rectItem : rectItems) {
        rects.append(rectItem->rect().toRect());
    }

    return rects;
}

void UvGraphicsView::clearMasks()
{
    for (const auto maskRectItem : rectItems) {
        scene.removeItem(maskRectItem);
    }
    rectItems.clear();
}

void UvGraphicsView::setEditMode(bool value)
{
    editMode = value;
    for (const auto rectItem : rectItems) {
        rectItem->setVisible(value);
    }
}

//TODO Починить сделать возможность переключения маштабирования
void UvGraphicsView::setResizeMode(bool value)
{
    resizeMode = value;
    if (resizeMode == true)
        this->fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
    else {

    }
    this->repaint();
}

