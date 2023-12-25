#ifndef DIALTEK_LIBDEVICE_MANAGERS_DEVICECONFIG_H_
#define DIALTEK_LIBDEVICE_MANAGERS_DEVICECONFIG_H_

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "devices/device.h"
#include "enums.h"

class DeviceServerBuilder;

class DeviceConfig {
  friend DeviceServerBuilder;
 public:

  std::shared_ptr<Device> createDevice(const std::string &name, ErrorCode *error_code = nullptr);
  void addDevice(const std::shared_ptr<Device> &device, ErrorCode *error_code = nullptr);
  void removeDevice(const std::string &name, ErrorCode *error_code = nullptr);

  std::shared_ptr<Device> getDeviceByName(const std::string &name,
                                          ErrorCode *error_code = nullptr);
  std::shared_ptr<Property> getDevicePropertyByName(const std::shared_ptr<Device> &device,
                                                    const std::string &name,
                                                    ErrorCode *error_code = nullptr);
  std::shared_ptr<Command> getDeviceCommandByName(const std::shared_ptr<Device> &device,
                                                  const std::string &name,
                                                  ErrorCode *error_code);

  const std::map<std::string, std::shared_ptr<Device>> &getAllDevices();

 protected:
  std::map<std::string, std::shared_ptr<Device>> devices;

  DeviceConfig();

  std::shared_ptr<Device> checkDeviceInConfig(const std::string &device_name, ErrorCode *error_code);
  std::shared_ptr<Device> checkDeviceInConfig(const std::shared_ptr<Device> &device, ErrorCode *error_code);
  void checkDeviceNotInConfig(const std::shared_ptr<Device> &device, ErrorCode *error_code);

};

#endif //DIALTEK_LIBDEVICE_MANAGERS_DEVICECONFIG_H_
