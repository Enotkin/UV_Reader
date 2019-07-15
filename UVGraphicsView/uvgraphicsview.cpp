#include "uvgraphicsview.h"

UvGraphicsView::UvGraphicsView(QWidget *parent)
{
    Q_UNUSED(parent);
    this->setScene(&scene);
    imageItem = std::make_unique<QGraphicsPixmapItem>();
    scene.addItem(imageItem.get());
}

UvGraphicsView::~UvGraphicsView()
{
    this->clearMasks();
    imageItem.release();
}

// ========================= Mouse Events =================================
//TODO добавить проверку на вхождение прямоугольника в область изображения
void UvGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        if (editMaskMode){
            rectItemBuilder.emplace(this->mapToScene(event->pos()));
            scene.addItem(rectItemBuilder->getItem());
        } else {
            selectGraphicsItem(this->mapToScene(event->pos()));
        }
    }
}

void UvGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (editMaskMode && rectItemBuilder) {
        rectItemBuilder->setPoint(this->mapToScene(event->pos()).toPoint());
    }
}

void UvGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        if (editMaskMode && rectItemBuilder){
            rectItemBuilder->setPoint(this->mapToScene(event->pos()));
            rectItems.append(rectItemBuilder->getItem());
            emit addRect(rectItemBuilder->getItem()->rect());
        }
        rectItemBuilder = std::nullopt;
    }
}

// ======================================================================

bool UvGraphicsView::sceneBorderCheck(const QPoint &point) const
{
    return this->sceneRect().contains(point);
}

QBrush UvGraphicsView::getBrush(const BrushColor color)
{
    switch (color) {
    case BrushColor::Default: return QBrush(QColor(0, 0, 255), Qt::Dense6Pattern);
    case BrushColor::Selected: return QBrush(QColor(127, 255, 0), Qt::Dense6Pattern);
    }
}

void UvGraphicsView::setImage(const QImage &image)
{
    imageItem->setPixmap(QPixmap::fromImage(image));
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

void UvGraphicsView::setEditMaskMode(bool value)
{
    editMaskMode = value;
}

void UvGraphicsView::setShowMaskMode(bool value)
{
    showMaskMode = value;
    for (const auto rectItem : rectItems) {
        rectItem->setVisible(showMaskMode);
    }
}

//TODO Починить сделать возможность переключения маштабирования
void UvGraphicsView::setResizeMode(bool value)
{
    resizeMode = value;
    resizeImage();
}

void UvGraphicsView::resizeImage()
{
    resetMatrix();
    if (resizeMode){
        fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
    }
}

// ======================== Slots ========================
void UvGraphicsView::removeItemRect(QRectF rect)
{
    QGraphicsRectItem *removeItem = nullptr;
    for (auto item : rectItems){
        if (item->rect() == rect)
            removeItem = item;
    }
    if (removeItem){
        rectItems.removeOne(removeItem);
        scene.removeItem(removeItem);
        delete removeItem;
    }
}

void UvGraphicsView::selectItemRect(QRectF rect)
{
    for (auto item : rectItems) {
       item->rect() == rect ? selectItem(item) : unselectItem(item);
    }
}
// ========================================================

// ===================== Select items group =========================
void UvGraphicsView::selectGraphicsItem(QPointF point)
{
    for (auto item : rectItems) {
        item->contains(point) ? selectItem(item) : unselectItem(item);
    }
}

void UvGraphicsView::selectItem(QGraphicsRectItem *rectItem)
{
    rectItem->setSelected(true);
    rectItem->setBrush(getBrush(BrushColor::Selected));
    emit rectSelected(rectItem->rect());
}

void UvGraphicsView::unselectItem(QGraphicsRectItem *rectItem)
{
    rectItem->setSelected(false);
    rectItem->setBrush(getBrush(BrushColor::Default));
}
//====================================================================


