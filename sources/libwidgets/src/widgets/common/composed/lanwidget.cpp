#include "widgets/common/composed/lanwidget.h"

#include <QVBoxLayout>

#include "widgets/common/basic/standardpropertylabel.h"
#include "widgets/common/basic/standardlineedit.h"
#include "widgets/common/basic/ledwidget.h"
#include "widgets/common/basic/standardbutton.h"
#include "widgets/consts.h"

#include <QDebug>


LanWidget::LanWidget(QWidget *parent): QGroupBox("LAN", parent) {
  initUI();
}

void LanWidget::setConnectionStatus(bool status) {
  connection_status_led_widget->setState(status);

  connect_button->setEnabled(!status);
  disconnect_button->setEnabled(status);
  ip_line_edit->setEnabled(!status);
  port_line_edit->setEnabled(!status);
}

void LanWidget::setIP(const QString &ip) {
  ip_line_edit->setText(ip);
}

void LanWidget::setPort(int port) {
  port_line_edit->setText(QString::number(port));
}

void LanWidget::connectButtonClickedSlot() {
  qDebug() << "Connect button clicked " << __func__;
  emit connect(true);
}

void LanWidget::disconnectButtonClickedSlot() {
  qDebug() << "Disconnect button clicked " << __func__;
  emit connect(false);
}

void LanWidget::initUI() {
  setFont(header_group_box_font);

  auto *main_layout = new QVBoxLayout(this);
  auto *address_form_layout = new QGridLayout;
  auto *buttons_layout = new QHBoxLayout;
  auto *status_lan_form_layout = new QGridLayout;

  auto *ip_label = new StandardPropertyLabel(tr("IP"), 14, this);
  auto *port_label = new StandardPropertyLabel(tr("PORT"), 14, this);
  auto *status_lan_label = new StandardPropertyLabel(tr("STATUS LAN"), 14, this);

  ip_line_edit = new StandardLineEdit(this);
  port_line_edit = new StandardLineEdit(this);
  connection_status_led_widget = new LedWidget(Qt::green, Qt::red, this);

  connect_button = new StandardButton(tr("Connect"), this);
  disconnect_button = new StandardButton(tr("Disconnect"), this);

  // LAYOUTING
  address_form_layout->addWidget(ip_label, 0, 0, Qt::AlignLeft);
  address_form_layout->addWidget(port_label, 1, 0, Qt::AlignLeft);
  address_form_layout->addWidget(ip_line_edit, 0, 1, Qt::AlignRight);
  address_form_layout->addWidget(port_line_edit, 1, 1, Qt::AlignRight);

  buttons_layout->addWidget(connect_button);
  buttons_layout->addWidget(disconnect_button);

  status_lan_form_layout->addWidget(status_lan_label, 0, 0, Qt::AlignLeft);
  status_lan_form_layout->addWidget(connection_status_led_widget, 0, 1, Qt::AlignRight);

  main_layout->addLayout(address_form_layout);
  main_layout->addLayout(buttons_layout);
  main_layout->addLayout(status_lan_form_layout);

//  address_form_layout->setContentsMargins(0, 0, 0, 0);
//  buttons_layout->setContentsMargins(0, 0, 0, 0);
//  status_lan_form_layout->setContentsMargins(0, 0, 0, 0);

  main_layout->setSizeConstraint(QLayout::SetMaximumSize);

  // CONNECTIONS
  QObject::connect(connect_button, &StandardButton::pressed,
                   this, &LanWidget::connectButtonClickedSlot);
  QObject::connect(disconnect_button, &StandardButton::pressed,
                   this, &LanWidget::disconnectButtonClickedSlot);
}
