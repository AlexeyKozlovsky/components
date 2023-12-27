#include "modbuswrappers/modbusclientwrapper/modbusclientwrapper.h"

#include <utils/enumconverter.h>


ModbusClientWrapper::ModbusClientWrapper() {

}

ErrorCode ModbusClientWrapper::connect() {
  auto result = OPERATION_INTERRUPTED;

  if (_current_state != nullptr) {
    result = _current_state->connect();
  }

  return result;
}

ErrorCode ModbusClientWrapper::disconnect() {
  auto result = OPERATION_INTERRUPTED;

  if (_current_state != nullptr) {
    result = _current_state->disconnect();
  }

  return result;
}

ErrorCode ModbusClientWrapper::isConnected(bool &is_connected) {
  auto result = OPERATION_INTERRUPTED;

  if (_current_state != nullptr) {
    result = _current_state->isConnected(is_connected);
  }

  return result;
}

ErrorCode ModbusClientWrapper::readHoldingRegister(int reg_num, uint16_t &value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;

  if (_current_state != nullptr) {
    result = _current_state->readHoldingRegister(reg_num, value, modbus_id);
  }

  return result;
}

ErrorCode ModbusClientWrapper::readHoldingRegisters(int reg_num,
                                                    int reg_count,
                                                    std::vector<uint16_t> &values,
                                                    int modbus_id) {
  auto result = OPERATION_INTERRUPTED;

  if (_current_state != nullptr) {
    result = _current_state->readHoldingRegisters(reg_num, reg_count, values, modbus_id);
  }

  return result;
}

ErrorCode ModbusClientWrapper::writeHoldingRegister(int reg_num, uint16_t value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;

  if (_current_state != nullptr) {
    result = _current_state->writeHoldingRegister(reg_num, value, modbus_id);
  }

  return result;
}

ErrorCode ModbusClientWrapper::writeHoldingRegisters(int reg_num, std::vector<uint16_t> value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;

  if (_current_state != nullptr) {
    result = _current_state->writeHoldingRegisters(reg_num, value, modbus_id);
  }

  return result;
}

ErrorCode ModbusClientWrapper::readInputRegister(int reg_num, uint16_t &value, int modbus_id) {
  auto result = OPERATION_INTERRUPTED;

  if (_current_state != nullptr) {
    result = _current_state->readInputRegister(reg_num, value, modbus_id);
  }

  return result;
}

ErrorCode ModbusClientWrapper::readInputRegisters(int reg_num,
                                                  int reg_count,
                                                  std::vector<uint16_t> &values,
                                                  int modbus_id) {
  auto result = OPERATION_INTERRUPTED;

  if (_current_state != nullptr) {
    result = _current_state->readInputRegisters(reg_num, reg_count, values, modbus_id);
  }

  return result;
}

void ModbusClientWrapper::addConnectable(const std::shared_ptr<Connectable> &connectable) {
  ModbusWrapper::addConnectable(connectable);
}

void ModbusClientWrapper::sendConnectionStatus(bool connection_status) {
  ModbusWrapper::sendConnectionStatus(connection_status);
}

void ModbusClientWrapper::checkConnectionStatusByResponse(modbus::ModbusResult response) {
  if (response == modbus::TCP_TIMEOUT_ERROR || response == modbus::NO_SOCKET_CONNECTION) {
    sendConnectionStatus(false);
    changeState(DISCONNECTED);
  } else {
    sendConnectionStatus(true);
    changeState(CONNECTED);
  }
}

void ModbusClientWrapper::changeState(DeviceState state) {
  if (_states.count(state) != 0) {
    _current_state = _states[state];
  }
}

void ModbusClientWrapper::addState(const std::pair<DeviceState, std::shared_ptr<ModbusWrapper>> &state) {
  _states.insert(state);
}
