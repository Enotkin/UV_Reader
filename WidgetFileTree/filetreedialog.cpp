#include "filetreedialog.h"
#include "ui_filetreedialog.h"


FileTreeDialog::FileTreeDialog(const QString &dir, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileTreeDialog)
{
    ui->setupUi(this);
    this->setModal(true);
    if (!dir.isEmpty()) {
        ui->fileTree->setRootFolder(dir);
    }
    connectSignals();
}

FileTreeDialog::~FileTreeDialog()
{
    delete ui;
}

FileTree *FileTreeDialog::fileTree()
{
    return ui->fileTree;
}

void FileTreeDialog::on_pushButtonOpenDir_clicked()
{
    m_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory tree \\w files"),
                                                    ui->fileTree->rootFolder(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    if (m_dir.isEmpty()){
        return;
    }
    ui->fileTree->setRootFolder(m_dir);
}

void FileTreeDialog::on_pushButtonOpenFile_clicked()
{
    selectNewCurrentWorkDirectory(ui->fileTree->currentSelectedQString());
}

void FileTreeDialog::connectSignals()
{
//    connect(ui->fileTree, SIGNAL(signalDoubleClicked(QString)), SIGNAL(signalSelectedFile(QString)));
    connect(ui->fileTree, &FileTree::signalDoubleClicked, this, &FileTreeDialog::selectNewCurrentWorkDirectory);
}

void FileTreeDialog::selectNewCurrentWorkDirectory(QString newDir)
{
    this->hide();
    emit signalSelectedFile(newDir);
}

void FileTreeDialog::setRootDir(const QString &dir)
{
    if (m_dir == dir)
        return;
    m_dir = dir;
    if (m_dir.isEmpty()) {
        return;
    }
    ui->fileTree->setRootFolder(m_dir);
}

QString FileTreeDialog::getRootDir() const
{
    return m_dir;
}
