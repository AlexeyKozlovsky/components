#ifndef SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_STANDARDPROPERTYLABEL_H_
#define SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_STANDARDPROPERTYLABEL_H_

#include <QLabel>
#include "widgets/export.h"

class WIDGETS_EXPORT StandardPropertyLabel: public QLabel {
  Q_OBJECT
 public:
  explicit StandardPropertyLabel(const QString &caption, int font_size, QWidget *parent = nullptr);
  explicit StandardPropertyLabel(const QString &caption, QWidget *parent = nullptr);

 private:
  void initUI(int font_size);
};

#endif //TSSS_DEVICE_WIDGET_WIDGETS_COMPONENTS_STANDARDPROPERTYLABEL_H_
