#include "excelhelper.h"

ExcelHelper::ExcelHelper(bool closeExcelOnExit)
{
    m_closeExcelOnExit = closeExcelOnExit;
    m_excelApplication = nullptr;
    m_sheet = nullptr;
    m_sheets = nullptr;
    m_workbook = nullptr;
    m_workbooks = nullptr;
    m_excelApplication = nullptr;

    m_excelApplication = new QAxObject("Excel.Application", 0);//{00024500-0000-0000-C000-000000000046}

    // TODO проверки на корректное создание объектов

    //if (m_excelApplication == nullptr)
    //    throw invalid_argument("Failed to initialize interop with Excel (probably Excel is not installed)");

    m_excelApplication->dynamicCall("SetVisible(bool)", false ); // hide excel
    m_excelApplication->setProperty("DisplayAlerts", 0); // disable alerts

    m_workbooks = m_excelApplication->querySubObject("Workbooks");
    m_workbook = m_workbooks->querySubObject("Add");
    m_sheets = m_workbook->querySubObject("Worksheets");
    m_sheet = m_sheets->querySubObject("Item(int)", 1);
}

void ExcelHelper::SetCellValue(int row, int col, const QString &value)
{
    QAxObject *cell = m_sheet->querySubObject("Cells(int,int)", row, col);
    cell->setProperty("Value",value);
    delete cell;
}

void ExcelHelper::SetCellWidth(int row, int col, int width)
{
    QAxObject *cell = m_sheet->querySubObject("Cells(int,int)", row, col);
    QAxObject *cols = cell->querySubObject("Columns");
    cols->setProperty("ColumnWidth", width);
    delete cols;
    delete cell;
}

void ExcelHelper::SetCellHeight(int row, int col, int height)
{
    QAxObject *cell = m_sheet->querySubObject("Cells(int,int)", row, col);
    QAxObject *rows = cell->querySubObject("Rows");
    rows->setProperty("RowHeight", height);
    delete rows;
    delete cell;
}

void ExcelHelper::SetCellColor(int row, int col, QColor color)
{
    QAxObject *cell = m_sheet->querySubObject("Cells(int,int)", row, col);
    QAxObject *interior = cell->querySubObject("Interior");
    interior->setProperty("Color", color);
    delete interior;
    delete cell;
}

void ExcelHelper::SetCellValueAndWidth(int row, int col, const QString &value, int width)
{
    QAxObject *cell = m_sheet->querySubObject("Cells(int,int)", row, col);
    cell->setProperty("Value",value);
    QAxObject *cols = cell->querySubObject("Columns");
    cols->setProperty("ColumnWidth", width);
    delete cols;
    delete cell;
}

void ExcelHelper::SetRowsHeight(const QString &str_range, int height)
{
    QAxObject *range = m_sheet->querySubObject("Range(const QVariant&)",
                                               QVariant(str_range));
    QAxObject *rows = range->querySubObject("Rows");
    rows->setProperty("RowHeight", height);
    delete rows;
    delete range;
}

void ExcelHelper::SetBorder(const QString &str_range)
{
    QAxObject *range = m_sheet->querySubObject("Range(const QVariant&)",
                                               QVariant(str_range));
    QAxObject *border = range->querySubObject("Borders");
    border->setProperty("LineStyle", 1);
    delete border;
    delete range;
}

void ExcelHelper::SetHorizontalAlignment(const QString &str_range,
                                        ExcelHelper::HorizontalAlignment ha)
{
    QAxObject *range = m_sheet->querySubObject("Range(const QVariant&)",
                                               QVariant(str_range));
    range->dynamicCall("Select()");
    range->dynamicCall("HorizontalAlignment", ha);
    delete range;
}

void ExcelHelper::SetVerticalAlignment(const QString &str_range,
                                      ExcelHelper::VerticalAlignment va)
{
    QAxObject *range = m_sheet->querySubObject("Range(const QVariant&)",
                                               QVariant(str_range));
    range->dynamicCall("Select()");
    range->dynamicCall("VerticalAlignment", va);
    delete range;
}

void ExcelHelper::MergeCells(const QString &str_range)
{
    QAxObject *range = m_sheet->querySubObject("Range(const QVariant&)",
                                               QVariant(str_range));
    range->dynamicCall("Select()");
    range->dynamicCall("MergeCells", true);
    delete range;
}

void ExcelHelper::SaveAs(const QString &fileName)
{
    // TODO порверка на корректность имени
    m_workbook->dynamicCall("SaveAs(const QString&)", fileName);
}

void ExcelHelper:: AddPicture(int row, int col, const QString &path_img, bool square)
{
    // определяем координаты верхнего левого угла ячейки и её размеры
    QAxObject *cell = m_sheet->querySubObject("Cells(int,int)", row, col);
    double x = cell->property("Left").toDouble();
    double y = cell->property("Top").toDouble();
    double w = cell->property("Width").toDouble();
    double h = cell->property("Height").toDouble();

    if (square) w = h;

    QAxObject *shapes = m_sheet->querySubObject("Shapes");
    QAxObject *img = shapes->querySubObject(
        "AddPicture(const QString&, bool, bool, QVariant, QVariant, QVariant, QVariant)",
        path_img, false, true, x + 2, y + 2, w - 4, h - 4);

    delete img;
    delete shapes;
    delete cell;
}

void ExcelHelper::AddPicture(const QString &str_range, const QString &path_img, bool square)
{
    QAxObject *cell = m_sheet->querySubObject("Range(const QVariant&)",
                                              QVariant(str_range));
    double x = cell->property("Left").toDouble();
    double y = cell->property("Top").toDouble();
    double w = cell->property("Width").toDouble();
    double h = cell->property("Height").toDouble();

    if (square) w = h;

    QAxObject *shapes = m_sheet->querySubObject("Shapes");
    QAxObject *img = shapes->querySubObject(
        "AddPicture(const QString&, bool, bool, QVariant, QVariant, QVariant, QVariant)",
        path_img, false, true, x + 2, y + 2, w - 4, h - 4);

    delete img;
    delete shapes;
    delete cell;
}

ExcelHelper::~ExcelHelper()
{
    if (m_excelApplication != nullptr)
    {
        if (!m_closeExcelOnExit)
        {
            m_excelApplication->setProperty("DisplayAlerts", 1);
            m_excelApplication->dynamicCall("SetVisible(bool)", true );
        }

        if (m_workbook != nullptr && m_closeExcelOnExit)
        {
            m_workbook->dynamicCall("Close(Boolean)", true);
            m_excelApplication->dynamicCall("Quit(void)");
        }
    }

    delete m_sheet;
    delete m_sheets;
    delete m_workbook;
    delete m_workbooks;
    delete m_excelApplication;
}
