#ifndef COLORSELECTIONFORM_H
#define COLORSELECTIONFORM_H

#include <QWidget>
#include <QDebug>
#include "abstractsettingstab.h"
#include "settingkeeper.h"
#include "contourfiltersettings.h"

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
    void on_selectColorOnImagePushButton_clicked(bool checked);
    void getChanelValue(int value);

private:
    Ui::ColorSelectionForm *ui;
    QColor currentColor;
};

#endif // COLORSELECTIONFORM_H
