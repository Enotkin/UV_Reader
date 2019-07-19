#include "masksaver.h"

MaskSaver::MaskSaver(QString mainFileName) : settings(mainFileName, QSettings::IniFormat)
{

}

void MaskSaver::saveMasks(QString fileName, Masks rects)
{
    if (settings.childGroups().contains(fileName))
        clearGroup(fileName);

    settings.beginGroup(fileName);
    int index = 0;
    for (auto rect : rects) {
        settings.setValue(QString::number(index++), rect);
    }
    settings.endGroup();
    settings.sync();
}

std::optional<Masks> MaskSaver::loadMasks(QString fileName)
{
    if (!settings.childGroups().contains(fileName)) {
        return std::nullopt;
    }
    settings.beginGroup(fileName);
    QVector<QRectF> rectss;
    for (auto key : settings.childKeys()) {
        auto ss = settings.value(key).toRectF();
        rectss.append(ss);
    }
    return std::optional<QVector<QRectF>>(rectss);
}

void MaskSaver::clearGroup(QString groupName)
{
    settings.beginGroup(groupName);
    for (auto key : settings.childKeys()) {
        settings.remove(key);
    }
    settings.endGroup();
    settings.sync();
}
