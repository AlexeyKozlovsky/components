#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_DEVICEPACKFACTORY_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_DEVICEPACKFACTORY_H_

#include <string>
#include <memory>

struct ConnectWrapperInfo {
  std::string ip;
  int port = 4001;
  int modbus_id = 1;

  std::string device_name;

  int poll_period = 500;
};

class DevicePackFactory {
 public:
  virtual std::shared_ptr<BaseDevice> createCPSDevicePack(const std::string &uid,
                                                          const std::shared_ptr<BaseDeviceDTO> &dto,
                                                          const ConnectWrapperInfo &connect_wrapper_info) = 0;
};


#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_DEVICEPACKFACTORY_H_
