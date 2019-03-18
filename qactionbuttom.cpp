#include "qactionbuttom.h"

QActionButtom::QActionButtom(QWidget *parent) :
    QPushButton(parent)
{
    actionOwner = nullptr;
}

void QActionButtom::setAction(QAction *action)
{
    if (actionOwner && actionOwner != action) {
           disconnect(actionOwner, &QAction::changed,
                      this, &QActionButtom::updateButtonStatusFromAction);
           disconnect(this, &QActionButtom::clicked,
                      actionOwner, &QAction::trigger);
       }
    actionOwner = action;
    updateButtonStatusFromAction();
    connect(action, &QAction::changed,
                this, &QActionButtom::updateButtonStatusFromAction);
    connect(this, &QActionButtom::clicked,
                actionOwner, &QAction::trigger);
}

void QActionButtom::updateButtonStatusFromAction()
{
    if (!actionOwner)
          return;
    this->setText( actionOwner->text() );
    this->setStatusTip( actionOwner->statusTip() );
    this->setToolTip( actionOwner->toolTip() );
    this->setIcon( actionOwner->icon() );
    this->setEnabled( actionOwner->isEnabled() );
    this->setCheckable( actionOwner->isCheckable() );
    this->setChecked( actionOwner->isChecked());

}
