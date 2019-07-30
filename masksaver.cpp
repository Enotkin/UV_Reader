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

Masks MaskSaver::loadMasks(QString fileName)
{
    QVector<QRectF> rectss;
    if (!settings.childGroups().contains(fileName)) {
        return rectss;
    }
    settings.beginGroup(fileName);

    for (auto key : settings.childKeys()) {
        auto ss = settings.value(key).toRectF();
        rectss.append(ss);
    }
    settings.endGroup();
    return rectss;
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
