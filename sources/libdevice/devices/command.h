#ifndef DIALTEK_LIBDEVICE_DEVICES_COMMAND_H_
#define DIALTEK_LIBDEVICE_DEVICES_COMMAND_H_

#include <string>
#include <vector>
#include <memory>

#include "macros.h"
#include "enums.h"

#include "devices/deviceattribute.h"


using device::DeviceState;
using device::ErrorCode;

class Command: public DeviceAttribute {
 public:
  VARIANT executeCommand(const VARIANT &value, ErrorCode *error_code);

  void poll() override;

 protected:
  Command(const std::string &name, const std::shared_ptr<Device> &device);

  virtual void beforeExecute(ErrorCode *error_code = nullptr);
  virtual VARIANT execute(const VARIANT &argin, ErrorCode *error_code = nullptr) = 0;
  virtual void afterExecute(ErrorCode *error_code = nullptr);
};

#endif //DIALTEK_LIBDEVICE_DEVICES_COMMAND_H_
