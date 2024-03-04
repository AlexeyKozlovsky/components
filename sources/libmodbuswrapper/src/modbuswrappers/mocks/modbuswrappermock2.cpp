#include "modbuswrappers/mocks/modbuswrappermock2.h"

#include <iostream>

static const int MAX_REG_NUM = 10000;
static const int MAX_HOLDING_REG_NUM = 10000;
static const int MAX_INPUT_REG_NUM = 10000;


ErrorCode ModbusWrapperMock2::connect() {
  auto result = OPERATION_INTERRUPTED;

  if (!_is_connected) {
    _is_connected = true;
    result = SUCCESS;

    sendConnectionStatus(_is_connected);
    std::cout << "CONNECTED" << std::endl;
  }

  return result;
}

ErrorCode ModbusWrapperMock2::disconnect() {
  auto result = OPERATION_INTERRUPTED;

  if (_is_connected) {
    _is_connected = false;
    result = SUCCESS;

    sendConnectionStatus(_is_connected);
    std::cout << "DISCONNECTED" << std::endl;
  }

  return result;
}

ErrorCode ModbusWrapperMock2::isConnected(bool &is_connected) {
  auto result = OPERATION_INTERRUPTED;

  is_connected = _is_connected;
  result = SUCCESS;

  return result;
}

ErrorCode ModbusWrapperMock2::readHoldingRegister(int reg_num, uint16_t &value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;

  if (_is_connected) {
    result = readRegCard(reg_num, value, modbus_id, _holding_reg_values);

    std::cout << "Read from Holding Register: " << reg_num << " " << value << " " << modbus_id << result << " "  <<  " " << __func__ << std::endl;
  }

  return result;
}

ErrorCode ModbusWrapperMock2::readHoldingRegisters(int reg_num,
                                                   int reg_count,
                                                   std::vector<uint16_t> &values,
                                                   int modbus_id) {
  auto result = OPERATION_INTERRUPTED;

  if (_is_connected) {
    values.resize(reg_count);
    for (int current_reg_num = reg_num; current_reg_num < reg_num + reg_count; current_reg_num++) {
      uint16_t current_reg_value;
      result = readHoldingRegister(current_reg_num, current_reg_value, modbus_id);

      values[current_reg_num - reg_num] = current_reg_value;

      if (result != SUCCESS) {
        break;
      }
    }
  }

  return result;
}

ErrorCode ModbusWrapperMock2::writeHoldingRegister(int reg_num, uint16_t value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;

  if (_is_connected) {
    result = writeRegCard(reg_num, value, modbus_id, _holding_reg_values);
    std::cout << "Write to Holding Register: " << reg_num << " " << value << " " << modbus_id << " " << result << " "  << __func__ << std::endl;
  }

  return result;
}

ErrorCode ModbusWrapperMock2::writeHoldingRegisters(int reg_num, std::vector<uint16_t> value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;

  if (_is_connected) {
    auto reg_count = value.size();
    for (int current_reg_num = reg_num; current_reg_num < reg_num + reg_count; current_reg_num++) {
      auto current_reg_value = value[current_reg_num - reg_num];
      result = writeHoldingRegister(current_reg_num, current_reg_value, modbus_id);
    }
  }

  return result;
}

ErrorCode ModbusWrapperMock2::readInputRegister(int reg_num, uint16_t &value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;

  if (_is_connected) {
    result = readRegCard(reg_num, value, modbus_id, _input_reg_values);
    std::cout << "Read from Input Register: " << reg_num << " " << value << " " << modbus_id << " " << result << " " << __func__ << std::endl;

  }

  return result;
}

ErrorCode ModbusWrapperMock2::readInputRegisters(int reg_num,
                                                 int reg_count,
                                                 std::vector<uint16_t> &values,
                                                 int modbus_id) {
  auto result = OPERATION_INTERRUPTED;

  if (_is_connected) {
    values.resize(reg_count);
    for (int current_reg_num = reg_num; current_reg_num < reg_num + reg_count; current_reg_num++) {
      uint16_t current_reg_value;
      result = readInputRegister(current_reg_num, current_reg_value, modbus_id);

      values[current_reg_num - reg_num] = current_reg_value;

      if (result != SUCCESS) {
        break;
      }
    }
  }

  return result;
}

void ModbusWrapperMock2::addConnectable(const std::shared_ptr<Connectable> &connectable) {
  ModbusWrapper::addConnectable(connectable);
}

void ModbusWrapperMock2::sendConnectionStatus(bool connection_status) {
  ModbusWrapper::sendConnectionStatus(connection_status);
}

void ModbusWrapperMock2::process() {
  ModbusWrapper::process();
}

ErrorCode ModbusWrapperMock2::readRegCard(int reg_num, uint16_t &value, int modbus_id, RegCardType &reg_card) {
  auto result = OPERATION_INTERRUPTED;

  if (reg_card.count(modbus_id) == 0) {
    reg_card.insert({modbus_id, {}});
  }

  auto &reg_vector = reg_card.at(modbus_id);

  if (reg_num >= 0 && reg_num < MAX_REG_NUM) {
    if (reg_num >= reg_vector.size()) {
      reg_vector.resize(reg_num + 1);
    }

    value = reg_vector[reg_num];
    result = SUCCESS;
  }

  return result;
}

ErrorCode ModbusWrapperMock2::writeRegCard(int reg_num, uint16_t value, int modbus_id, RegCardType &reg_card) {
  auto result = OPERATION_INTERRUPTED;

  if (reg_card.count(modbus_id) == 0) {
    reg_card.insert({modbus_id, {}});
  }

  auto &reg_vector = reg_card.at(modbus_id);

  if (reg_num >= 0 && reg_num < MAX_REG_NUM) {
    if (reg_num >= reg_vector.size()) {
      reg_vector.resize(reg_num + 1);
    }

    reg_vector[reg_num] = value;
    result = SUCCESS;
  }

  return result;
}

void ModbusWrapperMock2::checkConnectionStatusByResponse(modbus::ModbusResult response) {
  if (response == modbus::TCP_TIMEOUT_ERROR || response == modbus::NO_SOCKET_CONNECTION) {
    sendConnectionStatus(false);
  } else {
    sendConnectionStatus(true);
  }
}
