#ifndef TESTANALYSISWIDGET_H
#define TESTANALYSISWIDGET_H

#include <QWidget>
#include <QFileInfo>
#include <QDebug>
#include <QTime>
#include <memory>
#include <algorithm>
#include <videofilereader.h>
#include <labelevent.h>
#include "crowncharge.h"

using Contour = std::vector<cv::Point>;
using Contours = std::vector<Contour>;

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

    void setRectsList(const QList<QRect> &value);
    void setFrame(int frame);



private slots:
    void on_horizontalSliderFrame_valueChanged(int value);

private:
    Ui::TestAnalysisWidget *ui;
    QFileInfo sourceFile;
    QList<QRect> rectsList;
    std::list<CrownCharge> crownCharges;
    std::map<int, Contours> countersAtFrames;
    std::unique_ptr<VideoFileReader> dataReader;
    std::unique_ptr<cv::VideoCapture> videoCapture;
    double thresholdValue = 225;
    int currentFrame = 0;

    void thresholdMagic();
    void applyMask(cv::Mat &img);
    void firstAnalysis();
    void fillListView(const Contours &contours);

};

#endif // TESTANALYSISWIDGET_H
