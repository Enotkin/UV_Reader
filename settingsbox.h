#ifndef SETTINGSBOX_H
#define SETTINGSBOX_H

#include <QWidget>
#include <QDebug>

#include "maskcreateform.h"
#include "colorselectionform.h"

enum class SettingsMode {
    MaskMode,
    ColorMode
};

namespace Ui {
class SettingsBox;
}

class SettingsBox : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsBox(QWidget *parent = nullptr);
    ~SettingsBox();

    void showTabs(SettingsMode mode);
    void hideTabs();
    MaskCreateForm* getMaskWidget();
    ColorSelectionForm* getColorWidget();

private slots:
    void tabChanged(int index);

private:
    Ui::SettingsBox *ui;
    int currentIndex = 0;

};

#endif // SETTINGSBOX_H
