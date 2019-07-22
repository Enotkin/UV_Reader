#include "settingkeeper.h"

SettingKeeper *SettingKeeper::p_instance = nullptr;

SettingKeeper::SettingKeeper() :
    mainSettings(MainSettingsFileName, QSettings::IniFormat),
    maskSettings(MaskSettingsFileName) {}

std::optional<QFileInfo> SettingKeeper::getCurrentFile() const
{
    return currentFile;
}

void SettingKeeper::setCurrentFile(const QFileInfo &value)
{
    currentFile = value;
    saveDefaultPath(currentFile->path());
}

void SettingKeeper::saveMasks(Masks rects)
{
    maskSettings.saveMasks(currentFile->baseName(), rects);
}

Masks SettingKeeper::loadMask()
{
    auto ss = maskSettings.loadMasks(currentFile->baseName());
    return ss;
}

void SettingKeeper::saveContourFilterSettings(ContourFilterSettings settings)
{
    mainSettings.beginGroup("Contour_Filter_Settings");
    mainSettings.setValue("Filter_mode", static_cast<int>(settings.mode));
    mainSettings.setValue("Color", settings.color);
    mainSettings.endGroup();
}

std::optional<ContourFilterSettings> SettingKeeper::loadContourFilterSettings()
{
    if (!mainSettings.childGroups().contains("Contour_Filter_Settings"))
        return std::nullopt;
    ContourFilterSettings settings;
    mainSettings.beginGroup("Contour_Filter_Settings");
    settings.mode =static_cast<ContourFilterSettings::FilterContourMode>(mainSettings.value("Filter_mode").toInt());
    auto variantColor = mainSettings.value("Color");
    settings.color = variantColor.value<QColor>();
    std::optional<ContourFilterSettings> result = settings;
    return result;
}

void SettingKeeper::saveDefaultPath(QString path)
{
    mainSettings.setValue("Default_Path", path);
}

std::optional<QString> SettingKeeper::loadDefaultPath()
{
    QString path = mainSettings.value("Default_Path").toString();
    return !path.isNull() ? std::optional<QString>(path) : std::nullopt;
}


