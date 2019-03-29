#ifndef FRAGMENTMODEL_H
#define FRAGMENTMODEL_H

#include <QAbstractTableModel>
#include <QFlags>
#include <algorithm>
#include <functional>

#include "fragmentinfo.h"

//namespace Filters {
//    enum Flags {
//        VideoFragmentsOnly,
//        FrameFragmentsoOnly,
//        AllFragments,
//        Selected
//    };
//    Q_DECLARE_FLAGS(FiltersFlags, Flags)
//}
//Q_DECLARE_OPERATORS_FOR_FLAGS(Filters::FiltersFlags)


class FragmentModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Filters {
        VideoFragments,
        FrameFragments,
        AllFragments,
        Selected
    };
    Q_DECLARE_FLAGS(FiltersFlags, Filters)


    explicit FragmentModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index)const override;

    void addFragment(const FragmentInfo &fragment);
    void removeFragment(const QModelIndexList modelIdexesList);
    void clearModel();

    QList<FragmentInfo> getFragments(FiltersFlags filters = AllFragments) const;

    bool isContainsVideoFragment();
    bool isEmpty();


private:
//    struct Fragment {
//        Fragment(FragmentInfo info, Qt::CheckState state)
//            : isSelected(state), info(info) {}
//        Qt::CheckState isSelected;
//        FragmentInfo info;
//    };

    QStringList headers {"", "Состяние", "Кадры", "Опоры", "Время", "Номер в отчёте"};
//    QList<FragmentInfo *> selectedFraments;
    std::list<std::reference_wrapper<FragmentInfo> > ss;

    QList<FragmentInfo> fragments;
//    QList<Fragment> fragments;

};

Q_DECLARE_OPERATORS_FOR_FLAGS(FragmentModel::FiltersFlags)

#endif // FRAGMENTMODEL_H
