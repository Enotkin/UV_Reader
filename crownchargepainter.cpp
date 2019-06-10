#include "crownchargepainter.h"
#include <QtDebug>

CrownChargePainter::CrownChargePainter(const FragmentInfo &fragment) : fragment(fragment)
{
    auto crownCharge = fragment.getCrownCharge();
    for (auto contour : fragment.getCrownCharge().getContours()) {
        track.push_back(contour.getCenterMass());
    }
}

QImage CrownChargePainter::getImage(cv::Mat imageMat, int number)
{
    auto contours = fragment.getCrownCharge().getContours(number);
    if (!contours.empty()) {
        for (auto &contour : contours) {
            auto minRect = cv::boundingRect(contour.getContour());
            cv::rectangle(imageMat, cv::Point(minRect.x, minRect.y),
                          cv::Point((minRect.x+minRect.width),(minRect.y+minRect.height)), cv::Scalar(0, 0, 255));
        }
    }
    drawTrack(imageMat);
    //cv::imshow("Lelelele", imageMat);
    QImage image(static_cast<uchar*>(imageMat.data), imageMat.cols, imageMat.rows, QImage::Format_RGB888);
    return image.copy();
}

void CrownChargePainter::drawTrack(cv::Mat &imageMat)
{
    if(track.empty())
        return;
    for (int i = 0; i < track.size() - 1; i++){
        cv::circle(imageMat, track.at(i), 2, cv::Scalar(0, 255, 0), -1, cv::LINE_AA);
        cv::line(imageMat, track.at(i), track.at(i+1), cv::Scalar(0, 255, 0), 1);
    }
    cv::circle(imageMat, track.back(), 2, cv::Scalar(0, 255, 0), -1, cv::LINE_AA);
}

