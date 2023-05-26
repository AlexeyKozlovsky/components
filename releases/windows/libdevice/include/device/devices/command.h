#ifndef DIALTEK_LIBDEVICE_DEVICES_COMMAND_H_
#define DIALTEK_LIBDEVICE_DEVICES_COMMAND_H_

#include <string>
#include <vector>
#include <memory>
#include <mutex>

#include "macros.h"
#include "enums.h"

#include "devices/deviceattribute.h"


using device::DeviceState;
using device::ErrorCode;

class Command: public DeviceAttribute {
 public:
  VARIANT__D executeCommand(const VARIANT__D &value, ErrorCode *error_code);

  void poll() override;

 protected:
  std::mutex exec_mutex;

  Command(const std::string &name, const std::shared_ptr<Device> &device);

  virtual void beforeExecute(ErrorCode *error_code = nullptr);
  virtual VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr) = 0;
  virtual void afterExecute(ErrorCode *error_code = nullptr);
};

#endif //DIALTEK_LIBDEVICE_DEVICES_COMMAND_H_
