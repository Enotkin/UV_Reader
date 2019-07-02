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
#include "fragmentinfo.h"
#include "crownchargedetector.h"

//using Contours = std::vector<Contour>;

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
    void setFrame(int frame);
    void setRectsList(const QList<QRect> &value);
    void setMaskRects(QList<QRect> rects);

private slots:
    void on_horizontalSliderFrame_valueChanged(int value);

private:
    Ui::TestAnalysisWidget *ui;
    QFileInfo sourceFile;
    QList<QRect> rectsList;
    std::map<int, std::vector<Contour>> countersAtFrames;
    std::unique_ptr<VideoFileReader> dataReader;
    std::unique_ptr<cv::VideoCapture> videoCapture;
    double thresholdValue = 225;
    int currentFrame = 0;

    cv::Mat binarization(const cv::Mat &scr);
    void thresholdMagic();
    void fillListView(const std::vector<Contour> &contours);
    void applyMask(cv::Mat &src);
};

#endif // TESTANALYSISWIDGET_H
