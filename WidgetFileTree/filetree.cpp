#include "filetree.h"
#include "ui_filetree.h"

#include <QDebug>
// Create widget with starting directory "dir"
// If dir is empty, then object isn't valid
FileTree::FileTree(QWidget *parent, const QString &dir) :
    QWidget(parent),
    ui(new Ui::FileTree)
{
    ui->setupUi(this);
    if (!dir.isEmpty()) {
        m_pModel.reset(new TreeModel(dir));
        ui->treeView->setModel(m_pModel.data());
    }
}

// Basic destructor
FileTree::~FileTree()
{
    delete ui;
}

// Directory was set properly
bool FileTree::isValid()
{
    return !m_pModel.isNull();  // valid: not null
}

// Get root folder (which is located in table's header)
QString FileTree::rootFolder()
{
    QString root;
    if (m_pModel.isNull())
        return root;
    root = m_pModel->rootFolder();
    return root;
}

// Sets root folder to the model, and updates view immediately
void FileTree::setRootFolder(const QString &dir)
{
    m_pModel.reset(new TreeModel(dir, m_filterList));
    ui->treeView->setModel(m_pModel.data());
    //ui->treeView->columnAt()
}

// Get file's extension filter
QStringList FileTree::filter()
{
    return m_filterList;
}

// Set new extension filter
void FileTree::setFilter(const QStringList &filterList)
{
    m_filterList = filterList;
}

// Update model with current folder
void FileTree::update()
{
    setRootFolder(m_pModel->rootFolder());
}

// Get data from user's selected index
QFileInfo FileTree::currentSelected()
{
    QFileInfo fileInfo;
    QModelIndex index = ui->treeView->currentIndex();
    fileInfo = m_pModel->fileInfo(index);
    return fileInfo;
}

QString FileTree::currentSelectedQString()
{
    QFileInfo fileInfo;
    QModelIndex index = ui->treeView->currentIndex();
    fileInfo = m_pModel->fileInfo(index);
    return fileInfo.filePath();
}

// Get data index which located above, than selected
QFileInfo FileTree::currentSelectedAbove()
{
    return currentSelectedOffset(-1);
}

// Get data index which located below, than selected
QFileInfo FileTree::currentSelectedBelow()
{
    return currentSelectedOffset(1);
}

// Get current fileinfo list of expanded folder
// (all entries, which lies at the same level, as current selected item)
QFileInfoList FileTree::currentList()
{
    QFileInfoList fileInfoList;
    // get parent index
    QModelIndex indexCurrent = ui->treeView->currentIndex();
    if (!indexCurrent.isValid()) {
        return fileInfoList;
    }
    QModelIndexList indexList = availableAtThisLevel(indexCurrent);
    // make list of indexes
    for (auto &index : indexList) {
        QFileInfo fileInfo;
        fileInfo = m_pModel->fileInfo(index);
        fileInfoList.append(fileInfo);
    }
    return fileInfoList;
}

// Get data of index which shifted from current
// user's selected by "nOffset" value
QFileInfo FileTree::currentSelectedOffset(int nOffset)
{
    QFileInfo fileInfo;
    QModelIndex indexCurrent = ui->treeView->currentIndex();
    QModelIndex indexShifted = ui->treeView->model()->index(indexCurrent.row() + nOffset,
                                                            indexCurrent.column(),
                                                            indexCurrent.parent());
    fileInfo = m_pModel->fileInfo(indexShifted);
    return fileInfo;
}

// Available one-level childs of parent QModelIndex
// (make list of them)
QModelIndexList FileTree::availableAtThisLevel(const QModelIndex &index)
{
    QModelIndexList list;
    QModelIndex parent = index.parent();
    TreeItem* pItem;
    // 'pItem' for 'childCount()'
    pItem = static_cast<TreeItem*>(index.internalPointer())->parentItem();
    const int infoColumn = 0;
    for (int i = 0; i < pItem->childCount(); ++i) {
        QModelIndex index = ui->treeView->model()->index(i, infoColumn, parent);
        list.append(index);
    }

    return list;
}


// User double-clicked at some entry
void FileTree::on_treeView_doubleClicked(const QModelIndex &index)
{
    if (!index.isValid())
    {
        qDebug() << "Nothing is activated";
        return;
    }

    // Isn't leaf
    if (m_pModel->rowCount(index) > 0)
    {
        return;
    }

    // Activated!
    QFileInfo fileInfo = m_pModel->fileInfo(index);

    emit signalDoubleClicked(fileInfo.filePath());
//    qDebug() << "DClicked file: " << fileInfo.absoluteFilePath();
}
