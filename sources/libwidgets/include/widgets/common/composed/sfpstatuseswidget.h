#ifndef WIDGETS_LIBWIDGETS_INCLUDE_WIDGETS_COMMON_COMPOSED_SFPSTATUSESWIDGET_H_
#define WIDGETS_LIBWIDGETS_INCLUDE_WIDGETS_COMMON_COMPOSED_SFPSTATUSESWIDGET_H_

#include <memory>

#include <QWidget>
#include <QLabel>
#include "widgets/export.h"


class WIDGETS_EXPORT SFPStatusesWidget: public QWidget {
  Q_OBJECT
 public:
  explicit SFPStatusesWidget(QWidget *parent = nullptr);

  void setTemp(const QString &value);
  void setTxVoltage(const QString &value);
  void setTxAmperage(const QString &value);
  void setTxOpticalPower(const QString &value);
  void setRxPower(const QString &value);

 private:
  QString _temp_postfix = " celc.";
  QString _tx_voltage_postfix = " mV";
  QString _tx_amperage_postfix = " mA";
  QString _tx_optical_power_postfix = " mW";
  QString _rx_power_postfix = " mW";


  QLabel *_temp_value_label = nullptr;
  QLabel *_voltage_value_label = nullptr;
  QLabel *_tx_amperage_shift_value_label = nullptr;
  QLabel *_tx_optical_power_value_label = nullptr;
  QLabel *_rx_signal_power_value_label = nullptr;

  void initUI();
  void setConnections();
};


#endif //WIDGETS_LIBWIDGETS_INCLUDE_WIDGETS_COMMON_COMPOSED_SFPSTATUSESWIDGET_H_
