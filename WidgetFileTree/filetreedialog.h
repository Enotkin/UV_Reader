#ifndef FILETREEDIALOG_H
#define FILETREEDIALOG_H

#include <QWidget>
#include <QFileDialog>
#include <QDialog>

#include "WidgetFileTree/filetree.h"


namespace Ui {
class FileTreeDialog;
}

class FileTreeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FileTreeDialog(const QString &m_dir = QString(), QWidget *parent = nullptr );
    ~FileTreeDialog();
    FileTree *fileTree();
    QString getRootDir() const;
    void setRootDir(const QString &dir);

signals:
    void signalSelectedFile(QString dir);

private slots:
    void on_pushButtonOpenDir_clicked();
    void on_pushButtonOpenFile_clicked();
    void selectNewCurrentWorkDirectory(QString newDir);

private:
    void connectSignals();

private:
    Ui::FileTreeDialog *ui;
    QString m_dir;
};

#endif // FILETREEDIALOG_H
