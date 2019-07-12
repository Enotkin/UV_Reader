#ifndef MASKCREATEFORM_H
#define MASKCREATEFORM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QDebug>
using RerctItem = QPair<QRectF, QListWidgetItem*>;

namespace Ui {
class maskCreateForm;
}

class MaskCreateForm : public QWidget
{
    Q_OBJECT

public:
    explicit MaskCreateForm(QWidget *parent = nullptr);
    ~MaskCreateForm();

signals:
    void itemSelected(QRectF);
    void itemRemoved(QRectF);
    void setEditMode(bool);
    void clearAll();

public slots:
    void addItem(QRectF rect);
    void selectItem(QRectF rect);

private slots:
    void on_listWidgetDeathAreas_itemClicked(QListWidgetItem *item);

    void on_pushButtonRemoveDeathArea_clicked();

    void on_pushButtonClearDeathArea_clicked();

private:
    Ui::maskCreateForm *ui;
    QRectF selectedRect = QRectF();
    QList <RerctItem> areas;

    QString rect2String(const QRectF &rect) const;
    QListWidgetItem *getListItem (const QRectF &rect) const;
    QRectF getRectF(const QListWidgetItem *item) const;
    void removeItem(QRectF rect);
};

#endif // MASKCREATEFORM_H
