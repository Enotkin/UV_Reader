#ifndef FRAME_H
#define FRAME_H
#include <QImage>

#include "opencv2/highgui.hpp"
#include "asmOpenCV.h"

struct Frame
{
    Frame(cv::Mat image, int frameNumber, double time) :
    image(image), number(frameNumber), time(time) {}

    cv::Mat image;
    int number;
    double time;

    QImage getQImage() {return ASM::cvMatToQImage(image);}
};
#endif // FRAME_H
