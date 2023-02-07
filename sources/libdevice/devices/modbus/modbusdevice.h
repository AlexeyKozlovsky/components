#ifndef LIBDEVICE_DEVICES_MODBUS_MODBUSDEVICE_H_
#define LIBDEVICE_DEVICES_MODBUS_MODBUSDEVICE_H_

#include <modbus.h>

#include "devices/device.h"

using modbus::ModbusClient;

class ModbusDevice: public Device {
 public:
  static std::shared_ptr<ModbusDevice> createModbusDevice(const std::string &name,
                                                          const std::string &ip,
                                                          int port,
                                                          int modbus_id,
                                                          ErrorCode *error_code = nullptr);

  const std::shared_ptr<ModbusClient> &getModbusClient();

  const std::string &getIP() const;
  int getPort() const;
  int getModbusID() const;

 protected:
  std::string ip;
  int port;
  int modbus_id;

  std::shared_ptr<ModbusClient> modbus_client;

  ModbusDevice(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client);
};

#endif //LIBDEVICE_DEVICES_MODBUS_MODBUSDEVICE_H_
