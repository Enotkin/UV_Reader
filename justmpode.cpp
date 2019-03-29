#include "justmpode.h"

justMpode::justMpode(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant justMpode::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

bool justMpode::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

QModelIndex justMpode::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex justMpode::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int justMpode::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int justMpode::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant justMpode::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

bool justMpode::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags justMpode::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;


    return Qt::ItemIsEditable; // FIXME: Implement me!
}
