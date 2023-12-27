#include "widgets/common/composed/connectlanwidget.h"

#include <QGridLayout>
#include <QLabel>

#include "widgets/consts.h"
#include "widgets/common/basic/standardpropertylabel.h"


ConnectLANWidget::ConnectLANWidget(QWidget *parent) : QGroupBox(parent), is_connected(false) {
  initUI();
  setConnections();
}

QString ConnectLANWidget::getIP() {
  QString result;
  ip_edit_spinbox->getText(result);
  return result;
}

void ConnectLANWidget::setIP(const QString &new_ip) {
  ip_edit_spinbox->setText(new_ip);
}

int ConnectLANWidget::getPort() {
  int result;
  QString value;
  port_edit_spinbox->getText(value);
  result = value.toInt();
  return result;
}

void ConnectLANWidget::setPort(int new_port) {
  port_edit_spinbox->setText(QString::number(new_port));
}

LampStates ConnectLANWidget::getLANStatus() {
  return LampStates::LAMP_OFF;
}

void ConnectLANWidget::setLANStatus(LampStates lamp_state) {
  lan_status_lamp->setState(lamp_state);
}

void ConnectLANWidget::initUI() {
  setTitle("LAN");
  setMaximumWidth(350);
  setFont(header_group_box_font);

  auto *main_layout = new QGridLayout(this);
  auto *buttons_layout = new QHBoxLayout;

  auto ip_range = QString("(0|[1-9][0-9]?|1[0-9]?[0-9]?|2[0-4][0-9]|25[0-5])");
  auto ip_regex = QRegExp(ip_range + "\\." + ip_range + "\\." + ip_range + "\\." + ip_range);

  auto *ip_label = new StandardPropertyLabel("IP", 14, this);
  auto *port_label = new StandardPropertyLabel("Port", 14, this);
  auto *lan_status_label = new StandardPropertyLabel(tr("Status LAN"), 14, this);

  ip_edit_spinbox = new SoftValidationSpinBox(ip_regex, this);
  port_edit_spinbox = new SoftValidationSpinBox(QRegExp("([0-9]{,5})"), this);

  lan_status_lamp = new LampWidget(this);

  connect_button = new StandardButton(tr("Подкл."), this);
  disconnect_button = new StandardButton(tr("Откл."), this);

  ip_edit_spinbox->setFixedWidth(200);
  ip_edit_spinbox->setAlignment(Qt::AlignRight);

  port_edit_spinbox->setFixedWidth(200);
  port_edit_spinbox->setAlignment(Qt::AlignRight);

  buttons_layout->addWidget(connect_button);
  buttons_layout->addWidget(disconnect_button);

  main_layout->addWidget(ip_label, 0, 0);
  main_layout->addWidget(port_label, 1, 0);
  main_layout->addWidget(lan_status_label, 3, 0);

  main_layout->addWidget(ip_edit_spinbox, 0, 1);
  main_layout->addWidget(port_edit_spinbox, 1, 1);
  main_layout->addWidget(lan_status_lamp, 3, 1, Qt::AlignRight);

  main_layout->addLayout(buttons_layout, 2, 0, 1, 2);

  main_layout->setColumnStretch(0, 1);
  main_layout->setColumnStretch(1, 3);
}

void ConnectLANWidget::setConnections() {
  QObject::connect(this->connect_button, &QPushButton::released,
                   this, &ConnectLANWidget::connectButtonClickedSignal);
  QObject::connect(this->disconnect_button, &QPushButton::released,
                   this, &ConnectLANWidget::disconnectButtonClickedSignal);
}

void ConnectLANWidget::setConnectionStatus(bool status) {
  is_connected = status;
  setLANStatus(status ? LampStates::LAMP_GOOD : LampStates::LAMP_BAD);
  connect_button->setEnabled(!status);
  disconnect_button->setEnabled(status);
}

void ConnectLANWidget::setConnectionInProgress(bool status) {
  connect_button->setEnabled(!status && !is_connected);
  disconnect_button->setEnabled(!status && is_connected);
  update();
}
