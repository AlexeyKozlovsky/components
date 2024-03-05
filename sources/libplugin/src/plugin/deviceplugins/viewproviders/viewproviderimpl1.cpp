#include "plugin/deviceplugins/viewproviders/viewproviderimpl1.h"

#include <memory>
#include <QString>
#include <QVariant>

void ViewProviderImpl1::setFactoryWidget(const std::shared_ptr<QWidget> &factory_widget) {
  if (factory_widget != nullptr) {
    _factory_widget = factory_widget;
  }
}

void ViewProviderImpl1::setMainManagementWidget(const std::shared_ptr<QWidget> &widget) {
  if (widget != nullptr) {
    _main_management_widget = widget;
  }
}

void ViewProviderImpl1::setConnectionWidget(const std::shared_ptr<QWidget> &widget) {
  if (_connection_widget != nullptr) {
    _connection_widget = widget;
  }
}

void ViewProviderImpl1::setMonitoringWidget(const std::shared_ptr<QWidget> &widget) {
  if (widget != nullptr) {
    _monitoring_widget = widget;
  }
}


std::shared_ptr<QWidget> ViewProviderImpl1::getFactoryWidget() {
  return _factory_widget;
}

std::shared_ptr<QWidget> ViewProviderImpl1::getManagementWidget() {
  return _main_management_widget;
}

std::shared_ptr<QWidget> ViewProviderImpl1::getConnectionWidget() {
  return _connection_widget;
}

std::shared_ptr<QWidget> ViewProviderImpl1::getMonitoringWidget() {
  return _monitoring_widget;
}

bool ViewProviderImpl1::hasManagementWidgetByKey(const QString &key) {
  bool result = _extra_widgets.contains(key);
  return result;
}

std::shared_ptr<QWidget> ViewProviderImpl1::getManagementWidget(const QString &key, QVariant arg) {
  std::shared_ptr<QWidget> result = nullptr;

  if (hasManagementWidgetByKey(key)) {
    result = _extra_widgets[key];
  }

  return result;
}

ErrorCode ViewProviderImpl1::addExtraWidget(const QString &key, const std::shared_ptr<QWidget> &widget) {
  auto result = OPERATION_INTERRUPTED;

  if (!hasManagementWidgetByKey(key)) {
    _extra_widgets.insert(key, widget);
  }

  return result;
}

ErrorCode ViewProviderImpl1::removeExtraWidget(const QString &key) {
  auto result = OPERATION_INTERRUPTED;

  if (hasManagementWidgetByKey(key)) {
    _extra_widgets.remove(key);
  }

  return result;
}