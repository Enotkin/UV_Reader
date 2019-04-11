#include "htmltemplatebuilder.h"

HtmlTemplateBuilder::HtmlTemplateBuilder()
{
    QFile file(":/templates/repotTemplate.html");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    html = in.readAll();
    html.replace(html.indexOf("Report"), 6, "Отчёт");
    file.close();
}

QString HtmlTemplateBuilder::getHtml() const
{
    return html;
}

void HtmlTemplateBuilder::insertMessage(const QString &message)
{
    auto htmlMessage = "<p>" + message + "</p>";
    html.insert(emplacePosition(HtmlInsertionPlase::Message), htmlMessage);
}

void HtmlTemplateBuilder::insertImages(const QStringList &imgs)
{
    int pos = html.lastIndexOf("</div>");
    QStringList htmlBlock;
    htmlBlock.append("<div>");
    for (auto imagePath : imgs){
        QString textToInsert = "<img src=\"" + imagePath + "\" width=\"300\">";
        htmlBlock.append(textToInsert);
    }
    htmlBlock.append("</div");
    html.insert(pos, htmlBlock.join("\n"));
}

void HtmlTemplateBuilder::insertUpImages(const QStringList &imgs)
{
    auto pos = emplacePosition(HtmlInsertionPlase::UpImage);
    for (auto imgPath : imgs){
        QString imageInseter = "<img src=\"" + imgPath + "\" width=\"300\">\n";
        html.insert(pos, imageInseter);
        pos += imageInseter.length();
    }
}

void HtmlTemplateBuilder::insertDownImages(const QStringList &imgs)
{
    auto pos = emplacePosition(HtmlInsertionPlase::DownImage);
    for (auto imgPath : imgs){
        QString imageInseter = "<img src=\"" + imgPath + "\" width=\"300\">\n";
        html.insert(pos, imageInseter);
        pos += imageInseter.length();
    }
}

void HtmlTemplateBuilder::insertAdspInfo(const QStringList adspInfo)
{
    int pos = emplacePosition(HtmlInsertionPlase::AdspInfo);
    QString style = "<p>";
    html.insert(pos, style);
    pos += style.size();
    for (auto var : adspInfo) {
        QString htmlIsertStr = var + "<br>";
        html.insert(pos, htmlIsertStr);
        pos += htmlIsertStr.length();
    }
    html.insert(pos, "</p");
}

int HtmlTemplateBuilder::emplacePosition(const QString &htmlInsertionPlase)
{
    return html.indexOf(htmlInsertionPlase) + htmlInsertionPlase.size();
}
