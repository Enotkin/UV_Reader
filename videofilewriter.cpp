#include "videofilewriter.h"


VideoFileWriter::VideoFileWriter(const QFileInfo &pathToDir, VideoSettings settings) : fileInfo(pathToDir), settings(settings)
{

}

VideoFileWriter::VideoFileWriter(const QString &pathToDir, VideoSettings settings) : fileInfo(pathToDir), settings(settings)
{

}


void VideoFileWriter::fn(int value)
{   
//    if (!vfr->isOpen())
//        return;


//    outputVideo.open(getFullName().toStdString(), vfr->getCodec(), vfr->getFrameRate(), size, true);

//    cv:: Mat src, res;
//    vfr->setCurrentFrameNumber(value);
//    for(;;) //Show the image captured in the window and repeat
//    {
//        vfr->get             // read
//        if (src.empty())
//            break;         // check if at end
//        qDebug()<<"pixel: "<<src.at<uint>(0);
//        cv::Mat matCopy = src.clone();
//        outputVideo << src;

//    }
}
