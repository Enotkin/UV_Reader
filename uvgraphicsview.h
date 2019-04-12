#ifndef UVGRAPHICSVIEW_H
#define UVGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>

class UvGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    UvGraphicsView(QWidget *parent);

    void setResizeMode(bool value);

    void setEditMode(bool value);

    bool getResizeMode() const;

protected:
    void mousePressEvent(QMouseEvent *event) override final;
    void mouseMoveEvent(QMouseEvent *event) override final;
    void paintEvent(QPaintEvent *event) override final;

private:
    bool editMode = false;
    bool resizeMode = true;
};

#endif // UVGRAPHICSVIEW_H
