#ifndef DIALTEK_LIBDEVICE_DEVICES_DEVICEATTRIBUTE_H_
#define DIALTEK_LIBDEVICE_DEVICES_DEVICEATTRIBUTE_H_

#include <string>
#include <set>
#include <chrono>
#include <functional>
#include <memory>
#include <utils/baseutils.h>

#include "enums.h"

using device::DeviceState;

class Device;

/**
 * Базовый класс для свойств и команд девайса. НЕ ПУТАТЬ С TANGO ATTRIBUTE (НЕ АНАЛОГИЯ)
 */
class DeviceAttribute {
 public:
  inline const std::string &getName() const {
    return name;
  }

  inline void setName(const std::string &name) {
    this->name = name;
  }

  inline const std::string &getDescription() const {
    return description;
  }

  inline void setDescription(const std::string &description) {
    this->description = description;
  }

  inline const std::set<DeviceState> &getAvailableStates() const {
    return available_states;
  }

  void setPollingCallback(const std::function<void(VARIANT__D&, ErrorCode*)> &callback);
  void setPollingPeriod(int polling, ErrorCode *error_code);
  virtual void poll() = 0;

  inline int getPollingPeriod() const {
    return polling_period;
  }

  inline bool operator ==(const DeviceAttribute &attribute) {
    return name == attribute.name;
  }

  inline bool operator <(const DeviceAttribute &attribute) {
    return name < attribute.name;
  }

 protected:
  std::string name;
  std::string description;
  std::shared_ptr<Device> device;

  std::set<DeviceState> available_states;

  /**
   * Период поллинга. Если 0, то атрибут не поллится. Измеряется в миллисекундах
   */

  int polling_period;

  /**
   * Время последнего поллинга свойства.
   */
  std::chrono::time_point<std::chrono::system_clock> last_polled_time = std::chrono::system_clock::now();
  std::function<void(VARIANT__D&, ErrorCode*)> polling_callback;


  DeviceAttribute(const std::string &name, const std::shared_ptr<Device> &device);
};

#endif //DIALTEK_LIBDEVICE_DEVICES_DEVICEATTRIBUTE_H_
