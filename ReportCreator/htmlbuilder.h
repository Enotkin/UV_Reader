#ifndef HTMLBUILDER_H
#define HTMLBUILDER_H
#include <QString>
#include <QStringList>

class HtmlBuilder
{
public:
    HtmlBuilder();
    QString getHtml() const;
    void insertImages(const QStringList &imgs);
    void insertMessage(const QString &message);
    void insertAdspInfo(const QStringList &adspInfo);

private:
    QStringList html;
};

#endif // HTMLBUILDER_H
