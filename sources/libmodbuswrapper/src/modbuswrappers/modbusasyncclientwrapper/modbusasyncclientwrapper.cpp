
#include "modbuswrappers/modbusasyncclientwrapper/modbusasyncclientwrapper.h"

ModbusAsyncClientWrapper::ModbusAsyncClientWrapper(const std::shared_ptr<ModbusWrapper> &modbus_wrapper,
                                                   int holding_regs_count,
                                                   int input_regs_count):
                                                   _modbus_wrapper(modbus_wrapper),
                                                   _holding_regs_count(holding_regs_count),
                                                   _input_regs_count(input_regs_count),
                                                   _holding_regs(holding_regs_count),
                                                   _input_regs(input_regs_count) {

}

void ModbusAsyncClientWrapper::process() {
//  _is_processed = true;

//  while (_is_processed) {
    if (_modbus_wrapper != nullptr) {
      _modbus_wrapper->readHoldingRegisters(0, _holding_regs_count, _holding_regs);
      _modbus_wrapper->readInputRegisters(0, _input_regs_count, _input_regs);
    }

//    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

//  _is_processed = false;
//}

ErrorCode ModbusAsyncClientWrapper::connect() {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->connect();
  }

  return result;
}

ErrorCode ModbusAsyncClientWrapper::disconnect() {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->disconnect();
  }

  return result;
}

ErrorCode ModbusAsyncClientWrapper::isConnected(bool &is_connected) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->isConnected(is_connected);
  }

  return result;
}

ErrorCode ModbusAsyncClientWrapper::readHoldingRegister(int reg_num, uint16_t &value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    if (reg_num >= 0 && reg_num < _holding_regs.size()) {
      value = _holding_regs[reg_num];
      result = SUCCESS;
    }
  }

  return result;
}

ErrorCode ModbusAsyncClientWrapper::readHoldingRegisters(int reg_num,
                                                         int reg_count,
                                                         std::vector<uint16_t> &values,
                                                         int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  values.resize(reg_count);
  if (_modbus_wrapper != nullptr) {
    if (reg_num >= 0 && reg_num < _holding_regs.size()) {
      values = std::vector<uint16_t>(_holding_regs.begin() + reg_num, _holding_regs.begin() + reg_num + reg_count);
      result = SUCCESS;
    }
  }

  return result;
}

ErrorCode ModbusAsyncClientWrapper::writeHoldingRegister(int reg_num, uint16_t value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->writeHoldingRegister(reg_num, value, modbus_id);
  }

  return result;
}

ErrorCode ModbusAsyncClientWrapper::writeHoldingRegisters(int reg_num, std::vector<uint16_t> value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->writeHoldingRegisters(reg_num, value, modbus_id);
  }

  return result;
}

ErrorCode ModbusAsyncClientWrapper::readInputRegister(int reg_num, uint16_t &value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    if (reg_num >= 0 && reg_num < _input_regs.size()) {
      value = _input_regs[reg_num];
      result = SUCCESS;
    }
  }

  return result;
}

ErrorCode ModbusAsyncClientWrapper::readInputRegisters(int reg_num,
                                                       int reg_count,
                                                       std::vector<uint16_t> &values,
                                                       int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  values.resize(reg_count);
  if (_modbus_wrapper != nullptr) {
    if (reg_num >= 0 && reg_num < _input_regs.size()) {
      values = std::vector<uint16_t>(_input_regs.begin() + reg_num, _input_regs.begin() + reg_num + reg_count);
      result = SUCCESS;
    }
  }

  return result;
}
