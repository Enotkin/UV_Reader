#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QFileInfo>


// Basic node
class TreeItem
{
public:
    explicit TreeItem(const QFileInfo &fileInfo, TreeItem *parentItem = Q_NULLPTR);
    TreeItem (const QFileInfo &fileInfo, QString sectorName, TreeItem *parentItem = Q_NULLPTR);
    ~TreeItem();

    TreeItem *child(int row);
    void appendChild(TreeItem *child);
    void removeChild(int row);
    int childCount() const;

    TreeItem *parentItem();
    QFileInfo data() const;
//    QString getSectorName() const;
//    void setSectorName(const QString &sectorName);

//    int columnCount() const;
    int row() const;
    bool isEmpty() const;


// -------------------


    QString getTripName() const;
    void setTripName(const QString &tripName);

    QString getSecondName() const;
    void setSecondName(const QString &secondName);

    TreeItem *getParentItem() const;

private:    // members
    // -------------------
    TreeItem *m_parentItem;         // parent
    QList<TreeItem*> m_childItems;  // childs
    QFileInfo m_itemData;           // data
    QString m_sectorName = "";
    QString m_tripName = "";
    QString m_secondName = "";

};


#endif // TREEITEM_H
