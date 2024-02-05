#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_VIEWPROVIDER_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_VIEWPROVIDER_H_

#include <memory>
#include "widgetwrapper.h"


class PluginViewProvider {
 public:
  virtual std::shared_ptr<QWidget> getFactoryWidget() = 0;
  virtual std::shared_ptr<QWidget> getManagementWidget() = 0;

  virtual bool hasManagementWidgetByKey(const QString &key) = 0;
  virtual std::shared_ptr<QWidget> getManagementWidget(const QString &key, QVariant arg = {}) = 0;
};


#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_VIEWPROVIDER_H_
