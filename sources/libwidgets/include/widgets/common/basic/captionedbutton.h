#ifndef SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_CAPTIONEDBUTTON_H_
#define SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_CAPTIONEDBUTTON_H_

#include <QWidget>

#include "standardbutton.h"
#include "readwritewidget.h"

#include "widgets/export.h"


class WIDGETS_EXPORT CaptionedButton: public QWidget {
  Q_OBJECT
 public:
  explicit CaptionedButton(const QString& above_caption, const QString& inside_caption, QWidget *parent = nullptr);

  void setReadOnlyMode(bool status);

 signals:
  void clicked();

 private:
  StandardButton *button;

  void initUI(const QString &above_caption, const QString &inside_caption);
};

#endif //SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_CAPTIONEDBUTTON_H_
