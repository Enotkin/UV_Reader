#include "testanalysiswidget.h"
#include "ui_testanalysiswidget.h"

TestAnalysisWidget::TestAnalysisWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestAnalysisWidget)
{
    ui->setupUi(this);
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
    ui->horizontalSliderFrame->setRange(0, dataReader->getSettings().getCountFrames());
}


void TestAnalysisWidget::on_horizontalSliderFrame_valueChanged(int value)
{
    if (!dataReader)
        return;
    currentFrame = value;
    thresholdMagic();
}

void TestAnalysisWidget::thresholdMagic()
{
//    cv::Mat sourceMat = dataReader->getMatFrame(currentFrame);
    videoCapture->set(cv::CAP_PROP_POS_FRAMES, static_cast<double>(currentFrame));
    cv::Mat src;
    videoCapture->read(src);
    cv::Mat sourceMatGray, destMat;
    cv::cvtColor(src, sourceMatGray, cv::COLOR_BGR2GRAY);
    cv::threshold(sourceMatGray, destMat, thresholdValue, 255, cv::THRESH_BINARY);

    //поиск контуров
//    cv::Mat out;
//    cv::cvtColor()
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(destMat.clone(), contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    // Create output image
    cv::Mat out;
    cvtColor(destMat, out, cv::COLOR_GRAY2BGR);
    qDebug()<<"Новый кадр";
    std::vector<std::vector<cv::Point>> externalContours;
    std::vector<cv::Moments> moments;
    for (size_t i = 0; i < contours.size(); ++i)
    {

        // Find orientation: CW or CCW
        double area = contourArea(contours[i], true);

        if (area <= 0) {
            //Площадь контура
            double contourSize = cv::contourArea(contours[i]);
//            if (contourSize < 10)
//                continue;
            auto minRect = cv::boundingRect(contours[i]);
//            minRect.
            cv::rectangle(out, cv::Point(minRect.x, minRect.y),
                          cv::Point((minRect.x+minRect.width),(minRect.y+minRect.height)), cv::Scalar(255, 0, 0));

//            cv::drawContours(out, contours, static_cast<int>(i), cv::Scalar(0, 0, 255));

            externalContours.push_back(contours[i]);



            //Момент контура и центр масс
            auto moment = cv::moments(contours[i]);
            double x = moment.m10/moment.m00;
            double y = moment.m01/moment.m00;
//            cv::drawMarker(out, cv::Point(x, y), cv::Scalar(255, 0, 0));

            moments.push_back(moment);

        }
    }


    QImage image(static_cast<uchar*>(out.data), out.cols, out.rows, QImage::Format_RGB888);
    ui->label->setImage(image);
}
