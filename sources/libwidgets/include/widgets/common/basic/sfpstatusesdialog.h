#ifndef SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_SFPSTATUSESDIALOG_H_
#define SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_SFPSTATUSESDIALOG_H_

#include "widgets/utils.h"

#include <QDialog>


class SFPStatusesDialog: public QDialog {
  Q_OBJECT
 public:
  explicit SFPStatusesDialog(dev::SFPParameters statuses, QWidget *parent = nullptr);

 private:
  void initUI(dev::SFPParameters statuses);
};

#endif //SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_SFPSTATUSESDIALOG_H_
