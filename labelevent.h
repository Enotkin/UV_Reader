#ifndef LABELEVENT_H
#define LABELEVENT_H

// -----------------
//    Description
// -----------------
//
// QLabel but with events
//  [And image on it]
//

// ------------------------
//    Standard libraries
// ------------------------
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QImage>


// [QImage -> QLabel] expand problem
// >> Solution:
//    Ui, form -> Size Policy:
//                Ignored, Ignored
class LabelEvent : public QLabel
{
    Q_OBJECT
public:
    LabelEvent(QWidget *parent = nullptr,
               Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio,
               Qt::TransformationMode transformMode = Qt::SmoothTransformation);
    virtual ~LabelEvent();
    virtual int heightForWidth(int width) const;
    virtual QSize sizeHint() const;

    const QImage &image() const;
    Qt::AspectRatioMode imageAspectRatioMode() const;
    Qt::TransformationMode imageTransformationMode() const;

    void setImageAspectRatioMode(const Qt::AspectRatioMode &imageAspectRatioMode);
    void setImageTransformationMode(const Qt::TransformationMode &imageTransformationMode);

    QPoint convertToImageCoords(QPoint pt) const;

signals:
    void mousePos(QPoint &point);           // Cursor position
    void keyPressed(QKeyEvent *event);      // Keyboard pressed
    void leftButtonPressed(QPoint &point);  // Left mouse button pressed
    void imageClicked(QPoint &point);       // Clicked on image by left mouse button

public slots:
    void setImage(const QImage &image);
    void resizeEvent(QResizeEvent *event);

protected:
    void mouseMoveEvent(QMouseEvent *event);    // Mouse movement
    void mousePressEvent(QMouseEvent *event);   // Mouse's clicks
    void keyPressEvent(QKeyEvent *event);       // Keyboard inputs

    void redrawImage(const QImage &image);
    bool isOnImage(const QPoint &pos, QPoint *posNew = nullptr);

private:
    QImage m_image;
    Qt::AspectRatioMode m_imageAspectRatioMode;
    Qt::TransformationMode m_imageTransformationMode;
};

QPoint removeLabelOffset(QPoint pos, const QLabel *label, const QImage &image);
bool isOnImage(const QPoint pos, const QImage &image);

#endif // LABELEVENT_H
