#include "widgets/common/composed/datasaverswidget.h"

#include <QDebug>
#include <QGridLayout>

#include "widgets/common/basic/standardbutton.h"


DataSaverWidget::DataSaverWidget(QWidget *parent): QWidget(parent) {
  initUI();
  setConnections();
}

void DataSaverWidget::initUI() {
  auto main_layout = new QGridLayout(this);

  _save_to_eprom_button = new StandardButton(tr("Сохранить в EEPROM"));
  _save_to_db_button = new StandardButton(tr("Сохранить в БД"));
  _save_named_to_db_button = new StandardButton(tr("Сохранить как режим в БД"));

  main_layout->addWidget(_save_to_eprom_button, 0, 0, 1, 2);
  main_layout->addWidget(_save_to_db_button, 1, 0);
  main_layout->addWidget(_save_named_to_db_button, 1, 1);

  _save_to_db_button->setEnabled(false);
  _save_named_to_db_button->setEnabled(false);
}

void DataSaverWidget::setConnections() {
  if (_save_to_eprom_button != nullptr) {
    QObject::connect(_save_to_eprom_button, &QPushButton::released,
                     this, &DataSaverWidget::saveDataToEPROMButtonClickedBridgeSlot);
  } else {
    qWarning() << "save to eprom button is nullptr " << __func__;
  }

  if (_save_to_db_button != nullptr) {
    QObject::connect(_save_to_db_button, &QPushButton::released,
        this, &DataSaverWidget::saveDataToDBButtonClickedBridgeSlot);
  } else {
    qWarning() << "save to db is nullptr " << __func__;
  }

  if (_save_named_to_db_button != nullptr) {
    QObject::connect(_save_named_to_db_button, &QPushButton::released,
                     this, &DataSaverWidget::saveNamedDataToDBButtonClickedBridgeSlot);
  } else {
    qWarning() << "save to db is nullptr " << __func__;
  }
}

void DataSaverWidget::saveDataToEPROMButtonClickedBridgeSlot() {
  emit saveDataToEPROMActionSignal();
}

void DataSaverWidget::saveDataToDBButtonClickedBridgeSlot() {
  emit saveDataToDBActionSignal();
}

void DataSaverWidget::saveNamedDataToDBButtonClickedBridgeSlot() {

}
