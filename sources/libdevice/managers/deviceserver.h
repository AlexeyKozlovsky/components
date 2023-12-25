#ifndef DIALTEK_LIBDEVICE_MANAGERS_DEVICESERVER_H_
#define DIALTEK_LIBDEVICE_MANAGERS_DEVICESERVER_H_

#include <queue>
#include <mutex>
#include <thread>
#include <chrono>
#include <atomic>

#include "enums.h"
#include "devices/device.h"
#include "deviceconfig.h"

class DeviceServer;
class DeviceServerBuilder;

class DeviceServer {
  friend DeviceServerBuilder;
 public:
  VARIANT__D readProperty(const std::shared_ptr<Device> &device,
                          const std::string &property_name,
                          ErrorCode *error_code = nullptr);
  void writeProperty(const std::shared_ptr<Device> &device,
                     const std::string &property_name,
                     const VARIANT__D &value,
                     ErrorCode *error_code = nullptr);
  VARIANT__D executeCommand(const std::shared_ptr<Device> &device,
                            const std::string &command_name,
                            const VARIANT__D &value,
                            ErrorCode *error_code = nullptr);

  inline const std::shared_ptr<DeviceConfig> &getDeviceConfig() {
    return device_config;
  }

  void startPolling(ErrorCode *error_code = nullptr);
  void stopPolling(ErrorCode *error_code = nullptr);
  void polling();


 protected:
  std::shared_ptr<DeviceConfig> device_config;

  std::atomic<bool> polling_processing_flag;
  std::mutex polling_mutex;
  std::thread polling_thread;

  /**
   * Тик поллинга. Поллинговый поток ждет это время, чтобы остальные запросы могли работать.
   * Измеряется в мс
   */
  int polling_tact;

 private:
  std::chrono::time_point<std::chrono::system_clock> time_point;

  DeviceServer();
};


class DeviceServerBuilder {
 public:
  static std::shared_ptr<DeviceServerBuilder> getInstance();
  std::shared_ptr<DeviceServer> createDeviceServer();

 private:
  static std::shared_ptr<DeviceServerBuilder> instance;

  DeviceServerBuilder();
};

#endif //DIALTEK_LIBDEVICE_MANAGERS_DEVICESERVER_H_
