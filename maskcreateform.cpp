#include "maskcreateform.h"
#include "ui_maskcreateform.h"

MaskCreateForm::MaskCreateForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::maskCreateForm)
{
    ui->setupUi(this);
    this->hide();
}

MaskCreateForm::~MaskCreateForm()
{
    delete ui;
}

void MaskCreateForm::addItem(QRectF rect)
{
    auto item = new QListWidgetItem(rect2String(rect));
    areas.push_back(RerctItem(rect, item));
    ui->listWidgetDeathAreas->addItem(item);
}

void MaskCreateForm::selectItem(QRectF rect)
{
    if (!selectedRect.isNull())
        getListItem(selectedRect)->setSelected(true);
    selectedRect = rect;
    getListItem(selectedRect)->setSelected(true);
}

void MaskCreateForm::removeItem(QRectF rect)
{
    if (selectedRect == rect){
        getListItem(selectedRect)->setSelected(false);
        selectedRect = QRectF();
    }
    ui->listWidgetDeathAreas->removeItemWidget(getListItem(rect));
    delete getListItem(rect);
    areas.removeOne(RerctItem(rect, getListItem(rect)));
    emit itemRemoved(rect);
}

void MaskCreateForm::saveMask()
{

}

void MaskCreateForm::on_listWidgetDeathAreas_itemClicked(QListWidgetItem *item)
{
    selectedRect = getRectF(item);
    emit itemSelected(selectedRect);
}

void MaskCreateForm::on_pushButtonRemoveDeathArea_clicked()
{
    if (!selectedRect.isNull())
        removeItem(selectedRect);
}

void MaskCreateForm::on_pushButtonClearDeathArea_clicked()
{
    for (auto [rect, item] : areas){
        ui->listWidgetDeathAreas->removeItemWidget(item);
        delete item;
    }
    areas.clear();
    emit clearAll();
}

QRectF MaskCreateForm::getRectF(const QListWidgetItem *item) const
{
    for (auto [localRect, localItem] : areas) {
        if (localItem == item){
            return localRect;
        }
    }
    return QRectF();
}

QListWidgetItem *MaskCreateForm::getListItem(const QRectF &rect) const
{
    for (auto [localRect, item] : areas) {
        if (localRect == rect){
            return item;
        }
    }
    return nullptr;
}

QString MaskCreateForm::rect2String(const QRectF &rect) const
{
    return QString("(%1, %2)(%3, %4)").arg(QString::number(rect.toRect().topLeft().x()))
            .arg(QString::number(rect.toRect().topLeft().y()))
            .arg(QString::number(rect.toRect().topLeft().x() + rect.toRect().width()))
            .arg(QString::number(rect.toRect().topLeft().y() + rect.toRect().width()));
}

void MaskCreateForm::on_pushButtonAddDeathArea_clicked(bool checked)
{
    emit setEditMode(checked);
}
