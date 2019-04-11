#ifndef REPORTDIALOG_H
#define REPORTDIALOG_H

#include <QDialog>
#include <QPair>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QPrinter>
#include <QTextDocument>
#include <ReportCreator/htmltemplatebuilder.h>
#include <ReportCreator/htmlbuilder.h>

//#include "vkuzoptionname.h"
//#include "statesaver.h"

namespace Ui {
class ReportDialog;
}

class ReportDialog : public QDialog
{
    Q_OBJECT

public:

    enum class ImageType
    {
        LowerImages,
        UpperImages,
        Default
    };

    explicit ReportDialog(QDir dir, QWidget *parent = nullptr);
    ~ReportDialog();
    void addUpImage(QList<QImage> images);
    void addDownImage(QList<QImage> images);
    void addAdspInfo(QStringList adspInfo);
    void addImages(QList<QImage> images, ImageType imageType = ImageType::Default);

private slots:
    void on_buttonBox_accepted();

    void on_pushButtonChangeReportSavePath_clicked();

    void on_lineEditReportSavePath_editingFinished();

private:
    typedef QPair<ImageType, QList<QImage>> ReportImages;
    Ui::ReportDialog *ui;
    QDir workDir;
    QTextDocument document;
    HtmlTemplateBuilder OLD_htmlBuilder;
    HtmlBuilder htmlBuilder;
    QStringList tempFileList;
    QString currentReportFileName;
    QList<QImage> downImages;
    QList<QImage> upperImages;
    QList<ReportImages> allImages;
    int globalIndexImageFiles = 0;

    void temp_on_buttonBox_accepted();
    void temp_insertDownImageInHtml();
    void temp_insertUpperImagesInHtml();


    void clearTempFiles();
    void printDocument() const;
    void insertUpperImagesInHtml();
    void insertDownImageInHtml();
    void insertImageToHtml(QList<QImage> &img);
    void insertMessageInHtml(const QString &message);
    QString getFreeFileName();
    void loadSavedReportsDir();
};

#endif // REPORTDIALOG_H
