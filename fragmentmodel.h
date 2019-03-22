#ifndef FRAGMENTMODEL_H
#define FRAGMENTMODEL_H

#include <QAbstractTableModel>

#include "fragmentinfo.h"

class FragmentModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit FragmentModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addFragment(const FragmentInfo &fragment);

private:
    QStringList headers {"Состяние", "Кадры", "Опоры", "Время", "Номер в отчёте"};
    QList<FragmentInfo> fragments;
};

#endif // FRAGMENTMODEL_H
