#include "reportdialog.h"
#include "ui_reportdialog.h"

ReportDialog::ReportDialog(QDir dir, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportDialog),
    workDir(dir)
{
    ui->setupUi(this);
    loadSavedReportsDir();
    ui->lineEditReportSavePath->setText(getFreeFileName());
}

ReportDialog::~ReportDialog()
{
    clearTempFiles();
    delete ui;
}

//====================================================================================

void ReportDialog::addUpImage(QList<QImage> images)
{
    if (!images.isEmpty()){
        upperImages = images;
        ui->checkBoxUpImages->setChecked(true);
    } else {
        ui->checkBoxUpImages->setEnabled(false);
    }
}

void ReportDialog::addDownImage(QList<QImage> images)
{
    if (!images.isEmpty()){
        downImages = images;
        ui->checkBoxDownImage->setChecked(true);
    } else {
       ui->checkBoxDownImage->setEnabled(false);
    }
}

void ReportDialog::addImages(QList<QImage> images, ImageType imageType)
{
    ReportImages imags {imageType, images};
    allImages.append(imags);
}

//====================================================================================

void ReportDialog::addAdspInfo(QStringList adspInfo)
{
    OLD_htmlBuilder.insertAdspInfo(adspInfo);
}

void ReportDialog::on_buttonBox_accepted()
{
    if (ui->checkBoxMessage->isChecked()){
        insertMessageInHtml(ui->textEdit->toPlainText());
    }
    if (ui->checkBoxDownImage->isChecked()){
        insertDownImageInHtml();
    }
    if (ui->checkBoxUpImages->isChecked()){
        insertUpperImagesInHtml();
    }
    document.setHtml(OLD_htmlBuilder.getHtml());
    printDocument();
    clearTempFiles();
}

void ReportDialog::on_pushButtonChangeReportSavePath_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QString result = dialog.getSaveFileName(this, tr("Выбор каталога"), workDir.absolutePath(), tr("Pdf документы (*.pdf)"));
    ui->lineEditReportSavePath->setText(result);
//    QFileInfo fileInfo(result);
//    fileInfo.absolutePath();

}

void ReportDialog::clearTempFiles()
{
    if (!tempFileList.isEmpty()){
        for (auto var : tempFileList){
            QFile file(var);
            file.remove();
        }
    }
}

void ReportDialog::printDocument() const
{
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(ui->lineEditReportSavePath->text());
    printer.setPageMargins(QMarginsF(10, 10, 10, 10));
    document.print(&printer);
}

void ReportDialog::insertUpperImagesInHtml()
{
    if (upperImages.isEmpty())
        return;

    QStringList upperFilesPath;
    for (auto i = 0; i < upperImages.size(); i++){
        QString absoluteImageFilePath = workDir.absolutePath()+"/upperImage_" + QString::number(i) + ".bmp";
        upperImages.at(i).save(absoluteImageFilePath);
        upperFilesPath.append(absoluteImageFilePath);
    }
    tempFileList += upperFilesPath;
    OLD_htmlBuilder.insertImages(upperFilesPath);
//    htmlBuilder.insertUpImages(upperFilesPath);
}

void ReportDialog::insertDownImageInHtml()
{
    if (downImages.isEmpty())
        return;

    QStringList downFilesPath;
    for (auto i = 0; i < downImages.size(); i++){
        QString absoluteImageFilePath = workDir.absolutePath() + "/downImage_" + QString::number(i) + ".bmp";
        downImages.at(i).save(absoluteImageFilePath);
        downFilesPath.append(absoluteImageFilePath);
    }
    tempFileList += downFilesPath;
    OLD_htmlBuilder.insertDownImages(downFilesPath);
}

void ReportDialog::insertImageToHtml(QList<QImage> &img)
{
    if (img.isEmpty())
        return;
    QStringList imagePaths;
    for (int localImageIndex = 0; localImageIndex < img.size(); localImageIndex++){
        int imageIndex = globalIndexImageFiles + localImageIndex;
        QString imageFilePath = workDir.absolutePath() + "/Temp_Image_" + QString::number(imageIndex) + ".bmp";
        img.at(localImageIndex).save(imageFilePath);
        imagePaths.append(imageFilePath);
    }
    tempFileList += imagePaths;
    OLD_htmlBuilder.insertImages(imagePaths);
}

void ReportDialog::insertMessageInHtml(const QString &message)
{
    OLD_htmlBuilder.insertMessage(message);
}

QString ReportDialog::getFreeFileName()
{
    int numberReport = 1;
    currentReportFileName = "report_" + QString::number(numberReport) + ".pdf";
    QString resultFileName = workDir.absolutePath() + "/" + currentReportFileName;
    while (QFile::exists(resultFileName)) {
        numberReport++;
        resultFileName = workDir.absolutePath() + "/report_"+QString::number(numberReport) + ".pdf";
    }
    return resultFileName;
}

void ReportDialog::loadSavedReportsDir()
{
//    QDir savedDir(StateSaver::getInstance()->getSomeSetting(nameoptions::ReportSavePath).toString());
//    if (!savedDir.isEmpty())
//        workDir = savedDir;
}

void ReportDialog::on_lineEditReportSavePath_editingFinished()
{
    QFileInfo fileInfo(ui->lineEditReportSavePath->text());
    bool wrongFileName = false;
    bool wrongDiretory = false;
    if (fileInfo.exists()){
        wrongFileName = true;
        QMessageBox fileIsExists;
        fileIsExists.setText("Файл с таким именем уже существует\n" + fileInfo.fileName());
        fileIsExists.exec();
    }
    QDir dir(fileInfo.absoluteDir());
    if (!dir.exists()){
        wrongDiretory = true;
        QMessageBox fileIsExists;
        fileIsExists.setText("Такой каталог не существует\n"+dir.absolutePath());
        fileIsExists.exec();
    }

    qDebug()<<"Вызов сигнала";
}

void ReportDialog::temp_on_buttonBox_accepted()
{
    if (ui->checkBoxMessage->isChecked()){
        insertMessageInHtml(ui->textEdit->toPlainText());
    }
    if (ui->checkBoxDownImage->isChecked()){
        temp_insertDownImageInHtml();
    }
    if (ui->checkBoxUpImages->isChecked()){
        temp_insertUpperImagesInHtml();
    }
    document.setHtml(OLD_htmlBuilder.getHtml());
    printDocument();
    clearTempFiles();
}

void ReportDialog::temp_insertDownImageInHtml()
{
    for (auto var : allImages){
        if (var.first == ImageType::LowerImages){
            insertImageToHtml(var.second);
        }
    }
}

void ReportDialog::temp_insertUpperImagesInHtml()
{

}
