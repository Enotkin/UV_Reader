#include "fragmentmodel.h"

FragmentModel::FragmentModel(QObject *parent)
    : QAbstractTableModel(parent)
{

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
    if (role == Qt::CheckStateRole && index.column() == 0){
        return fragmentsCheckState.at(index.row());
    }
    if (role == Qt::DisplayRole){
        switch (index.column()) {
        case 1:
            return fragments.at(index.row()).getStatus();
        case 2:
            return fragments.at(index.row()).getFrameRangeString();
        case 3:
            return fragments.at(index.row()).getPillarRangeString();
        case 4:
            return fragments.at(index.row()).getTimeString();
        case 5:
            return fragments.at(index.row()).getFrameNumberReport();
        }
    }
    return QVariant();

}

bool FragmentModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (role == Qt::CheckStateRole) {
        if (static_cast<Qt::CheckState>(value.toInt()) == Qt::Checked){
            fragmentsCheckState[index.row()] = Qt::Checked;
//            selectedFraments.push_back(&fragments[index.row()]);
            return true;
        } else {
            fragmentsCheckState[index.row()] = Qt::Unchecked;
            return true;
        }
    }
    return false;
}

Qt::ItemFlags FragmentModel::flags(const QModelIndex &index) const
{
    if(index.column() == 0)
        return Qt::ItemIsUserCheckable | Qt::ItemIsEditable |Qt::ItemIsEnabled;
    else
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void FragmentModel::addFragment(const FragmentInfo &fragment)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    fragments.append(fragment);
    fragmentsCheckState.append(Qt::Unchecked);
    endInsertRows();
}

void FragmentModel::removeFragment(const QModelIndexList modelIdexesList)
{
    if (fragments.isEmpty() || modelIdexesList.isEmpty())
        return;
    beginRemoveRows(QModelIndex(), modelIdexesList.first().row(), modelIdexesList.last().row());
    for (const auto &modelIndex : modelIdexesList){
        fragments.removeAt(modelIndex.row());
        fragmentsCheckState.removeAt(modelIndex.row());
    }
    endRemoveRows();
}

void FragmentModel::clearModel()
{
    while (!fragments.isEmpty()) {
        beginRemoveRows(QModelIndex(), 0, 0);
        fragments.removeFirst();
        fragmentsCheckState.removeFirst();
        endRemoveRows();
    }
}

QList<FragmentInfo> FragmentModel::getSelectedFragments() const
{
    QList<FragmentInfo> resultList;
    for (int i = 0; i < fragments.size(); i++) {
        if(fragmentsCheckState.at(i) == Qt::Checked)
            resultList.append(fragments.at(i));
    }
    return resultList;
}

bool FragmentModel::isContainsVideoFragment()
{
    for (auto &fragment : fragments) {
        if (fragment.isVideoFragment())
            return true;
    }
    return false;
}

bool FragmentModel::isEmpty()
{
    return fragments.isEmpty();
}

