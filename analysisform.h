#ifndef ANALYSISFORM_H
#define ANALYSISFORM_H

#include <QWidget>
#include <QScopedPointer>
#include <QDebug>
#include <QToolBar>
#include <QFileDialog>

#include <memory>

#include "addfragmentcommentdialog.h"
#include "fragmentinfo.h"
#include "fragmentmodel.h"
#include "videofilereader.h"

namespace Ui {
class analysisForm;
}

class AnalysisForm : public QWidget
{
    Q_OBJECT

public:
    explicit AnalysisForm(QWidget *parent = nullptr);
    void addIntervalComment();
    void clear();
    ~AnalysisForm();

private slots:
    void buttomEnableSwitcher(const QModelIndex &parent, int first, int last);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_actionDelete_triggered();

    void on_actionClear_triggered();

    void on_actionHideAnalysisPanel_triggered();

    void on_actionAddIntervalComment_triggered();

    void on_actionSaveVideoFragment_triggered();

private:
    Ui::analysisForm *ui;
   std::unique_ptr<FragmentModel> model;
    std::shared_ptr<VideoFileReader> videoData;

    void setupUI();
    void setVideoControlButtomEnabled(const bool &state);
    void setDeleteButtomEnabeled(const bool &state);

};

#endif // ANALYSISFORM_H
