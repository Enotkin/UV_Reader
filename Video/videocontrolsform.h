#ifndef VIDEOCONTROLSFORM_H
#define VIDEOCONTROLSFORM_H

#include <QWidget>
#include <QToolBar>
#include <QDebug>
#include <QFileInfo>
#include <QLabel>
#include <QSlider>
#include <functional>
#include <memory>

#include <videoplayer.h>
#include <ktime.h>
#include <frame.h>

namespace Ui {
class VideoControlsForm;
}

using ViewMethod = std::function<void(const QImage&)>;

class VideoControlsForm : public QWidget
{
    Q_OBJECT

public:
    explicit VideoControlsForm(QWidget *parent = nullptr);
    ~VideoControlsForm();

    void setSourceVideoFile(const QFileInfo &value);

    void setFragment(const FragmentInfo &fragment);

    void setView(const ViewMethod &value);

    void play();

    void stop();

public slots:
    void updateFrame(Frame frame);

private slots:
    void on_actionPlayPause_triggered(bool checked);

    void on_actionStop_triggered();

    void on_actionNextFrame_triggered();

    void on_actionPrevFrame_triggered();

    void on_actionEndVideo_triggered();

    void on_actionBeginVideo_triggered();

    void on_actionReset_triggered();

    void on_actionRepeatFragment_triggered(bool checked);

    void on_changeFrameSpinBox_valueChanged(int arg1);

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::VideoControlsForm *ui;
    QFileInfo sourceVideoFile;

    std::unique_ptr<VideoPlayer> videoPlayer;
    std::unique_ptr<VideoSettings> videoSettings;
    ViewMethod displayFrame;

    void setupMediaControlsToolBar();
    QString msecToStr(const double value);
    void updateLabel(QLabel *label, const QString &first, const QString &second);
    void updateSlider(int frame);
    void updateSlider(int startValue, int endValue);
    FragmentInfo createSourceFragment();
    void updateAction(QAction *action, const QIcon &icon, const QString &text);


};

#endif // VIDEOCONTROLSFORM_H
