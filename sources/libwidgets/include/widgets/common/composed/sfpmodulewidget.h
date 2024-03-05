#ifndef SYNC_SYS_DEVICE_WIDGET_WIDGETS_COMMON_COMPOSED_SFPMODULEWIDGET_H_
#define SYNC_SYS_DEVICE_WIDGET_WIDGETS_COMMON_COMPOSED_SFPMODULEWIDGET_H_

#include <QGroupBox>
#include "widgets/export.h"

class EditableLedWidget;
class LedWidget;


class WIDGETS_EXPORT SFPModuleWidget: public QGroupBox {
  Q_OBJECT
 public:
  explicit SFPModuleWidget(const QString &sfp_module_name, QWidget *parent = nullptr);

  void setRxLossStatus(bool enabled);
  void setTxFaultStatus(bool status);
  void setRxLoss(bool status);
  void setTxFault(bool status);

signals:
  void rxClicked();
  void txClicked();

  void getSFPParamsSignal();

 private:
  // WIDGET POINTERS
  EditableLedWidget *rx_led_widget;
  EditableLedWidget *tx_led_widget;
  LedWidget *rx_loss_led_widget;
  LedWidget *tx_fault_led_widget;

  void initUI();
};

#endif //SYNC_SYS_DEVICE_WIDGET_WIDGETS_COMMON_COMPOSED_SFPMODULEWIDGET_H_
