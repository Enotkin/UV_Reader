#ifndef TESTANALYSISWIDGET_H
#define TESTANALYSISWIDGET_H

#include <QWidget>
#include <QFileInfo>
#include <QDebug>
#include <memory>
#include <videofilereader.h>
#include <labelevent.h>

namespace Ui {
class TestAnalysisWidget;
}

class TestAnalysisWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestAnalysisWidget(QWidget *parent = nullptr);
    ~TestAnalysisWidget();

    void setSourceFile(const QFileInfo &value);

private slots:
    void on_horizontalSliderFrame_valueChanged(int value);

private:
    Ui::TestAnalysisWidget *ui;
    QFileInfo sourceFile;
    std::unique_ptr<VideoFileReader> dataReader;
    std::unique_ptr<cv::VideoCapture> videoCapture;
    double thresholdValue = 230;
    int currentFrame = 0;

    void thresholdMagic();

};

#endif // TESTANALYSISWIDGET_H
