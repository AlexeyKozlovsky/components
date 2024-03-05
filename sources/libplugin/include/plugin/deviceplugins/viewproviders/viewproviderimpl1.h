#ifndef PLUGIN_LIBPLUGIN_INCLUDE_PLUGIN_DEVICEPLUGINS_VIEWPROVIDERS_VIEWPROVIDERIMPL1_H_
#define PLUGIN_LIBPLUGIN_INCLUDE_PLUGIN_DEVICEPLUGINS_VIEWPROVIDERS_VIEWPROVIDERIMPL1_H_

#include <QMap>
#include <utils/baseutils.h>

#include "plugin/deviceplugins/viewprovider.h"
#include <plugin/export.h>


class PLUGIN_EXPORT ViewProviderImpl1: public PluginViewProvider {
 public:
  void setFactoryWidget(const std::shared_ptr<QWidget> &factory_widget) override;
  void setMainManagementWidget(const std::shared_ptr<QWidget> &widget) override;
  void setConnectionWidget(const std::shared_ptr<QWidget> &widget) override;
  void setMonitoringWidget(const std::shared_ptr<QWidget> &widget) override;

  std::shared_ptr<QWidget> getFactoryWidget() override;
  std::shared_ptr<QWidget> getManagementWidget() override;
  std::shared_ptr<QWidget> getConnectionWidget() override;
  std::shared_ptr<QWidget> getMonitoringWidget() override;

  bool hasManagementWidgetByKey(const QString &key) override;
  std::shared_ptr<QWidget> getManagementWidget(const QString &key, QVariant arg) override;

  ErrorCode addExtraWidget(const QString &key, const std::shared_ptr<QWidget> &widget) override;
  ErrorCode removeExtraWidget(const QString &key) override;

 private:
  std::shared_ptr<QWidget> _factory_widget = nullptr;
  std::shared_ptr<QWidget> _main_management_widget = nullptr;
  std::shared_ptr<QWidget> _connection_widget = nullptr;
  std::shared_ptr<QWidget> _monitoring_widget = nullptr;

  QMap<QString, std::shared_ptr<QWidget>> _extra_widgets;
};

#endif //PLUGIN_LIBPLUGIN_INCLUDE_PLUGIN_DEVICEPLUGINS_VIEWPROVIDERS_VIEWPROVIDERIMPL1_H_
