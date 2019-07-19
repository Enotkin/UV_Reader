#ifndef MASKCREATEFORM_H
#define MASKCREATEFORM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QDebug>
#include <QSettings>
#include <optional>
#include "abstractsettingstab.h"

using RerctItem = QPair<QRectF, QListWidgetItem*>;

namespace Ui {
class maskCreateForm;
}

class MaskCreateForm : public AbstractSettingsTab
{
    Q_OBJECT

public:
    explicit MaskCreateForm(QWidget *parent = nullptr);
    ~MaskCreateForm() override;
    void setWorkState(bool state) override final;

signals:
    void itemSelected(QRectF);
    void itemRemoved(QRectF);
    void setEditMode(bool);
    void setShowMode(bool);
    void clearAll();

public slots:
    void addItem(QRectF rect);
    void selectItem(QRectF rect);

private slots:
    void on_listWidgetDeathAreas_itemClicked(QListWidgetItem *item);

    void on_pushButtonRemoveDeathArea_clicked();

    void on_pushButtonClearDeathArea_clicked();

    void on_pushButtonAddDeathArea_clicked(bool checked);

private:
    Ui::maskCreateForm *ui;
    QRectF selectedRect = QRectF();
    QList <RerctItem> areas;

    QString rect2String(const QRectF &rect) const;
    QListWidgetItem *getListItem (const QRectF &rect) const;
    QRectF getRectF(const QListWidgetItem *item) const;
    void removeItem(QRectF rect);
    void saveMask();
};

#endif // MASKCREATEFORM_H
