#ifndef HTMLTEMPLATEBUILDER_H
#define HTMLTEMPLATEBUILDER_H
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QImage>
#include <QStringList>
#include <QDebug>

namespace HtmlInsertionPlase {
    const QString Message = "<div id=\"message\">";
    const QString UpImage = "<div id=\"upImage\">";
    const QString DownImage ="<div id=\"downImage\">";
    const QString AdspInfo = "<div id=\"adspInfo\"></div>";

};

class HtmlTemplateBuilder
{
public:
    HtmlTemplateBuilder();    
    QString getHtml() const;
    void insertMessage(const QString &message);
    void insertImages(const QStringList &imgs);
    void insertUpImages(const QStringList &imgs);
    void insertDownImages(const QStringList &imgs);
    void insertAdspInfo(const QStringList adspInfo);

private:
    int emplacePosition(const QString &htmlInsertionPlase);

    QString html;
};

#endif // HTMLTEMPLATEBUILDER_H
