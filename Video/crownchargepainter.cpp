#include "crownchargepainter.h"
#include <QtDebug>

CrownChargePainter::CrownChargePainter(const FragmentInfo &fragment) : fragment(fragment)
{
    auto crownCharge = fragment.getCrownCharge();
    for (auto contour : fragment.getCrownCharge().getContours()) {
        track.push_back(contour.getCenterMass());
    }
}

Frame CrownChargePainter::getTrackFrame(const Frame &frame)
{
    auto trackframe = frame;
    auto contours = fragment.getCrownCharge().getContours(trackframe.number);
    if (!contours.empty()) {
        for (auto &contour : contours) {
            auto minRect = cv::boundingRect(contour.getContour());
            cv::rectangle(trackframe.image, cv::Point(minRect.x, minRect.y),
                          cv::Point((minRect.x+minRect.width),(minRect.y+minRect.height)), cv::Scalar(0, 0, 255));
        }
    }
    drawTrack(trackframe.image);
    return trackframe;
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

