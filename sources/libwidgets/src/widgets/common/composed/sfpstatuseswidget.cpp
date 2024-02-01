#include <QFormLayout>

#include "widgets/common/composed/sfpstatuseswidget.h"
#include "widgets/common/basic/standardpropertylabel.h"

#include <QDebug>

SFPStatusesWidget::SFPStatusesWidget(QWidget *parent) : QWidget(parent) {
  initUI();
  setConnections();
}

void SFPStatusesWidget::initUI() {
  auto *main_layout = new QFormLayout(this);

  QFont key_font("Segoe UI", 14, 2);
  QFont value_font("Segoe UI", 14, 1);

  auto *temp_key_label = new StandardPropertyLabel(tr("Temperature: "), this);
  auto *voltage_key_label = new StandardPropertyLabel(tr("Voltage: "), this);
  auto *tx_amperage_shift_key_label = new StandardPropertyLabel(tr("TX amperage shift: "), this);
  auto *tx_optical_power_key_label = new StandardPropertyLabel(tr("TX optical power: "), this);
  auto *rx_signal_power_key_label = new StandardPropertyLabel(tr("RX signal power: "), this);

  _temp_value_label = new StandardPropertyLabel(_temp_postfix, this);
  _voltage_value_label = new StandardPropertyLabel(_tx_voltage_postfix, this);
  _tx_amperage_shift_value_label = new StandardPropertyLabel(_tx_amperage_postfix, this);
  _tx_optical_power_value_label = new StandardPropertyLabel(_tx_optical_power_postfix, this);
  _rx_signal_power_value_label = new StandardPropertyLabel(_rx_power_postfix, this);

  temp_key_label->setFont(key_font);
  voltage_key_label->setFont(key_font);
  tx_amperage_shift_key_label->setFont(key_font);
  tx_optical_power_key_label->setFont(key_font);
  rx_signal_power_key_label->setFont(key_font);

  _temp_value_label->setFont(value_font);
  _voltage_value_label->setFont(value_font);
  _tx_amperage_shift_value_label->setFont(value_font);
  _tx_optical_power_value_label->setFont(value_font);
  _rx_signal_power_value_label->setFont(value_font);

  main_layout->addRow(temp_key_label, _temp_value_label);
  main_layout->addRow(voltage_key_label, _voltage_value_label);
  main_layout->addRow(tx_amperage_shift_key_label, _tx_amperage_shift_value_label);
  main_layout->addRow(tx_optical_power_key_label, _tx_optical_power_value_label);
  main_layout->addRow(rx_signal_power_key_label, _rx_signal_power_value_label);
}

void SFPStatusesWidget::setConnections() {

}


void SFPStatusesWidget::setTemp(const QString &value) {
  if (_temp_value_label != nullptr) {
    _temp_value_label->setText(value + _temp_postfix);
  } else {
    qCritical() << "Value label is nullptr " << __func__;
  }
}

void SFPStatusesWidget::setTxVoltage(const QString &value) {
  if (_voltage_value_label != nullptr) {
    _voltage_value_label->setText(value + _tx_voltage_postfix);
  } else {
    qCritical() << "Value label is nullptr " << __func__;
  }
}

void SFPStatusesWidget::setTxAmperage(const QString &value) {
  if (_tx_amperage_shift_value_label != nullptr) {
    _tx_amperage_shift_value_label->setText(value + _tx_amperage_postfix);
  } else {
    qCritical() << "Value label is nullptr " << __func__;
  }
}

void SFPStatusesWidget::setTxOpticalPower(const QString &value) {
  if (_tx_optical_power_value_label != nullptr) {
    _tx_optical_power_value_label->setText(value + _tx_optical_power_postfix);
  } else {
    qCritical() << "Value label is nullptr " << __func__;
  }
}

void SFPStatusesWidget::setRxPower(const QString &value) {
  if (_rx_signal_power_value_label != nullptr) {
    _rx_signal_power_value_label->setText(value + _rx_power_postfix);
  } else {
    qCritical() << "Value label is nullptr " << __func__;
  }
}
