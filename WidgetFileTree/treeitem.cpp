//
//  treeitem.cpp
//
//  A container for items of data supplied by the simple tree model.
//

#include <QStringList>

#include "treeitem.h"


TreeItem::TreeItem(const QFileInfo &fileInfo, TreeItem *parent)
{
    m_parentItem = parent;
    m_itemData = fileInfo;
}

TreeItem::TreeItem(const QFileInfo &fileInfo, QString sectorName, TreeItem *parentItem)
{
    m_parentItem = parentItem;
    m_itemData = fileInfo;
    m_sectorName = sectorName;
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    m_childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    return m_childItems.value(row);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

//int TreeItem::columnCount() const
//{
//    return m_itemData.count();
//}

QFileInfo TreeItem::data() const
{
//    return m_itemData.value(column);
    return m_itemData;
}

TreeItem *TreeItem::parentItem()
{
    return m_parentItem;
}

bool TreeItem::isEmpty() const
{
    return childCount() == 0;
}

QString TreeItem::getTripName() const
{
    return m_tripName;
}

void TreeItem::setTripName(const QString &tripName)
{
    m_tripName = tripName;
}

QString TreeItem::getSecondName() const
{
    return m_secondName;
}

void TreeItem::setSecondName(const QString &secondName)
{
    m_secondName = secondName;
}

TreeItem *TreeItem::getParentItem() const
{
    return m_parentItem;
}

//void TreeItem::setSectorName(const QString &sectorName)
//{
//    m_sectorName = sectorName;
//}

//QString TreeItem::getSectorName() const
//{
//    return m_sectorName;
//}

void TreeItem::removeChild(int row)
{
    m_childItems.removeAt(row);
}

int TreeItem::row() const
{
//    if (m_parentItem)
//        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
