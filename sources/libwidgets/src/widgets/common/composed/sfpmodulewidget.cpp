#include "widgets/common/composed/sfpmodulewidget.h"

#include <QVBoxLayout>

#include "widgets/common/basic/ledwidget.h"
#include "widgets/common/basic/standardbutton.h"
#include "widgets/common/basic/standardpropertylabel.h"


SFPModuleWidget::SFPModuleWidget(const QString &sfp_module_name, QWidget *parent): QGroupBox(sfp_module_name, parent) {
  initUI();
}

void SFPModuleWidget::setRxLossStatus(bool enabled) {
  rx_led_widget->setState(enabled);
}

void SFPModuleWidget::setTxFaultStatus(bool status) {
  tx_led_widget->setState(status);
}

void SFPModuleWidget::setRxLoss(bool status) {
  rx_loss_led_widget->setState(status);
}

void SFPModuleWidget::setTxFault(bool status) {
  tx_fault_led_widget->setState(status);
}

void SFPModuleWidget::initUI() {
  setFont(QFont("Segoe UI", 16));

  auto *main_layout = new QVBoxLayout(this);
  auto *led_form_layout = new QGridLayout;

  auto *tx_en_label = new StandardPropertyLabel("RX", 14, this);
  auto *rx_sel_label = new StandardPropertyLabel("TX: ", 14, this);
  auto *rx_los_label = new StandardPropertyLabel("rx los: ", 14, this);
  auto *tx_fault_label = new StandardPropertyLabel("tx fault: ", 14, this);

  rx_led_widget = new EditableLedWidget(Qt::green, Qt::gray, this);
  tx_led_widget = new EditableLedWidget(Qt::green, Qt::gray, this);
  rx_loss_led_widget = new LedWidget(Qt::gray, Qt::red, this);
  tx_fault_led_widget = new LedWidget(Qt::gray, Qt::red, this);

  auto *get_sfp_params_button = new StandardButton(tr("SFP parameters"), this);

  led_form_layout->addWidget(tx_en_label, 0, 0);
  led_form_layout->addWidget(rx_sel_label, 1, 0);
  led_form_layout->addWidget(rx_los_label, 2, 0);
  led_form_layout->addWidget(tx_fault_label, 3, 0);

  led_form_layout->addWidget(rx_led_widget, 0, 1, Qt::AlignRight);
  led_form_layout->addWidget(tx_led_widget, 1, 1, Qt::AlignRight);
  led_form_layout->addWidget(rx_loss_led_widget, 2, 1, Qt::AlignRight);
  led_form_layout->addWidget(tx_fault_led_widget, 3, 1, Qt::AlignRight);

  main_layout->addLayout(led_form_layout);
  main_layout->addWidget(get_sfp_params_button);

  //CONNECTIONS
  // TODO: Заменить виджет для Tx en на редактируемый

  QObject::connect(get_sfp_params_button, &StandardButton::released,
                   this, &SFPModuleWidget::getSFPParamsSignal);
  QObject::connect(rx_led_widget, &EditableLedWidget::clicked,
                   this, &SFPModuleWidget::rxClicked);
  QObject::connect(tx_led_widget, &EditableLedWidget::clicked,
                   this, &SFPModuleWidget::txClicked);

}



