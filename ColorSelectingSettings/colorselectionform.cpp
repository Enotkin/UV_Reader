#include "colorselectionform.h"
#include "ui_colorselectionform.h"

ColorSelectionForm::ColorSelectionForm(QWidget *parent) :
    AbstractSettingsTab (parent),
    ui(new Ui::ColorSelectionForm)
{
    ui->setupUi(this);
    ui->widgetColorSelect->setVisible(false);
}

ColorSelectionForm::~ColorSelectionForm()
{
    delete ui;
}

void ColorSelectionForm::setWorkState(bool state)
{
    state ? activate() : deactivate();
}

void ColorSelectionForm::setColor(QColor color)
{
    currentColor = color.toRgb();
    displayColor(color);
    currentColorSelector->setColor(color);
}

void ColorSelectionForm::activate()
{
    auto settings = SettingKeeper::getInstance()->loadFilterSettings();
    currentColor = settings.color;
    setFilterMode(static_cast<FilterType>(settings.mode));
}

void ColorSelectionForm::deactivate()
{
    FilterSettings settings{currentColor,
                static_cast<FilterType>(ui->comboBoxFilterType->currentIndex())};
    SettingKeeper::getInstance()->saveContourFilterSettings(settings);
}

void ColorSelectionForm::displayColor(QColor color)
{   
    QPixmap colorImage(ui->labelViewColor->rect().width(), ui->labelViewColor->rect().height());
    colorImage.fill(color);
    ui->labelViewColor->setPixmap(colorImage);

    auto colorName = QString("%1%2%3").arg(color.red(), 0, 16).arg(color.green(), 0, 16).arg(color.blue(), 0, 16);
    ui->labelNameColor->setText(colorName);

    if(currentColorSelector)
        currentColorSelector->setColor(color);
}

void ColorSelectionForm::on_comboBoxFilterType_activated(int index)
{
    setFilterMode(static_cast<FilterType>(index));
}

void ColorSelectionForm::activateNormalMode()
{
    ui->comboBoxFilterType->setCurrentIndex(static_cast<int>(FilterType::Normal));
    ui->widgetColorSelect->hide();
    displayColor(QColor(Qt::white).toRgb());
}

void ColorSelectionForm::activateColorfullMode()
{
    ui->comboBoxFilterType->setCurrentIndex(static_cast<int>(FilterType::Colorfull));
    ui->widgetColorSelect->show();
    displayColor(currentColor.toRgb());


    if (currentColorSelector){
        currentColorSelector->disconnect();
        ui->layoutColorSelector->removeWidget(currentColorSelector);
        delete currentColorSelector;
    }
    currentColorSelector = new ColorSelectorRgb();
    currentColorSelector->setColor(currentColor);
    connect(currentColorSelector, &ColorSelector::colorChanged, this, &ColorSelectionForm::displayColor);
    ui->layoutColorSelector->addWidget(currentColorSelector);
}

void ColorSelectionForm::on_comboBoxColorSpace_currentIndexChanged(int index)
{
    if (currentColorSelector){
        currentColorSelector->disconnect();
        ui->layoutColorSelector->removeWidget(currentColorSelector);
        delete currentColorSelector;
    }
    switch (static_cast<ColorMode>(index)) {
    case ColorMode::RGB:
        currentColorSelector = new ColorSelectorRgb();
        break;
    case ColorMode::HSV:
        currentColorSelector = new ColorSelectorHsv();
        break;
    }
    currentColorSelector->setColor(currentColor);
    connect(currentColorSelector, &ColorSelector::colorChanged, this, &ColorSelectionForm::displayColor);
    ui->layoutColorSelector->addWidget(currentColorSelector);
}

void ColorSelectionForm::setFilterMode(FilterType type)
{
    switch (type) {
    case FilterType::Normal: activateNormalMode(); break;
    case FilterType::Colorfull: activateColorfullMode(); break;
    }
}

void ColorSelectionForm::on_pushButtonSelectColorOnImage_clicked(bool checked)
{
    emit turnOnColorSelection(checked);
}
