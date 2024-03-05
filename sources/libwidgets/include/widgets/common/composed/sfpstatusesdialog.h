#ifndef WIDGETS_LIBWIDGETS_INCLUDE_WIDGETS_COMMON_COMPOSED_SFPSTATUSESDIALOG_H_
#define WIDGETS_LIBWIDGETS_INCLUDE_WIDGETS_COMMON_COMPOSED_SFPSTATUSESDIALOG_H_

#include <QDialog>

#include "sfpstatuseswidget.h"
#include "widgets/export.h"


class WIDGETS_EXPORT SFPStatusesDialog: public QDialog {
 public:
  explicit SFPStatusesDialog(QWidget *parent = nullptr);

  void setTemp(const QString &value);
  void setTxVoltage(const QString &value);
  void setTxAmperage(const QString &value);
  void setTxOpticalPower(const QString &value);
  void setRxPower(const QString &value);

 private:
  SFPStatusesWidget *_sfp_statuses_widget = nullptr;

  void initUI();
  void setConnections();
};

#endif //WIDGETS_LIBWIDGETS_INCLUDE_WIDGETS_COMMON_COMPOSED_SFPSTATUSESDIALOG_H_
