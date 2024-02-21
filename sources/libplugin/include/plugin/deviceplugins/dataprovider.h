#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_DATAPROVIDER_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_DATAPROVIDER_H_

#include <string>
#include <memory>

#include <QIcon>

#include <utils/baseutils.h>


class PluginDataProvider {
 public:
  virtual std::string getPluginName() = 0;
  virtual std::string getPluginDescription() = 0;
  virtual std::string getPluginVersion() = 0;
  virtual std::string getPluginDeveloperInfo() = 0;
  virtual QIcon *getPluginIcon() = 0;

  virtual std::string getDeviceName() = 0;
  virtual void setDeviceName(const std::string &value) = 0;
  virtual std::string getDeviceDescription() = 0;
  virtual void setDeviceDescription(const std::string &value) = 0;
  virtual std::string getDeviceType() = 0;
  virtual std::string getDeviceFirmwareVersion() = 0;
  virtual std::string getDeviceDeveloperInfo() = 0;

  virtual DeviceState getDeviceState() = 0;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_DATAPROVIDER_H_
