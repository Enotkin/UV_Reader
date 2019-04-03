#ifndef FRAGMENTMODEL_H
#define FRAGMENTMODEL_H

#include <QAbstractTableModel>
#include <QFlags>
#include <algorithm>
#include <functional>

#include "fragmentinfo.h"


class FragmentModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit FragmentModel(QObject *parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index)const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool isContainsVideoFragment();
    bool isEmpty();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    void addFragment(const FragmentInfo &fragment);
    void removeFragment(const QModelIndexList modelIdexesList);
    void clearModel();
    QList<FragmentInfo> getSelectedFragments() const;

private:
    QStringList headers {"", "Состяние", "Кадры", "Опоры", "Время", "Номер в отчёте"};
    QList<FragmentInfo> fragments;
    QList<Qt::CheckState> fragmentsCheckState;
};

#endif // FRAGMENTMODEL_H
