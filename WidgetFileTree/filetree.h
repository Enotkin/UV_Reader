#ifndef FILETREE_H
#define FILETREE_H

#include <QWidget>

// Main fileTree model
#include "WidgetFileTree/treeitem.h"
#include "WidgetFileTree/treemodel.h"


#include <QString>
#include <QTreeView>


namespace Ui {
class FileTree;
}


// Widget, that provides simple file tree model
// without empty folders
class FileTree : public QWidget
{
    Q_OBJECT

public:
    explicit FileTree(QWidget *parent = 0, const QString &dir = QString());
    ~FileTree();

    bool isValid();

    QString rootFolder();
    void setRootFolder(const QString &dir);
    QStringList filter();
    void setFilter(const QStringList &filterList);

    void update();

    QFileInfo currentSelected();
    QString currentSelectedQString();
    QFileInfo currentSelectedAbove();
    QFileInfo currentSelectedBelow();

    QFileInfoList currentList();

signals:
    void signalDoubleClicked(QString item);


private slots:
    void on_treeView_doubleClicked(const QModelIndex &index);

// -------------------
private:    // methods
// -------------------
    QFileInfo currentSelectedOffset(int nOffset);
    QModelIndexList availableAtThisLevel(const QModelIndex &index);

// -------------------
private:    // members
// -------------------
    Ui::FileTree *ui;

    QSharedPointer<TreeModel> m_pModel;
    QStringList m_filterList;
};

#endif // FILETREE_H
