#ifndef LIBDEVICE_DEVICES_MODBUS_MODBUSCOMMAND_H_
#define LIBDEVICE_DEVICES_MODBUS_MODBUSCOMMAND_H_

#include <modbus.h>

#include "devices/command.h"

class ModbusDevice;

using modbus::ModbusClient;

class ModbusCommand: public Command {
 public:
  ModbusCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);
};

#endif //LIBDEVICE_DEVICES_MODBUS_MODBUSCOMMAND_H_
