//
//  treemodel.cpp
//
//  Provides a simple tree model to show how to create and use hierarchical
//  models.
//

#include "treeitem.h"
#include "treemodel.h"

#include <QStringList>


// Basic model, which starts from 'folder',
// with file's extension filter
TreeModel::TreeModel(const QString &folder, const QStringList &filterList, QObject *parent)
    : QAbstractItemModel(parent),
      m_filterList(filterList),
      m_rootFolder(folder)
{
    rootItem = new TreeItem(QFileInfo(folder));
    m_filterList.append("avi");
    // init with files / make branches
    makeBranch(rootItem->data(), rootItem);
}

TreeModel::~TreeModel()
{
    if (rootItem != nullptr)
    {
        delete rootItem;
    }
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    // NOTE: unused variable
    Q_UNUSED(parent);

    return 1;
//    if (parent.isValid())
//        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
//    else
//        return rootItem->columnCount();
}

// Get FileInfo at specifed 'index'
QFileInfo TreeModel::fileInfo(const QModelIndex &index)
{
    QFileInfo fileInfo;
    if (!index.isValid())
    {
        return fileInfo;
    }

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    fileInfo = item->data();

    return fileInfo;
}

// Sets file's extension filter (list)
void TreeModel::setFilter(const QStringList &filterList)
{
    m_filterList = filterList;
}

// Get rootFolder (which locates in table's header)
QString TreeModel::rootFolder()
{
    return m_rootFolder;
}

// dunno. Just +c +v
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole || index.column() != 0)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return item->data().fileName()/* + "  —  " + item->getSecondName()*/;

//  return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return nullptr;

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    const QStringList headers = { m_rootFolder, "Участок" };
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole && section < headers.size()) {
        return headers[section];
    }
    return QVariant();

//    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//        return rootItem->data(section);

//    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}


// The recursive function:
// find all corresponding branches of paths
bool TreeModel::makeBranch(const QFileInfo &dirInfo, TreeItem *parentTreeItem)
{
    QDir dir = QDir(dirInfo.absoluteFilePath());
    QFileInfoList filesInfoList = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot,
                                                    QDir::DirsFirst);
    for (QFileInfo &fileInfo : filesInfoList) {
        if (isLeaf(fileInfo) && isNeed(fileInfo)) {
            parentTreeItem->setSecondName(getSectorName(dirInfo));
            TreeItem *childTreeItem = new TreeItem(fileInfo, parentTreeItem);
            parentTreeItem->appendChild(childTreeItem);
            //                if ( parentTreeItem->getParentItem()->getSecondName().isEmpty())
            //                    parentTreeItem->getParentItem()->setSecondName(getTripName(dirInfo));
            //                return true;
        } else {
            TreeItem *childTreeItem = new TreeItem(fileInfo, parentTreeItem);
            if (makeBranch(fileInfo, childTreeItem)) {
                parentTreeItem->appendChild(childTreeItem);
            } else {
                delete childTreeItem;
                childTreeItem = Q_NULLPTR;
            }
        }
    }
    return !parentTreeItem->isEmpty();
}

QString TreeModel::getSectorName(const QFileInfo &dirInfo)
{
//    QString adspDataFileFullName = dirInfo.absoluteFilePath() + "/" + AdspData::getDefaultADSPDataFileName();
//    QDir dir = QDir (dirInfo.absoluteFilePath());
//    if(dir.entryList(QDir::Files).contains(AdspData::getDefaultADSPDataFileName())){
//        return AdspData::getAreaName(adspDataFileFullName);
//    } else {
//        return "";
//    }
    return "Sector";
}

QString TreeModel::getTripName(const QFileInfo &dirInfo)
{
//    QString adspDataFileFullName = dirInfo.absoluteFilePath() + "/" + AdspData::getDefaultADSPDataFileName();
//    QDir dir = QDir (dirInfo.absoluteFilePath());
//    if(dir.entryList(QDir::Files).contains(AdspData::getDefaultADSPDataFileName())){
//        return AdspData::getTripName(adspDataFileFullName);
//    } else {
//        return "";
//    }

    return "Trip";
}

// Node - is a leaf
bool TreeModel::isLeaf(const QFileInfo &node)
{
    return !node.isDir();   // not a folder
}

// Leaf (node) has appropriate extension
bool TreeModel::isNeed(const QFileInfo &node)
{
    // No filter - always suitable
    if (m_filterList.isEmpty())
    {
        return true;
    }

    // get extension
    QString suffix = node.suffix();
    for (const QString &fileFilter : m_filterList)
    {
        if (fileFilter == suffix)
        {
            // we got, what do we need
            return true;
        }
    }

    return false;
}


