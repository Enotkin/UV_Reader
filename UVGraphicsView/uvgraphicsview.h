#ifndef UVGRAPHICSVIEW_H
#define UVGRAPHICSVIEW_H

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>
#include <QSettings>
#include <QTime>

#include <forward_list>
#include <memory>
#include <optional>

#include "masksaver.h"
#include "rectitembuilder.h"
#include "settingkeeper.h"

enum class BrushColor {Default, Selected};

class UvGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    UvGraphicsView(QWidget *parent);
    ~UvGraphicsView() override;

    void setResizeMode(bool value);

    void setImage(const QImage &image);

    QList<QRect> getMaskRect() const;

    void setFileName(QString value);

    void resizeImage();

signals:
    void rectSelected(QRectF rect);
    void addRect(QRectF rect);
    void colorSelected(QColor);

public slots:
    void setEditMaskMode(bool value);
    void setShowMaskMode(bool value);
    void setColorSelectionMode(bool value);
    void removeItemRect(QRectF rect);
    void selectItemRect(QRectF rect);
    void clearMasks();

protected:
    void mousePressEvent(QMouseEvent *event) override final;
    void mouseMoveEvent(QMouseEvent *event) override final;
    void mouseReleaseEvent(QMouseEvent *event) override final;

private:
    QGraphicsScene scene;
    QList<QGraphicsRectItem*> rectItems;
    QString fileName;
    std::unique_ptr<QGraphicsPixmapItem> imageItem;
    std::optional<RectItemBuilder> rectItemBuilder;
    std::optional<QSettings> settings;
    bool showMaskMode = false;
    bool editMaskMode = false;
    bool colorSelectionMode = false;
    bool resizeMode = true;

    bool sceneBorderCheck(const QPoint &point) const;
    void selectItem(QGraphicsRectItem* rectItem);
    void unselectItem(QGraphicsRectItem* rectItem);
    QBrush getBrush(const BrushColor color);
    void selectGraphicsItem(QPointF point);
    void loadMask();
    void saveMask();
    void maskActions(QPointF pos);
    void colorActions(QPointF pos);
};

#endif // UVGRAPHICSVIEW_H
