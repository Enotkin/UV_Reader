#include "videocontrolsform.h"
#include "ui_videocontrolsform.h"

VideoControlsForm::VideoControlsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoControlsForm)
{
    ui->setupUi(this);
    setupMediaControlsToolBar();
}

VideoControlsForm::~VideoControlsForm()
{
    delete ui;
}

void VideoControlsForm::setupMediaControlsToolBar()
{

    auto toolbar = new QToolBar(ui->controlButtonWidget);
    toolbar->setIconSize(QSize(24, 24));
    toolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    toolbar->addAction(ui->actionRepeatFragment);
    toolbar->addAction(ui->actionReset);
    toolbar->addSeparator();
    toolbar->addAction(ui->actionBeginVideo);
    toolbar->addAction(ui->actionPrevFrame);
    toolbar->addAction(ui->actionStop);
    toolbar->addAction(ui->actionPlayPause);
    toolbar->addAction(ui->actionNextFrame);
    toolbar->addAction(ui->actionEndVideo);
    ui->controlButtonWidget->layout()->addWidget(toolbar);
}

QString VideoControlsForm::msecToStr(const double value)
{

    KTime time(0, 0, 0, static_cast<int>(value));
    return time.toString();
}

void VideoControlsForm::on_actionPlayPause_triggered(bool checked)
{
    Q_UNUSED(checked)
    if (videoPlayer->isPlayBackActive())  {
        updateAction(ui->actionPlayPause, QIcon(":/mediaIcons/play.png"), "Play");
        videoPlayer->pause();
    } else {
        updateAction(ui->actionPlayPause, QIcon(":/mediaIcons/pausa.png"), "Pause");
        videoPlayer->play();
    }
}

void VideoControlsForm::on_actionStop_triggered()
{
    updateAction(ui->actionPlayPause, QIcon(":/mediaIcons/play.png"), "Play");
    videoPlayer->stop();
}

void VideoControlsForm::on_actionNextFrame_triggered()
{
   videoPlayer->nextFrame();
}

void VideoControlsForm::on_actionPrevFrame_triggered()
{
   videoPlayer->prevFrame();
}

void VideoControlsForm::on_actionEndVideo_triggered()
{
   videoPlayer->end();
}

void VideoControlsForm::on_actionBeginVideo_triggered()
{
   videoPlayer->begin();
}

void VideoControlsForm::on_actionReset_triggered()
{
    auto fragment = createSourceFragment();
    updateSlider(fragment.getFrameRange().first, fragment.getFrameRange().second);
    videoPlayer->setFragment(fragment);
}

void VideoControlsForm::on_actionRepeatFragment_triggered(bool checked)
{
    videoPlayer->setRepeatMode(checked);
}

void VideoControlsForm::setView(const ViewMethod &value)
{
    if (!displayFrame)
        displayFrame = value;
}

void VideoControlsForm::updateFrame(QImage image, double time, int frame)
{
    if (displayFrame){
        displayFrame(image);
        if (videoPlayer){
            updateLabel(ui->frameLabel, QString::number(frame), QString::number(videoSettings->getCountFrames()));
            updateLabel(ui->timeLabel, msecToStr(time), msecToStr(videoSettings->getDuration()));
            updateSlider(frame);
        } else {
            updateLabel(ui->frameLabel, "-", "-");
            updateLabel(ui->timeLabel, "-", "-");
            updateSlider(0, 0);
        }
    }
}

void VideoControlsForm::updateLabel(QLabel *label, const QString &first, const QString &second)
{
    auto result1 = QString("%1 / %2").arg(first).arg(second);
    label->setText(result1);
}

void VideoControlsForm::updateSlider(int frame)
{
    ui->horizontalSlider->blockSignals(true);
    ui->horizontalSlider->setValue(frame);
    ui->horizontalSlider->blockSignals(false);
}

void VideoControlsForm::updateSlider(int startValue, int endValue)
{
    ui->horizontalSlider->blockSignals(true);
    ui->horizontalSlider->setRange(startValue, endValue);
    ui->horizontalSlider->setValue(startValue);
    ui->horizontalSlider->blockSignals(false);
}

FragmentInfo VideoControlsForm::createSourceFragment()
{
    FrameRange frames{0, videoSettings->getCountFrames() - 1};
    TimeRange times;
    PillarRange pillars;
    FragmentInfo sourceFragment(frames, pillars, times, "Status");
    return sourceFragment;
}

void VideoControlsForm::updateAction(QAction *action, const QIcon &icon, const QString &text)
{
    action->setIcon(icon);
    action->setText(text);
    action->setToolTip(text);
}

void VideoControlsForm::setSourceVideoFile(const QFileInfo &value)
{
    disconnect(videoPlayer.get());
    sourceVideoFile = value;
    videoPlayer = std::make_unique<VideoPlayer>(value);
    videoSettings = std::make_unique<VideoSettings>(value);
    auto sourceFragment = createSourceFragment();
    videoPlayer->setFragment(sourceFragment);
    updateSlider(0, videoSettings->getCountFrames());
    connect(videoPlayer.get(), &VideoPlayer::updateFrame, this, &VideoControlsForm::updateFrame);
    connect(ui->horizontalSlider, &QSlider::valueChanged, videoPlayer.get(), &VideoPlayer::setFrame);
}

void VideoControlsForm::setFragment(const FragmentInfo &fragment)
{
    if (videoPlayer){
        updateSlider(fragment.getFrameRange().first - 10, fragment.getFrameRange().second + 10); //NOTE: Допуск для слайдера
        videoPlayer->setFragment(fragment);
    }
}
