#include "labelevent.h"

LabelEvent::LabelEvent(QWidget *parent,
                       Qt::AspectRatioMode aspectRatioMode,
                       Qt::TransformationMode transformMode) :
    QLabel(parent),
    m_imageAspectRatioMode(aspectRatioMode),
    m_imageTransformationMode(transformMode)
{
    this->setMinimumSize(1, 1);
    setScaledContents(false);
}

LabelEvent::~LabelEvent()
{
    // empty
}

int LabelEvent::heightForWidth(int width) const
{
     return m_image.isNull() ? this->height()
                             : ((qreal)m_image.height() * width) / m_image.width();
}

QSize LabelEvent::sizeHint() const
{
    int w = this->width();
    return QSize(w, heightForWidth(w));
}

const QImage &LabelEvent::image() const
{
    return m_image;
}

void LabelEvent::setImage(const QImage &image)
{
    m_image = image;
    if (image.isNull())
    {
        clear();
        return;
    }
    redrawImage(image);
}

void LabelEvent::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    if (!m_image.isNull())
    {
        redrawImage(m_image);
    }
}



// Do not forget about
// turning ON the 'mouse tracking' parameter on the form
void LabelEvent::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();

    if (pos.x() <= this->size().width() && pos.y() <= this->size().height())
    {
        if (pos.x() >= 0 && pos.y() >= 0)
        {
            emit mousePos(pos);
        }
    }
}

void LabelEvent::mousePressEvent(QMouseEvent *event)
{
    auto key = event->button();

    if (key == Qt::LeftButton)
    {
        QPoint pos = event->pos();
//        setFocus();
        emit leftButtonPressed(pos);
        QPoint posNew;
        if (isOnImage(pos, &posNew))
        {
            emit imageClicked(posNew);
        }
    }
}

void LabelEvent::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event);
}

void LabelEvent::redrawImage(const QImage &image)
{
    QSize lblSize = QLabel::size();
    QPixmap pixmap = QPixmap::fromImage(image.scaled(lblSize, m_imageAspectRatioMode, m_imageTransformationMode));
    QLabel::setPixmap(pixmap);
}

bool LabelEvent::isOnImage(const QPoint &pos, QPoint *posNew)
{
    const QPixmap *pixmap = QLabel::pixmap();
    if (pixmap == nullptr)
    {
        return false;
    }
    QImage image = pixmap->toImage();
    QPoint posNoOffset = removeLabelOffset(pos, this, image);

    bool onImage = ::isOnImage(posNoOffset, image);
    if (onImage)
    {
        if (posNew != nullptr)
        {
            float multipleX = this->image().width()  / (float)image.width();
            float multipleY = this->image().height() / (float)image.height();
            posNoOffset.setX(posNoOffset.x() * multipleX);
            posNoOffset.setY(posNoOffset.y() * multipleY);

            *posNew = posNoOffset;
        }
    }
    return onImage;
}

Qt::AspectRatioMode LabelEvent::imageAspectRatioMode() const
{
    return m_imageAspectRatioMode;
}

void LabelEvent::setImageAspectRatioMode(const Qt::AspectRatioMode &imageAspectRatioMode)
{
    m_imageAspectRatioMode = imageAspectRatioMode;
}

Qt::TransformationMode LabelEvent::imageTransformationMode() const
{
    return m_imageTransformationMode;
}

void LabelEvent::setImageTransformationMode(const Qt::TransformationMode &imageTransformationMode)
{
    m_imageTransformationMode = imageTransformationMode;
}

QPoint LabelEvent::convertToImageCoords(QPoint pt) const
{
    using ZoomType = float;
    const QPixmap *pm = QLabel::pixmap();
    if (!pm || image().isNull())
    {
        return pt;
    }
    pt = removeLabelOffset(pt, this, image());

    ZoomType zoomX = image().width() / static_cast<ZoomType>(pm->width());
    ZoomType zoomY = image().height() / static_cast<ZoomType>(pm->height());
    //int offsetX = (width() - pm->width()) / 2;
    //int offsetY = (height() - pm->height()) / 2;

    pt.setX((pt.x()) * zoomX);
    pt.setY((pt.y()) * zoomY);

    return pt;
}


QPoint removeLabelOffset(QPoint pos, const QLabel *label, const QImage &image)
{
    const QPixmap *pm = label->pixmap();
    if (!pm)
    {
        return pos;
    }

    if (label->alignment() & Qt::AlignHCenter)
    {
        int xOffset = pos.x() - ((label->width() - pm->width()) / 2);
        pos.setX(xOffset);
    }
    if (label->alignment() & Qt::AlignVCenter)
    {
        int yOffset = pos.y() - ((label->height() - pm->height()) / 2);
        pos.setY(yOffset);
    }

    return pos;
}

bool isOnImage(const QPoint pos, const QImage &image)
{
    if (pos.x() < image.width() && pos.y() < image.height())
    {
        if (pos.x() >= 0 && pos.y() >= 0)
        {
            return true;
        }
    }

    return false;
}
