#include "fragmentsaver.h"

FragmentSaver::FragmentSaver(const QString saveDirectoryPath, const QString sourceFilePath) : dir(saveDirectoryPath), sourceFileInfo(sourceFilePath)
{
    videoInput = std::make_unique<cv::VideoCapture>(sourceFileInfo.absoluteFilePath().toStdString());
}

FragmentSaver::~FragmentSaver()
{
    videoInput->release();
}

void FragmentSaver::saveFrameFragment(const FragmentInfo &fragmentInfo, const QString &fileName)
{
    QImage image;
    int numberFrame = fragmentInfo.getFrameRange().first;
    if (numberFrame <= videoInput->get(cv::CAP_PROP_FRAME_COUNT)){
        videoInput->set(cv::CAP_PROP_POS_FRAMES, static_cast<double>(numberFrame));
        cv::Mat frame;
        videoInput->read(frame);
        image = QImage(static_cast<uchar*>(frame.data),
                frame.cols, frame.rows, QImage::Format_RGB888);
    } else {
        image = QImage();
    }
    image.save(createFullFileName(fragmentInfo));
}

void FragmentSaver::saveVideoFragment(const FragmentInfo &fragmentInfo, const QString &fileName)
{
    videoInput->set(cv::CAP_PROP_POS_FRAMES, fragmentInfo.getFrameRange().first);

    int fourcc = static_cast<int>(videoInput->get(cv::CAP_PROP_FOURCC));
    double fps = videoInput->get(cv::CAP_PROP_FPS);
    cv::Size size(static_cast<int>(videoInput->get(cv::CAP_PROP_FRAME_WIDTH)),
                  static_cast<int>(videoInput->get(cv::CAP_PROP_FRAME_HEIGHT)));
    cv::VideoWriter outputVideo(this->createFullFileName(fragmentInfo).toStdString(), fourcc, fps, size, true);

    for (int frameNumber = fragmentInfo.getFrameRange().first; frameNumber < fragmentInfo.getFrameRange().second; frameNumber++) {
        cv::Mat scr;
        videoInput->read(scr);
        outputVideo.write(scr);
    }
    outputVideo.release();
}

QString FragmentSaver::createFullFileName(const FragmentInfo &fragmentInfo) const
{
    QString fileName;
    int number = 0;
    do{
        QString numberFile = (number == 0) ? QString("") : "_"+QString::number(number);
        number++;
        fileName = QString(fragmentInfo.isVideoFragment() ? FileNameTemplats::VideoFile : FileNameTemplats::FrameFile)
                .arg(fragmentInfo.getFrameRangeString())
                .arg(fragmentInfo.getPillarRangeString())
                .arg(fragmentInfo.getTimeString().replace(":","-"))
                .arg(numberFile);
    } while (dir.entryList(QDir::NoDotAndDotDot | QDir::Files).contains(fileName));
    return dir.absoluteFilePath(fileName).replace("/", "\\");
}

