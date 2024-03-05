#ifndef SYCSYS_DEVICE_WIDGET_WIDGETS_BASIC_LAMPWIDGET_H_
#define SYCSYS_DEVICE_WIDGET_WIDGETS_BASIC_LAMPWIDGET_H_

#include "widgets/stylesheets/default.h"
#include "widgets/enums.h"

#include <QWidget>
#include "widgets/export.h"

class WIDGETS_EXPORT LampWidget : public QWidget{
 public:
  explicit LampWidget(QWidget *parent = nullptr);
  void setState(LampStates new_state);
  void setState(bool new_state);
  LampStates getState() const;

 private:
  LampStates state;

  void initUI();
  void setNewStyleSheet();
};

#endif //OU_1U_WIDGETS_BASIC_LAMPWIDGET_H_
