
#include "modbuswrappers/modbusasyncclientwrapper/modbusasyncclientwrapper.h"

static const int DEFAULT_INPUT_FIRST_REG_NUM = 0;
static const int DEFAULT_HOLDING_FIRST_REG_NUM = 0;

static const int DEFAULT_INPUT_REG_PER_REQUEST_COUNT = 30;
static const int DEFAULT_HOLDING_REG_PER_REQUEST_COUNT = 30;


ModbusAsyncClientWrapper::ModbusAsyncClientWrapper(const std::shared_ptr<ModbusWrapper> &modbus_wrapper,
                                                   int holding_regs_count,
                                                   int input_regs_count):
                                                   _modbus_wrapper(modbus_wrapper),
                                                   _holding_regs_count(holding_regs_count),
                                                   _input_regs_count(input_regs_count),
                                                   _holding_regs(holding_regs_count),
                                                   _input_regs(input_regs_count) {
  _input_regs_divider = std::make_shared<RegReadDivider>(DEFAULT_INPUT_FIRST_REG_NUM,
                                                           _input_regs_count,
                                                           DEFAULT_INPUT_REG_PER_REQUEST_COUNT);

  _holding_regs_divider = std::make_shared<RegReadDivider>(DEFAULT_HOLDING_FIRST_REG_NUM,
                                                           _holding_regs_count,
                                                           DEFAULT_HOLDING_REG_PER_REQUEST_COUNT);
}

void ModbusAsyncClientWrapper::process() {
////  _is_processed = true;
//
////  while (_is_processed) {
//    if (_modbus_wrapper != nullptr) {
//      _modbus_wrapper->readHoldingRegisters(0, _holding_regs_count, _holding_regs);
//      _modbus_wrapper->readInputRegisters(0, _input_regs_count, _input_regs);
//    }
//
////    std::this_thread::sleep_for(std::chrono::milliseconds(200));

  if (_modbus_wrapper != nullptr && _holding_regs_divider != nullptr && _input_regs_divider != nullptr) {
    auto input_regs_read_data = _input_regs_divider->getRegReadData();
    std::vector<uint16_t> current_input_reg_vector;
    std::for_each(std::begin(input_regs_read_data), std::end(input_regs_read_data), [&](const RegReadData &data) {
      current_input_reg_vector.resize(data.reg_num);
      _modbus_wrapper->readHoldingRegisters(data.reg_num, data.reg_count, current_input_reg_vector);

      for (int i = 0; i < current_input_reg_vector.size(); i++) {
        auto input_reg = data.reg_num + i;
        if (input_reg < _input_regs.size())
          _input_regs[input_reg] = current_input_reg_vector[i];
      }

      std::cout << "REG READ DATA " << data.reg_num << " " << data.reg_count << std::endl;
    });



    auto holding_regs_read_data = _holding_regs_divider->getRegReadData();
    std::vector<uint16_t> current_holding_reg_vector;
    std::for_each(std::begin(holding_regs_read_data), std::end(holding_regs_read_data), [&](const RegReadData &data) {
      current_holding_reg_vector.resize(data.reg_num);
      _modbus_wrapper->readHoldingRegisters(data.reg_num, data.reg_count, current_holding_reg_vector);

      for (int i = 0; i < current_holding_reg_vector.size(); i++) {
        auto holding_reg = data.reg_num + i;
        if (holding_reg < _holding_regs.size())
          _holding_regs[holding_reg] = current_holding_reg_vector[i];
      }

      std::cout << "REG READ DATA " << data.reg_num << " " << data.reg_count << std::endl;
    });
  }

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
