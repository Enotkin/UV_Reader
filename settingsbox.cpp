#include "settingsbox.h"
#include "ui_settingsbox.h"

SettingsBox::SettingsBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsBox)
{
    ui->setupUi(this);
    this->hide();
    currentIndex = ui->tabWidget->currentIndex();
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &SettingsBox::tabChanged);
}

SettingsBox::~SettingsBox()
{
    delete ui;
}

void SettingsBox::showTabs(SettingsMode mode)
{
    auto newIndex = static_cast<int>(mode);
    if (this->isHidden())
        this->show();
    auto currentTab = dynamic_cast<AbstractSettingsTab*>(ui->tabWidget->currentWidget());
    if (newIndex == ui->tabWidget->currentIndex()){
        currentTab->setWorkState(true);
    } else {
        currentTab->setWorkState(false);
        auto newTab = dynamic_cast<AbstractSettingsTab*>(ui->tabWidget->widget(newIndex));
        newTab->setWorkState(true);
        ui->tabWidget->setCurrentIndex(newIndex);
    }
}

void SettingsBox::hideTabs()
{
    auto currentTab = dynamic_cast<AbstractSettingsTab*>(ui->tabWidget->currentWidget());
    currentTab->setWorkState(false);
    this->hide();
}

MaskCreateForm *SettingsBox::getMaskWidget()
{
    return dynamic_cast<MaskCreateForm*>(ui->tabWidget->widget(0));
}

ColorSelectionForm *SettingsBox::getColorWidget()
{
    return dynamic_cast<ColorSelectionForm*>(ui->tabWidget->widget(static_cast<int>(SettingsMode::ColorMode)));
}

void SettingsBox::tabChanged(int index)
{
    auto newTab = dynamic_cast<AbstractSettingsTab*>(ui->tabWidget->widget(currentIndex));
    newTab->setWorkState(false);
    currentIndex = ui->tabWidget->currentIndex();

    auto currentTab = dynamic_cast<AbstractSettingsTab*>(ui->tabWidget->currentWidget());
    currentTab->setWorkState(true);
}
