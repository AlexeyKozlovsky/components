#ifndef LIBDEVICE_DEVICES_MODBUS_MODBUSPROPERTY_H_
#define LIBDEVICE_DEVICES_MODBUS_MODBUSPROPERTY_H_

#include <modbus.h>

#include "devices/property.h"

using modbus::ModbusClient;
class ModbusDevice;


class ModbusProperty: public Property {
 public:
  ModbusProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  void beforeRead(ErrorCode *error_code = nullptr) override;
  void beforeWrite(ErrorCode *error_code = nullptr) override;

 private:
  void beforeProperty(ErrorCode *error_code = nullptr);
};

#endif //LIBDEVICE_DEVICES_MODBUS_MODBUSPROPERTY_H_
