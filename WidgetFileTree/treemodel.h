#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QFileInfo>
#include <QDir>

//#include <import/adspdata.h>

#include <QDebug>

class TreeItem;

// Basic fileTree model
// without empty folders
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TreeModel(const QString &folder,
                       const QStringList &filterList = QStringList(),
                       QObject *parent = nullptr);
    ~TreeModel() override;

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

// ---------------------
public:     // interface
// ---------------------
    QString rootFolder();
    QFileInfo fileInfo(const QModelIndex &index);

    void setFilter(const QStringList &filterList);

// -------------------
private:    // methods
// -------------------
    bool makeBranch(const QFileInfo &dirInfo, TreeItem *parent);
    bool isLeaf(const QFileInfo &node); // not a folder
    bool isNeed(const QFileInfo &node); // suitable (corresponding (appropriate)) extension
    QString getSectorName(const QFileInfo &dirInfo);
    QString getTripName(const QFileInfo &dirInfo);

// -------------------
private:    // members
// -------------------
    TreeItem *rootItem;         // root
    QStringList m_filterList = {"avi"};   // File filter (extensions)
    QString m_rootFolder;       // Top level folder (where we are)

};

#endif // TREEMODEL_H
