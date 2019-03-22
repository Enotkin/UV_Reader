#include "fragmentmodel.h"

FragmentModel::FragmentModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    fragments.append(FragmentInfo(64, "434D", QTime(0,3,4,0), "добвлено"));
    fragments.append(FragmentInfo(43, "423r", QTime(0,33,4,0), "добвлено"));
    fragments.append(FragmentInfo(12, "4T", QTime(0,3,34,0), "добвлено"));
}

QVariant FragmentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return headers.at(section);
    else
        return QVariant();
}

int FragmentModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return fragments.count();
}

int FragmentModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return headers.count();
}

QVariant FragmentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole){
        switch (index.column()) {
        case 0:
            return fragments.at(index.row()).getStatus();
        case 1:
            return fragments.at(index.row()).getFrameRange().first;
        case 2:
            return fragments.at(index.row()).getPillarRange().first;
        case 3:
            return fragments.at(index.row()).getTime().first.toString("hh:mm:ss");
        case 4:
            return fragments.at(index.row()).getFrameNumberReport();
        }
    } else {
        return QVariant();
    }
}

void FragmentModel::addFragment(const FragmentInfo &fragment)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    fragments.append(fragment);
    endInsertRows();
}
