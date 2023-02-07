#include "epssdevice.h"

std::shared_ptr<EPSSDevice> EPSSDevice::createEPSSDevice(const std::string &name,
                                                         const std::string &ip,
                                                         int port,
                                                         int modbus_id,
                                                         ErrorCode *error_code) {
  auto base_modbus_device = ModbusDevice::createModbusDevice(name, ip, port, modbus_id, error_code);
  IS_ERROR(
      error_code,
      return nullptr;
      );

  auto device = std::static_pointer_cast<EPSSDevice>(base_modbus_device);

  SET_ERROR_CODE(error_code, ErrorCode::SUCCESS);
  return device;
}

EPSSDevice::EPSSDevice(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client) :
  ModbusDevice(name, modbus_client) {

}
