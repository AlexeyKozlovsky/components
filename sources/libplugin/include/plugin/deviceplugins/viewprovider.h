#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_VIEWPROVIDER_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_VIEWPROVIDER_H_

#include <memory>

#include <QVariant>

#include <utils/baseutils.h>

#include "widgetwrapper.h"


class PluginViewProvider {
 public:
  virtual void setFactoryWidget(const std::shared_ptr<QWidget> &factory_widget) = 0;
  virtual void setMainManagementWidget(const std::shared_ptr<QWidget> &widget) = 0;
  virtual void setConnectionWidget(const std::shared_ptr<QWidget> &widget) = 0;
  virtual void setMonitoringWidget(const std::shared_ptr<QWidget> &widget) = 0;

  virtual std::shared_ptr<QWidget> getFactoryWidget() = 0;
  virtual std::shared_ptr<QWidget> getManagementWidget() = 0;
  virtual std::shared_ptr<QWidget> getConnectionWidget() = 0;
  virtual std::shared_ptr<QWidget> getMonitoringWidget() = 0;

  virtual bool hasManagementWidgetByKey(const QString &key) = 0;
  virtual std::shared_ptr<QWidget> getManagementWidget(const QString &key, QVariant arg = {}) = 0;

  virtual ErrorCode addExtraWidget(const QString &key, const std::shared_ptr<QWidget> &widget) = 0;
  virtual ErrorCode removeExtraWidget(const QString &key) = 0;
};


#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_VIEWPROVIDER_H_
