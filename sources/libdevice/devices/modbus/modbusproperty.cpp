#include "modbusproperty.h"

#include "devices/modbus/modbusdevice.h"


ModbusProperty::ModbusProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device):
    Property(name, modbus_device) {

}

void ModbusProperty::beforeRead(ErrorCode *error_code) {
  beforeProperty(error_code);
  Property::beforeRead(error_code);
}
void ModbusProperty::beforeWrite(ErrorCode *error_code) {
  beforeProperty(error_code);
  Property::beforeWrite(error_code);
}

void ModbusProperty::beforeProperty(ErrorCode *error_code) {
  auto current_state = device->getState();
  if (current_state != DeviceState::OPEN) {
    SET_ERROR_CODE(error_code, ErrorCode::OPERATION_INTERRUPTED);
  }
}
