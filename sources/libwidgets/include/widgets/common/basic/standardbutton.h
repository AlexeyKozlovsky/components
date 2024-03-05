#ifndef SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_STANDARDBUTTON_H_
#define SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_STANDARDBUTTON_H_

#include <QPushButton>

#include "widgets/common/basic/readwritewidget.h"
#include "widgets/export.h"

class WIDGETS_EXPORT StandardButton: public QPushButton, public ReadWriteWidget {
  Q_OBJECT
 public:
  explicit StandardButton(const QString& caption, QWidget *parent = nullptr);

  void setReadOnlyMode(bool status) override;
 private:
  void initUI();

  void paintEvent(QPaintEvent *) override;

};

#endif // SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_STANDARDBUTTON_H_
