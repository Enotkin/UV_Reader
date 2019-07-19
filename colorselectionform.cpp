#include "colorselectionform.h"
#include "ui_colorselectionform.h"

ColorSelectionForm::ColorSelectionForm(QWidget *parent) :
    AbstractSettingsTab (parent),
    ui(new Ui::ColorSelectionForm)
{
    ui->setupUi(this);
    connect(ui->redSlider, &QSlider::valueChanged, this, &ColorSelectionForm::getChanelValue);
    connect(ui->greenSlider, &QSlider::valueChanged, this, &ColorSelectionForm::getChanelValue);
    connect(ui->blueSlider, &QSlider::valueChanged, this, &ColorSelectionForm::getChanelValue);
}

ColorSelectionForm::~ColorSelectionForm()
{
    delete ui;
}

void ColorSelectionForm::setWorkState(bool state)
{
    if (state){
        auto newSettings = SettingKeeper::getInstance()->loadContourFilterSettings();
        if (newSettings){
            setColor(newSettings->color);
            ui->comboBox->setCurrentIndex(static_cast<int>(newSettings->mode));
        }else {
            ContourFilterSettings defaultSettings;
            setColor(defaultSettings.color);
            ui->comboBox->setCurrentIndex(static_cast<int>(defaultSettings.mode));
        }
    } else {
        ui->selectColorOnImagePushButton->setChecked(true);
        ContourFilterSettings settings{currentColor,
                    static_cast<ContourFilterSettings::FilterContourMode>(ui->comboBox->currentIndex())};
        SettingKeeper::getInstance()->saveContourFilterSettings(settings);
    }
}

void ColorSelectionForm::setColor(QColor color)
{
    ui->redSlider->setValue(color.red());
    ui->greenSlider->setValue(color.green());
    ui->blueSlider->setValue(color.blue());

    QPixmap colorImage(ui->viewColorLabel->rect().width(),ui->viewColorLabel->rect().height());
    colorImage.fill(color);
    ui->viewColorLabel->setPixmap(colorImage);

    auto colorName = QString("%1%2%3").arg(color.red(), 0, 16).arg(color.green(), 0, 16).arg(color.blue(), 0, 16);
    ui->nameColorLabel->setText(colorName);
}

void ColorSelectionForm::on_selectColorOnImagePushButton_clicked(bool checked)
{
    emit turnOnColorSelection(checked);
}

void ColorSelectionForm::getChanelValue(int value)
{
    int red = ui->redSlider->value();
    int green = ui->greenSlider->value();
    int blue = ui->blueSlider->value();
    setColor(QColor(red, green, blue));
}
