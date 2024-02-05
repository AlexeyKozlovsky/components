
#include "modbuswrappers/modbusasyncclientwrapper/modbusasyncclientwrapper2.h"


static const int DEFAULT_INPUT_FIRST_REG_NUM = 0;
static const int DEFAULT_HOLDING_FIRST_REG_NUM = 0;

static const int DEFAULT_INPUT_REG_PER_REQUEST_COUNT = 30;
static const int DEFAULT_HOLDING_REG_PER_REQUEST_COUNT = 30;


ModbusAsyncClientWrapper2::ModbusAsyncClientWrapper2(const std::shared_ptr<ModbusWrapper> &modbus_wrapper,
                                                   int holding_regs_count,
                                                   int input_regs_count):
    _modbus_wrapper(modbus_wrapper),
    _holding_regs_count(holding_regs_count),
    _input_regs_count(input_regs_count),
    _holding_regs(holding_regs_count),
    _input_regs(input_regs_count) {
}

void ModbusAsyncClientWrapper2::process() {
  if (_modbus_wrapper != nullptr) {
    auto error_code = _modbus_wrapper->readInputRegisters(0, _input_regs_count, _input_regs);
    error_code = _modbus_wrapper->readHoldingRegisters(0, _holding_regs_count, _holding_regs);

    // TODO: Добавить потом логирование и обработку ошибок

  }
}


ErrorCode ModbusAsyncClientWrapper2::connect() {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->connect();
  }

  return result;
}

ErrorCode ModbusAsyncClientWrapper2::disconnect() {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->disconnect();
  }

  return result;
}

ErrorCode ModbusAsyncClientWrapper2::isConnected(bool &is_connected) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->isConnected(is_connected);
  }

  return result;
}

ErrorCode ModbusAsyncClientWrapper2::readHoldingRegister(int reg_num, uint16_t &value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    if (reg_num >= 0 && reg_num < _holding_regs.size()) {
      value = _holding_regs[reg_num];
      result = SUCCESS;
    }
  }

  return result;
}

ErrorCode ModbusAsyncClientWrapper2::readHoldingRegisters(int reg_num,
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

ErrorCode ModbusAsyncClientWrapper2::writeHoldingRegister(int reg_num, uint16_t value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->writeHoldingRegister(reg_num, value, modbus_id);

    // Обновление

    if (result == SUCCESS) {
      uint16_t reg_value;
      result = _modbus_wrapper->readHoldingRegister(reg_num, reg_value, modbus_id);

      if (result == SUCCESS) {
        if (reg_num >= 0 && reg_num < _holding_regs.size()) {
          _holding_regs[reg_num] = reg_value;
        }
      }
    }
  }

  return result;
}

ErrorCode ModbusAsyncClientWrapper2::writeHoldingRegisters(int reg_num, std::vector<uint16_t> value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->writeHoldingRegisters(reg_num, value, modbus_id);

    // Обновление
    if (result == SUCCESS) {
      uint16_t reg_count = value.size();
      std::vector<uint16_t> reg_values;
      result = _modbus_wrapper->readHoldingRegisters(reg_num, reg_count, reg_values, modbus_id);

      if (result == SUCCESS) {
        if (reg_num >= 0 && reg_num < _holding_regs.size() && reg_num + reg_count <= _holding_regs.size()) {
          for (int i = reg_num; i < reg_num + reg_count; i++) {
            _holding_regs[i] = reg_values[i - reg_num];
          }
        }
      }
    }
  }

  return result;
}

ErrorCode ModbusAsyncClientWrapper2::readInputRegister(int reg_num, uint16_t &value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;
  if (_modbus_wrapper != nullptr) {
    if (reg_num >= 0 && reg_num < _input_regs.size()) {
      value = _input_regs[reg_num];
      result = SUCCESS;
    }
  }

  return result;
}

ErrorCode ModbusAsyncClientWrapper2::readInputRegisters(int reg_num,
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

const std::vector<uint16_t> &ModbusAsyncClientWrapper2::getHoldingRegs() {
  return _holding_regs;
}

const std::vector<uint16_t> &ModbusAsyncClientWrapper2::getInputRegs() {
  return _input_regs;
}
