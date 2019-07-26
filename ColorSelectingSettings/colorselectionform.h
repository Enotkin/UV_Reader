#ifndef COLORSELECTIONFORM_H
#define COLORSELECTIONFORM_H

#include <QWidget>
#include <QDebug>
#include <optional>
#include "abstractsettingstab.h"
#include "settingkeeper.h"
#include "contourfiltersettings.h"
#include "colorselectorhsv.h"
#include "colorselectorrgb.h"

namespace Ui {
class ColorSelectionForm;
}

class ColorSelectionForm : public AbstractSettingsTab
{
    Q_OBJECT

public:
    explicit ColorSelectionForm(QWidget *parent = nullptr);
    ~ColorSelectionForm() override;

    void setWorkState(bool state) override final;

signals:
    void turnOnColorSelection(bool);

public slots:
    void setColor(QColor color);

private slots:
    void on_comboBoxFilterType_activated(int index);

    void on_comboBoxColorSpace_currentIndexChanged(int index);

    void on_pushButtonSelectColorOnImage_clicked(bool checked);

private:
    enum class FilterType{
      Normal,
      Colorfull
    };

    enum class ColorMode{
        RGB,
        HSV
    };

    Ui::ColorSelectionForm *ui;
    QColor currentColor;

    ColorMode colorMode = ColorMode::RGB;


    void displayColor(QColor color);

    ColorSelector *currentColorSelector = nullptr;
    void setFilterMode(FilterType type);

    void activateNormalMode();
    void activateColorfullMode();

    void activate();
    void deactivate();
};

#endif // COLORSELECTIONFORM_H
