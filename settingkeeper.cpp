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

void SettingKeeper::saveContourFilterSettings(FilterSettings settings)
{
    mainSettings.beginGroup("Contour_Filter_Settings");

    mainSettings.setValue("Filter_mode", static_cast<int>(settings.mode));
    mainSettings.setValue("Color", settings.color.rgb());
    mainSettings.endGroup();
}

FilterSettings SettingKeeper::loadContourFilterSettings()
{
    FilterSettings settings;
    if (!mainSettings.childGroups().contains("Contour_Filter_Settings"))
        return settings;

    mainSettings.beginGroup("Contour_Filter_Settings");

    settings.mode =static_cast<FilterType>(mainSettings.value("Filter_mode").toInt());
    auto variantRgb = mainSettings.value("Color");
    auto rgb = variantRgb.toUInt();
    settings.color = QColor::fromRgb(rgb);

    mainSettings.endGroup();
    return settings;
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


