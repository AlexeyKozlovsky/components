#ifndef PLUGIN_LIBPLUGIN_INCLUDE_PLUGIN_DEVICEPLUGINS_WIDGETWRAPPER_H_
#define PLUGIN_LIBPLUGIN_INCLUDE_PLUGIN_DEVICEPLUGINS_WIDGETWRAPPER_H_

#include <QWidget>
#include <plugin/export.h>


class PLUGIN_EXPORT WidgetWrapper: public QWidget {
 public:
  explicit WidgetWrapper(QWidget *parent = nullptr);

  virtual void setArg(QVariant arg) = 0;
  virtual QVariant getArg() = 0;
};

#endif //PLUGIN_LIBPLUGIN_INCLUDE_PLUGIN_DEVICEPLUGINS_WIDGETWRAPPER_H_
