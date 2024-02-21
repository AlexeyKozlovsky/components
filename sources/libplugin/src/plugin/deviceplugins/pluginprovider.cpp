
#include <utility>

#include "plugin/deviceplugins/pluginprovider.h"


PluginProvider::PluginProvider(const std::shared_ptr<PluginDataProvider> &data_provider,
                               const std::shared_ptr<ConnectionManager> &connection_manager,
                               const std::shared_ptr<PluginCommandProvider> &command_provider,
                               const std::shared_ptr<PluginViewProvider> &view_provider,
                               const std::shared_ptr<PluginSerializer> &serializer,
                               const std::shared_ptr<PluginServiceProvider> &service_provider):
                               _data_provider(data_provider),
                               _connection_manager(connection_manager),
                               _command_provider(command_provider),
                               _view_provider(view_provider),
                               _serializer(serializer),
                               _service_provider(service_provider) {

}

std::string PluginProvider::getPluginName() {
  std::string result;

  if (_data_provider != nullptr) {
    result = _data_provider->getPluginName();
  }

  return result;
}

std::string PluginProvider::getPluginDescription() {
  std::string result;

  if (_data_provider != nullptr) {
    result = _data_provider->getPluginDescription();
  }

  return result;
}

std::string PluginProvider::getPluginDeveloperInfo() {
  std::string result;

  if (_data_provider != nullptr) {
    result = _data_provider->getPluginDeveloperInfo();
  }

  return result;
}

std::string PluginProvider::getPluginVersion() {
  std::string result;

  if (_data_provider != nullptr) {
    result = _data_provider->getPluginVersion();
  }

  return result;
}

QIcon *PluginProvider::getPluginIcon() {
  QIcon *result = nullptr;

  if (_data_provider != nullptr) {
    result = _data_provider->getPluginIcon();
  }

  return result;
}

std::string PluginProvider::getDeviceName() {
  std::string result;

  if (_data_provider != nullptr) {
    result = _data_provider->getDeviceName();
  }

  return result;
}

void PluginProvider::setDeviceName(const std::string &value) {
  if (_data_provider != nullptr) {
    _data_provider->setDeviceName(value);
  }
}

std::string PluginProvider::getDeviceDescription() {
  std::string result;

  if (_data_provider != nullptr) {
    result = _data_provider->getDeviceDescription();
  }

  return result;
}

void PluginProvider::setDeviceDescription(const std::string &value) {
  if (_data_provider != nullptr) {
    _data_provider->setDeviceDescription(value);
  }
}

std::string PluginProvider::getDeviceFirmwareVersion() {
  std::string result;

  if (_data_provider != nullptr) {
    result = _data_provider->getDeviceFirmwareVersion();
  }

  return result;
}

std::string PluginProvider::getDeviceDeveloperInfo() {
  std::string result;

  if (_data_provider != nullptr) {
    result = _data_provider->getDeviceDeveloperInfo();
  }

  return result;
}

bool PluginProvider::getHWConnectionStatus() {
  bool result = false;

  if (_connection_manager != nullptr) {
    result = _connection_manager->getHWConnectionStatus();
  }

  return result;
}

bool PluginProvider::getServerConnectionStatus() {
  bool result = false;

  if (_connection_manager != nullptr) {
    result = _connection_manager->getServerConnectionStatus();
  }

  return result;
}

ErrorCode PluginProvider::connectHW(bool connect) {
  ErrorCode result = OPERATION_INTERRUPTED;

  if (_connection_manager != nullptr) {
    result = _connection_manager->connectHW(connect);
  }

  return result;
}

ErrorCode PluginProvider::connectServer(bool connect) {
  ErrorCode result = OPERATION_INTERRUPTED;

  if (_connection_manager != nullptr) {
    result = _connection_manager->connectHW(connect);
  }

  return result;
}

DeviceState PluginProvider::getDeviceState() {
  DeviceState result = EMPTY;

  if (_data_provider != nullptr) {
    result = _data_provider->getDeviceState();
  }

  return result;
}

std::shared_ptr<QWidget> PluginProvider::getFactoryWidget() {
  std::shared_ptr<QWidget> result = nullptr;

  if (_view_provider != nullptr) {
    result = _view_provider->getFactoryWidget();
  }

  return result;
}

std::shared_ptr<QWidget> PluginProvider::getManagementWidget() {
  std::shared_ptr<QWidget> result = nullptr;

  if (_view_provider != nullptr) {
    result = _view_provider->getManagementWidget();
  }

  return result;
}

bool PluginProvider::hasManagementWidgetByKey(const QString &key) {
  bool result = false;

  if (_view_provider != nullptr) {
    result = _view_provider->hasManagementWidgetByKey(key);
  }

  return result;
}

std::shared_ptr<QWidget> PluginProvider::getManagementWidget(const QString &key, QVariant arg) {
  std::shared_ptr<QWidget> result = nullptr;


  if (_view_provider != nullptr) {
    result = _view_provider->getManagementWidget(key, std::move(arg));
  }

  return result;
}

bool PluginProvider::hasCommandByKey(const QString &key) {
  bool result = false;

  if (_command_provider != nullptr) {
    result = _command_provider->hasCommand(key);
  }

  return result;
}

CommandResponse PluginProvider::executeCommandByKey(CommandRequest request) {
  CommandResponse response{};

  if (_command_provider != nullptr) {
    response = _command_provider->executeCommand(request);
  }

  return response;
}

std::shared_ptr<IProcessable> PluginProvider::getBackgroundTask() {
  std::shared_ptr<IProcessable> result = nullptr;

  if (_service_provider != nullptr) {
    result = _service_provider->getBackgroundTask();
  }

  return result;
}

bool PluginProvider::hasBackgroundTaskByKey(const std::string &key) {
  bool result = false;

  if (_service_provider != nullptr) {
    result = _service_provider->hasBackgroundTaskByKey(key);
  }

  return result;
}

std::shared_ptr<IProcessable> PluginProvider::getBackgroundTask(const std::string &key) {
  std::shared_ptr<IProcessable> result = nullptr;

  if (_service_provider != nullptr) {
    result = _service_provider->getBackgroundTaskByKey(key);
  }

  return result;
}

std::string PluginProvider::serialize() {
  std::string result;

  if (_serializer != nullptr) {
    result = _serializer->serialize();
  }

  return result;
}

ErrorCode PluginProvider::deserialize(const std::string &data) {
  ErrorCode result = OPERATION_INTERRUPTED;

  if (_serializer != nullptr) {
    result = _serializer->deserialize(data);
  }

  return result;
}


// TODO: Дописать базовые реализации тестового плагина