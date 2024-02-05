
#include "modbuswrappers/modbuswrappermodbusiddecorator/modbusclientmodbusiddecorator.h"


ModbusClientModbusIDDecorator::ModbusClientModbusIDDecorator(const std::shared_ptr<ModbusWrapper> &modbus_wrapper,
                                                             int modbus_id):
                                                             _modbus_wrapper(modbus_wrapper), _modbus_id(modbus_id) {

}

ErrorCode ModbusClientModbusIDDecorator::connect() {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->connect();
  }

  return result;
}

ErrorCode ModbusClientModbusIDDecorator::disconnect() {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->disconnect();
  }

  return result;
}

ErrorCode ModbusClientModbusIDDecorator::isConnected(bool &is_connected) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->isConnected(is_connected);
  }

  return result;
}

ErrorCode ModbusClientModbusIDDecorator::readHoldingRegister(int reg_num, uint16_t &value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->readHoldingRegister(reg_num, value, _modbus_id);
  }

  return result;
}

ErrorCode ModbusClientModbusIDDecorator::readHoldingRegisters(int reg_num,
                                                              int reg_count,
                                                              std::vector<uint16_t> &values,
                                                              int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->readHoldingRegisters(reg_num, reg_count, values, _modbus_id);
  }

  return result;
}

ErrorCode ModbusClientModbusIDDecorator::writeHoldingRegister(int reg_num,
                                                              uint16_t value,
                                                              int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->writeHoldingRegister(reg_num, value, _modbus_id);
  }

  return result;
}

ErrorCode ModbusClientModbusIDDecorator::writeHoldingRegisters(int reg_num,
                                                               std::vector<uint16_t> value,
                                                               int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->writeHoldingRegisters(reg_num, value, _modbus_id);
  }

  return result;
}

ErrorCode ModbusClientModbusIDDecorator::readInputRegister(int reg_num, uint16_t &value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->readInputRegister(reg_num, value, _modbus_id);
  }

  return result;
}

ErrorCode ModbusClientModbusIDDecorator::readInputRegisters(int reg_num,
                                                            int reg_count,
                                                            std::vector<uint16_t> &values,
                                                            int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->readInputRegisters(reg_num, reg_count, values, _modbus_id);
  }

  return result;
}
