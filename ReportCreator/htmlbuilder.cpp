#include "htmlbuilder.h"

HtmlBuilder::HtmlBuilder()
{
    html.append("<meta charset=\"utf-8\">");
    html.append("<div><h1 align=center>Отчёт</h1></div>");
}

QString HtmlBuilder::getHtml() const
{
    return html.join("\n");
}

void HtmlBuilder::insertImages(const QStringList &imgs)
{
    html.append("<div>");
    for (auto imagePath : imgs){
        QString textToInsert = "<img src=\"" + imagePath + "\" width=\"300\">";
        html.append(textToInsert);
    }
    html.append("</div>");
}

void HtmlBuilder::insertMessage(const QString &message)
{
    html.append("<div>");
    html.append("<p>" + message + "</p>");
    html.append("</div>");
}

void HtmlBuilder::insertAdspInfo(const QStringList &adspInfo)
{
    html.append("<div><p>");
    for (auto var : adspInfo) {
        html.append(var + "<br>");
    }
    html.append("</p></div>");
}

