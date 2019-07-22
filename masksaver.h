#ifndef MASKSAVER_H
#define MASKSAVER_H
#include <QSettings>
#include <QVector>
#include <QRectF>
#include <optional>

using Masks = QVector<QRectF>;

class MaskSaver
{
public:
    MaskSaver(QString mainFileName);
    void saveMasks(QString fileName, Masks rects);
    Masks loadMasks(QString fileName);

private:
    QSettings settings;

    void clearGroup(QString groupName);
};

#endif // MASKSAVER_H
