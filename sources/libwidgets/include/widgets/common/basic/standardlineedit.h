#ifndef SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_STANDARDLINEEDIT_H_
#define SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_STANDARDLINEEDIT_H_

#include <QLineEdit>

#include "widgets/common/basic/readwritewidget.h"
#include "widgets/export.h"

class WIDGETS_EXPORT StandardLineEdit: public QLineEdit, public ReadWriteWidget {
  Q_OBJECT
 public:
  explicit StandardLineEdit(QWidget *parent = nullptr);

  void setReadOnlyMode(bool status) override;

 private:
  void initUI();
};

#endif //SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_STANDARDLINEEDIT_H_
