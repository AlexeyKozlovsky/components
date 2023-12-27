#include "widgets/common/basic/sfpstatusesdialog.h"

#include <QFormLayout>
#include <QLabel>


SFPStatusesDialog::SFPStatusesDialog(dev::SFPParameters statuses, QWidget *parent): QDialog(parent) {
  initUI(statuses);
}

// TODO: Редактировать SFP статусы. Добавить туда оптическую мощность

void SFPStatusesDialog::initUI(dev::SFPParameters statuses) {
  auto *main_layout = new QFormLayout(this);

  QFont key_font("Segoe UI", 14, 2);
  QFont value_font("Segoe UI", 14, 1);

  auto *temp_key_label = new QLabel(tr("Temperature: "), this);
  auto *voltage_key_label = new QLabel(tr("Voltage: "), this);
  auto *tx_amperage_shift_key_label = new QLabel(tr("TX amperage shift: "), this);
  auto *tx_optical_power_key_label = new QLabel(tr("TX optical power: "), this);
  auto *rx_signal_power_key_label = new QLabel(tr("RX signal power: "), this);

  auto *temp_value_label = new QLabel(QString::number(statuses.temperature) + " celc.", this);
  auto *voltage_value_label = new QLabel(QString::number(statuses.voltage) + " mV", this);
  auto *tx_amperage_shift_value_label = new QLabel(QString::number(statuses.tx_amperage_shift) + " mA", this);
  auto *tx_optical_power_value_label = new QLabel(QString::number(statuses.tx_optical_power), this);
  auto *rx_signal_power_value_label = new QLabel(QString::number(statuses.rx_power) + " mW", this);

  temp_key_label->setFont(key_font);
  voltage_key_label->setFont(key_font);
  tx_amperage_shift_key_label->setFont(key_font);
  tx_optical_power_key_label->setFont(key_font);
  rx_signal_power_key_label->setFont(key_font);

  temp_value_label->setFont(value_font);
  voltage_value_label->setFont(value_font);
  tx_amperage_shift_value_label->setFont(value_font);
  tx_optical_power_value_label->setFont(value_font);
  rx_signal_power_value_label->setFont(value_font);

  main_layout->addRow(temp_key_label, temp_value_label);
  main_layout->addRow(voltage_key_label, voltage_value_label);
  main_layout->addRow(tx_amperage_shift_key_label, tx_amperage_shift_value_label);
  main_layout->addRow(tx_optical_power_key_label, tx_optical_power_value_label);
  main_layout->addRow(rx_signal_power_key_label, rx_signal_power_value_label);
}

