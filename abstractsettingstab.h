#ifndef ABSTRACTSETTINGSTAB_H
#define ABSTRACTSETTINGSTAB_H

#include <QWidget>

class AbstractSettingsTab : public QWidget
{
    Q_OBJECT
public:
    AbstractSettingsTab(QWidget *parent = nullptr) : QWidget(parent){}
    virtual ~AbstractSettingsTab() {}
    virtual void setWorkState(bool state) = 0;
};

#endif // ABSTRACTSETTINGSTAB_H
