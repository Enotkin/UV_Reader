#ifndef EXCELREPORTCREATOR_H
#define EXCELREPORTCREATOR_H
#include "QString"
#include "QDir"
#include "excelhelper.h"
#include "fragmentinfo.h"


class ExcelReportCreator
{
public:
    ExcelReportCreator(QString pathToSave);

private:
    void createReportDir();
    QDir dir;
};

#endif // EXCELREPORTCREATOR_H
