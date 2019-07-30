#ifndef SETTINGKEEPER_H
#define SETTINGKEEPER_H

#include <QSettings>
#include <QFileInfo>
#include <QColor>
#include <optional>
#include <QDebug>

#include <masksaver.h>
#include <filtersettings.h>


class SettingKeeper
{
public:
    ~SettingKeeper();
    static SettingKeeper *getInstance(){
        if (!p_instance)
            p_instance = new SettingKeeper();
        return p_instance;
    }

    void setCurrentFile(const QFileInfo &value);
    std::optional<QFileInfo> getCurrentFile() const;

    void saveMasks(Masks rects);
    Masks loadMask();

    void saveContourFilterSettings(FilterSettings settings);
    FilterSettings loadFilterSettings();

    void saveDefaultPath(QString path);
    std::optional<QString> loadDefaultPath();

private:
    SettingKeeper();
    SettingKeeper( const SettingKeeper& );
    SettingKeeper& operator = ( SettingKeeper& );
    static SettingKeeper *p_instance;


    const QString MainSettingsFileName = "Settings.ini";
    const QString MaskSettingsFileName = "Saved_mask.ini";
    QSettings mainSettings;
    MaskSaver maskSettings;
    std::optional<QFileInfo> currentFile;
};

#endif // SETTINGKEEPER_H
