#ifndef FRAGMENTSAVER_H
#define FRAGMENTSAVER_H
#include <QDir>
#include <QDebug>
#include <QImage>
#include <memory>

#include "fragmentinfo.h"
#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"

namespace FileNameTemplats {
    const QString VideoFile = "Фрагмент_кадры_%1_опоры_(%2)_время_%3%4.avi";
    const QString FrameFile = "Кадр_№1%_опора_2%_время_3%4%.png";
};

class FragmentSaver
{
public:
    FragmentSaver(const QString saveDirectoryPathconst, QString sourceFilePath);
    ~FragmentSaver();
    void saveFragment(const FragmentInfo &fragmentInfo, const QString &fileName = "");
    void saveFrameFragment(const FragmentInfo &fragmentInfo, const QString &fileName = "");
    void saveVideoFragment(const FragmentInfo &fragmentInfo, const QString &fileName = "");

private:
    QDir dir;
    QFileInfo sourceFileInfo;
    std::unique_ptr<cv::VideoCapture> videoInput;

    QString createFullFileName(const FragmentInfo &fragmentInfo) const;

};

#endif // FRAGMENTSAVER_H
