#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_PLUGINPROVIDER_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_PLUGINPROVIDER_H_

#include <memory>

#include <QWidget>

#include <utils/baseutils.h>

#include "dataprovider.h"
#include "commandprovider.h"
#include "viewprovider.h"
#include "connectionmanager.h"
#include "serializer.h"
#include "serviceprovider.h"

class PluginProvider {
 public:
  explicit PluginProvider(const std::shared_ptr<PluginDataProvider> &data_provider,
                          const std::shared_ptr<ConnectionManager> &connection_manager,
                          const std::shared_ptr<PluginCommandProvider> &command_provider,
                          const std::shared_ptr<PluginViewProvider> &view_provider,
                          const std::shared_ptr<PluginSerializer> &serializer,
                          const std::shared_ptr<PluginServiceProvider> &service_provider);

  std::string getPluginName();
  std::string getPluginDescription();
  std::string getPluginDeveloperInfo();
  std::string getPluginVersion();
  QIcon *getPluginIcon();
  
  std::string getDeviceName();
  std::string getDeviceDescription();
  std::string getDeviceFirmwareVersion();
  std::string getDeviceDeveloperInfo();
  
  bool getHWConnectionStatus();
  bool getServerConnectionStatus();

  ErrorCode connectHW(bool connect);
  ErrorCode connectServer(bool connect);

  DeviceState getDeviceState();

  std::shared_ptr<QWidget> getFactoryWidget();
  std::shared_ptr<QWidget> getManagementWidget();
  bool hasManagementWidgetByKey(const std::string &key);
  std::shared_ptr<QWidget> getManagementWidget(const std::string &key);
  bool hasCommandByKey(const std::string &key);
  CommandResponse executeCommandByKey(CommandRequest request);

  std::shared_ptr<IProcessable> getBackgroundTask();

  bool hasBackgroundTaskByKey(const std::string &key);
  std::shared_ptr<IProcessable> getBackgroundTask(const std::string &key);

 private:
  std::shared_ptr<PluginDataProvider> _data_provider = nullptr;
  std::shared_ptr<ConnectionManager> _connection_manager = nullptr;
  std::shared_ptr<PluginCommandProvider> _command_provider = nullptr;
  std::shared_ptr<PluginViewProvider> _view_provider = nullptr;
  std::shared_ptr<PluginSerializer> _serializer = nullptr;
  std::shared_ptr<PluginServiceProvider> _service_provider = nullptr;
};


#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_PLUGINPROVIDER_H_