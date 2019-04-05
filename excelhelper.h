#ifndef EXCELHELPER_H
#define EXCELHELPER_H

#include <QColor>
#include <QString>
#include <QAxObject>

//Expected in .pro file: QT += axcontainer
//Application must be of UI type for ActiveX work.
class ExcelHelper
{
public:

    enum HorizontalAlignment
    {
        HA_LEFT   = -4131,
        HA_CENTER = -4108,
        HA_RIGHT  = -4152
    };

    enum VerticalAlignment
    {
        VA_TOP    = -4160,
        VA_CENTER = -4108,
        VA_BOTTOM = -4107
    };

    ExcelHelper(const ExcelHelper& other) = delete;
    ExcelHelper& operator=(const ExcelHelper& other) = delete;
    ExcelHelper(bool closeExcelOnExit = false);

    void SetCellValue(int row, int col, const QString& value);
    void SetCellWidth(int row, int col, int width);
    void SetCellHeight(int row, int col, int height);
    void SetCellColor(int row, int col, QColor color);

    void SetCellValueAndWidth(int row, int col, const QString& value, int width);
    void SetRowsHeight(const QString &str_range, int height);
    void SetBorder(const QString &str_range);

    void SetHorizontalAlignment(const QString &str_range, HorizontalAlignment ha);
    void SetVerticalAlignment(const QString &str_range, VerticalAlignment va);

    void MergeCells(const QString &str_range);

    void SaveAs(const QString& fileName);

    void AddPicture(int row, int col, const QString &path_img, bool square);
    void AddPicture(const QString &str_range, const QString &path_img, bool square);

    ~ExcelHelper();

private:
    QAxObject* m_excelApplication;
    QAxObject* m_workbooks;
    QAxObject* m_workbook;
    QAxObject* m_sheets;
    QAxObject* m_sheet;
    bool m_closeExcelOnExit;
};

#endif // EXCELHELPER_H
