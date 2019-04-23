#include "testanalysiswidget.h"
#include "ui_testanalysiswidget.h"

TestAnalysisWidget::TestAnalysisWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestAnalysisWidget)
{
    ui->setupUi(this);
    this->setVisible(false);
//    ui->verticalSliderThreshold->setRange(0, 255);
}

TestAnalysisWidget::~TestAnalysisWidget()
{
    delete ui;
}

void TestAnalysisWidget::setSourceFile(const QFileInfo &value)
{
    sourceFile = value;
    dataReader = std::make_unique<VideoFileReader>(sourceFile.absoluteFilePath());
    videoCapture = std::make_unique<cv::VideoCapture>(sourceFile.absoluteFilePath().toStdString());
    ui->horizontalSliderFrame->setRange(0, dataReader->getSettings().getCountFrames()-1);
    QTime t;
    t.start();
    firstAnalysis();

    if (crownCharges.empty())
        for (const auto &[numberFrame, contours] : countersAtFrames) {

        }
//        crownCharges.emplace_back()

    qDebug()<<"Время поиска контуров:" << t.elapsed();
}

void TestAnalysisWidget::firstAnalysis()
{
    videoCapture->set(cv::CAP_PROP_POS_AVI_RATIO, 0);
    auto countFrame = videoCapture->get(cv::CAP_PROP_FRAME_COUNT);
    for(size_t frameNumber = 0; frameNumber < countFrame; frameNumber++){
        cv::Mat src, srcGray, dst;
        videoCapture->read(src);
        cv::cvtColor(src, srcGray, cv::COLOR_BGR2GRAY);
        applyMask(srcGray);
        cv::threshold(srcGray, dst, thresholdValue, 255, cv::THRESH_BINARY);
        Contours srcContours, dstContours;
        cv::findContours(dst.clone(), srcContours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
        std::copy_if(srcContours.begin(), srcContours.end(), std::back_inserter(dstContours),
                     [](const auto &contour){ return (cv::contourArea(contour, false) > 5.0) ? true : false; });
        dstContours.shrink_to_fit();
        countersAtFrames.insert(std::make_pair(frameNumber, dstContours));
    }
}

void TestAnalysisWidget::fillListView(const Contours &contours)
{
    ui->listWidget->clear();
    int contourNumber = 1;
     for (const auto &contour : contours) {
            ui->listWidget->addItem(QString("%1 Size: %2").arg(contourNumber++).arg(cv::contourArea(contour)));
        }
}

void TestAnalysisWidget::applyMask(cv::Mat &img)
{
    if (!rectsList.isEmpty()){
        for (const auto &rect : rectsList) {
            cv::rectangle(img, cv::Point(rect.topLeft().x(), rect.topLeft().y()),
                          cv::Point(rect.topLeft().x() + rect.width(), rect.topLeft().y() + rect.height()),
                          cv::Scalar(0, 0, 0), cv::FILLED);
        }
    }
}

void TestAnalysisWidget::on_horizontalSliderFrame_valueChanged(int value)
{
    if (!dataReader)
        return;
    currentFrame = value;
    thresholdMagic();
}

void TestAnalysisWidget::setRectsList(const QList<QRect> &value)
{
    if (rectsList.isEmpty())
        rectsList = value;
    else {
        rectsList = value;
        firstAnalysis();
    }
}

void TestAnalysisWidget::setFrame(int frame)
{
    ui->horizontalSliderFrame->setValue(frame);
}

void TestAnalysisWidget::thresholdMagic()
{
    cv::Mat src;
    fillListView(countersAtFrames.at(currentFrame));
    videoCapture->set(cv::CAP_PROP_POS_FRAMES, currentFrame);
    videoCapture->read(src);
    cv::drawContours(src, countersAtFrames.at(currentFrame), -1, cv::Scalar(0, 0, 255));
    qDebug() << currentFrame <<countersAtFrames.at(currentFrame).size();
    QImage image(static_cast<uchar*>(src.data), src.cols, src.rows, QImage::Format_RGB888);
    ui->label->setImage(image);
}

//    std::vector<cv::Moments> moments;
//Момент контура и центр масс
//            auto moment = cv::moments(contours[i]);
//            double x = moment.m10/moment.m00;
//            double y = moment.m01/moment.m00;
//            cv::drawMarker(out, cv::Point(x, y), cv::Scalar(255, 0, 0));
//            moments.push_back(moment);

//Рисование текста рядом с контуром
//     cv::putText(out, QString("%1 Size: %2").arg(i).arg(area).toStdString(), minRect.tl(), cv::FONT_HERSHEY_PLAIN   , 0.8, cv::Scalar(255, 255, 0) );

//Поиск минимального прямоугольника для объведения контура
//            double contourSize = cv::contourArea(contours[i]);
//            auto minRect = cv::boundingRect(contours[i]);
//            auto minRect = cv::boundingRect(contours[i]);
//            cv::rectangle(out, cv::Point(minRect.x, minRect.y),
//            cv::Point((minRect.x+minRect.width),(minRect.y+minRect.height)), cv::Scalar(255, 0, 0));
