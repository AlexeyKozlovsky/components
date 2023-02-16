#ifndef LIBDEVICE_DEVICES_MODBUS_MODBUSDEVICE_H_
#define LIBDEVICE_DEVICES_MODBUS_MODBUSDEVICE_H_

#include <modbus.h>

#include "devices/device.h"

#define MODBUS_RW_DEVICE_ERROR_HANDLE(condition, positive_instruction, negative_instruction, error_code) {modbus::ModbusResult error_status; \
MODBUS_RW_ERROR_HANDLE( \
    condition, \
    SET_ERROR_CODE_SUCCESS(error_code)                                                                                                                                        \
    positive_instruction;, \
        if (error_status == modbus::NO_SOCKET_CONNECTION || error_status == modbus::TCP_TIMEOUT_ERROR) \
          device->changeState(DeviceState::CLOSE);     \
        negative_instruction;, \
    error_status \
) SET_ERROR_CODE(error_code, device::toErrorCode(error_status));}

using modbus::ModbusClient;

class ModbusDevice: public Device {
 public:
  static std::shared_ptr<ModbusDevice> createModbusDevice(const std::string &name,
                                                          const std::string &ip,
                                                          int port,
                                                          int modbus_id,
                                                          ErrorCode *error_code = nullptr);

  const std::shared_ptr<ModbusClient> &getModbusClient();

  std::string getIP() const;
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
