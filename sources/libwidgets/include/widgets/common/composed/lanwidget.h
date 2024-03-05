#ifndef CRATE_SYNCSYS_CLIENT_WIDGETS_COMMON_COMPOSED_LANWIDGET_H_
#define CRATE_SYNCSYS_CLIENT_WIDGETS_COMMON_COMPOSED_LANWIDGET_H_

#include <QGroupBox>
#include "widgets/export.h"

class LedWidget;
class StandardLineEdit;
class StandardButton;


class WIDGETS_EXPORT LanWidget: public QGroupBox {
  Q_OBJECT
 public:
  explicit LanWidget(QWidget *parent = nullptr);

  void setConnectionStatus(bool status);
  void setIP(const QString &ip);
  void setPort(int port);

 signals:
  /**
   * Сигнал для того, чтобы обозначить попытку коннекта или дисконнекта
   * @param connection -- true - если коннект, false -- иначе
   */
  void connect(bool connection);


 public slots:
  // СЛОТЫ, НЕОБХОДИМЫЕ ДЛЯ ДАННОГО ВИДЖЕТА
  void connectButtonClickedSlot();
  void disconnectButtonClickedSlot();

 private:
  LedWidget *connection_status_led_widget;
  StandardLineEdit *ip_line_edit;
  StandardLineEdit *port_line_edit;

  StandardButton *connect_button;
  StandardButton *disconnect_button;

  /**
   * Метод для инициализации GUI
   */
  void initUI();

};

#endif //CRATE_SYNCSYS_CLIENT_WIDGETS_COMMON_COMPOSED_LANWIDGET_H_
