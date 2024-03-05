#ifndef SYNCSYS_DEVICE_WIDGET_WIDGETS_EPSS_COMPOSED_CONNECTLANWIDGET_H_
#define SYNCSYS_DEVICE_WIDGET_WIDGETS_EPSS_COMPOSED_CONNECTLANWIDGET_H_

#include <QGroupBox>
#include <QPushButton>

#include "widgets/common/basic/softvalidationspinbox.h"
#include "widgets/common/basic/lampwidget.h"
#include "widgets/common/basic/standardbutton.h"
#include "widgets/export.h"

class WIDGETS_EXPORT ConnectLANWidget : public QGroupBox {
  Q_OBJECT
 public:
  explicit  ConnectLANWidget(QWidget *parent);
  QString getIP();
  void setIP(const QString &new_ip);
  int getPort();
  void setPort(int new_port);
  LampStates getLANStatus();
  void setLANStatus(LampStates);

  void setConnectionStatus(bool status);
  void setConnectionInProgress(bool status);

 signals:
  void connectButtonClickedSignal();
  void disconnectButtonClickedSignal();

 private:
  SoftValidationSpinBox *ip_edit_spinbox;
  SoftValidationSpinBox *port_edit_spinbox;
  LampWidget *lan_status_lamp;
  QPushButton *connect_button;
  QPushButton *disconnect_button;

  bool is_connected;

  void initUI();
  void setConnections();

};

#endif //SYNCSYS_DEVICE_WIDGET_WIDGETS_EPSS_COMPOSED_CONNECTLANWIDGET_H_
