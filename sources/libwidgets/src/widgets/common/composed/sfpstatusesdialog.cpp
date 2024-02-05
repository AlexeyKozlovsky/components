#include "widgets/common/composed/sfpstatusesdialog.h"

#include <QVBoxLayout>

#include <QDebug>


SFPStatusesDialog::SFPStatusesDialog(QWidget *parent): QDialog(parent) {
  initUI();
  setConnections();
}

void SFPStatusesDialog::initUI() {
  auto main_layout = new QVBoxLayout(this);

  _sfp_statuses_widget = new SFPStatusesWidget(this);
  main_layout->addWidget(_sfp_statuses_widget);
}

void SFPStatusesDialog::setConnections() {

}


void SFPStatusesDialog::setTemp(const QString &value) {
  if (_sfp_statuses_widget != nullptr) {
    _sfp_statuses_widget->setTemp(value);
  } else {
    qCritical() << "SFP statuses widget is nullptr and cannot be accessed from sfp statuses dialog" << __func__;
  }
}

void SFPStatusesDialog::setTxVoltage(const QString &value) {
  if (_sfp_statuses_widget != nullptr) {
    _sfp_statuses_widget->setTxVoltage(value);
  } else {
    qCritical() << "SFP statuses widget is nullptr and cannot be accessed from sfp statuses dialog" << __func__;
  }
}

void SFPStatusesDialog::setTxAmperage(const QString &value) {
  if (_sfp_statuses_widget != nullptr) {
    _sfp_statuses_widget->setTxAmperage(value);
  } else {
    qCritical() << "SFP statuses widget is nullptr and cannot be accessed from sfp statuses dialog" << __func__;
  }
}

void SFPStatusesDialog::setTxOpticalPower(const QString &value) {
  if (_sfp_statuses_widget != nullptr) {
    _sfp_statuses_widget->setTxOpticalPower(value);
  } else {
    qCritical() << "SFP statuses widget is nullptr and cannot be accessed from sfp statuses dialog" << __func__;
  }
}

void SFPStatusesDialog::setRxPower(const QString &value) {
  if (_sfp_statuses_widget != nullptr) {
    _sfp_statuses_widget->setRxPower(value);
  } else {
    qCritical() << "SFP statuses widget is nullptr and cannot be accessed from sfp statuses dialog" << __func__;
  }
}
