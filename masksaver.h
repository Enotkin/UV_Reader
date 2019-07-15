#ifndef MASKSAVER_H
#define MASKSAVER_H
#include <QSettings>
#include <QVector>
#include <QRectF>
#include <optional>

class MaskSaver
{
public:
    MaskSaver();
    void saveMasks(QString fileName, QVector<QRectF> rects);
    std::optional<QVector<QRectF>> loadMasks(QString fileName);

private:
    const QString masksFileName = "Saved_mask.ini";
    QSettings settings;

    void clearGroup(QString groupName);
};

#endif // MASKSAVER_H
