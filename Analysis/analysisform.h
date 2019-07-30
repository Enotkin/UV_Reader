#ifndef ANALYSISFORM_H
#define ANALYSISFORM_H

#include <QWidget>
#include <QScopedPointer>
#include <QDebug>
#include <QToolBar>
#include <QFileDialog>

#include <QItemSelection>
#include <QItemSelectionModel>


#include <memory>


#include "addfragmentcommentdialog.h"
#include "analyzer.h"
#include "fragmentinfo.h"
#include "fragmentmodel.h"
#include "fragmentsaver.h"
#include "videofilereader.h"
#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"
#include "excelhelper.h"

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

    void setVideoData(const std::shared_ptr<VideoFileReader> &value);
    void setMask(const QList<QRect> &value);
    void startAnalysis();

    void setFileInfo(const QFileInfo &value);

signals:
    void playFragment(FragmentInfo fragment);
    void stopFragment();

private slots:
    void buttomEnableSwitcher(const QModelIndex &parent, int first, int last);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_actionDelete_triggered();

    void on_actionClear_triggered();

    void on_actionHideAnalysisPanel_triggered();

    void on_actionAddIntervalComment_triggered();

    void on_actionSaveVideoFragment_triggered();

    void on_actionExcelExport_triggered();

    void on_actionPlay_triggered();

    void on_pushButtonStartAnalysis_clicked();

    void on_actionPlayPrev_triggered();

    void on_actionStop_triggered();

    void on_actionPlayNext_triggered();

    void on_actionDeleteAndPlayNext_triggered();

private:
    Ui::analysisForm *ui;
    QFileInfo fileInfo;
    std::unique_ptr<QItemSelectionModel> selectionModel;
    std::unique_ptr<FragmentModel> model;
    std::shared_ptr<VideoFileReader> videoData;

    void setupUI();
    void setVideoControlButtomEnabled(const bool &state);
    void setDeleteButtomEnabeled(const bool &state);
    BranchSettings assemblyBranchSettings();
};

#endif // ANALYSISFORM_H
