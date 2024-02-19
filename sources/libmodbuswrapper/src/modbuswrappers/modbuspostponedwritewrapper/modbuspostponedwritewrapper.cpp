#include <utils/services/domain/regreaddivider.h>
#include "modbuswrappers/modbuspostponedwritewrapper/modbuspostponedwritewrapper.h"


ModbusPostponedWriteWrapper::ModbusPostponedWriteWrapper(const std::shared_ptr<AbstractModbusAsyncClientWrapper> &modbus_wrapper):
  _modbus_wrapper(modbus_wrapper) {

}

ErrorCode ModbusPostponedWriteWrapper::connect() {
  ErrorCode result = OPERATION_INTERRUPTED;

  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->connect();
  }

  return result;
}

ErrorCode ModbusPostponedWriteWrapper::disconnect() {
  ErrorCode result = OPERATION_INTERRUPTED;

  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->disconnect();
  }

  return result;
}

ErrorCode ModbusPostponedWriteWrapper::isConnected(bool &is_connected) {
  ErrorCode result = OPERATION_INTERRUPTED;

  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->isConnected(is_connected);
  }

  return result;
}

ErrorCode ModbusPostponedWriteWrapper::readHoldingRegister(int reg_num, uint16_t &value, int modbus_id) {
  ErrorCode result = OPERATION_INTERRUPTED;

  if (_modbus_wrapper != nullptr) {

    if (start_postponing) {
      if (validateRegNum(reg_num)) {
        value = _tmp_holding_regs[reg_num];
        result = SUCCESS;
      }
    } else {
      result = _modbus_wrapper->readHoldingRegister(reg_num, value, modbus_id);
    }
  }

  return result;
}

ErrorCode ModbusPostponedWriteWrapper::readHoldingRegisters(int reg_num,
                                                            int reg_count,
                                                            std::vector<uint16_t> &values,
                                                            int modbus_id) {
  ErrorCode result = OPERATION_INTERRUPTED;

  if (_modbus_wrapper != nullptr) {

    if (start_postponing) {
      values.resize(reg_count);

      for (int i = reg_num; i < reg_num + reg_count; i++) {
        if (validateRegNum(i) && i - reg_num < values.size()) {
          values[i - reg_num] = _tmp_holding_regs[i];
        }
      }

      result = SUCCESS;

    } else {
      result = _modbus_wrapper->readHoldingRegisters(reg_num, reg_count, values, modbus_id);
    }
  }

  return result;
}

ErrorCode ModbusPostponedWriteWrapper::writeHoldingRegister(int reg_num, uint16_t value, int modbus_id) {
  ErrorCode result = OPERATION_INTERRUPTED;
  updateTempHoldingRegs();

  if (validateRegNum(reg_num)) {
    _tmp_holding_regs[reg_num] = value;
    result = SUCCESS;
  } else {
    result = INVALID_REQUEST;
  }

  return result;
}

ErrorCode ModbusPostponedWriteWrapper::writeHoldingRegisters(int reg_num, std::vector<uint16_t> value, int modbus_id) {
  ErrorCode result = OPERATION_INTERRUPTED;
  updateTempHoldingRegs();

  int reg_count = value.size();
  for (int i = reg_num; i < reg_num + reg_count; i++) {
    result = writeHoldingRegister(i, value[i - reg_num], modbus_id);
    if (result != SUCCESS) {
      return result;
    }
  }

  return result;
}

ErrorCode ModbusPostponedWriteWrapper::readInputRegister(int reg_num, uint16_t &value, int modbus_id) {
  ErrorCode result = OPERATION_INTERRUPTED;

  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->readInputRegister(reg_num, value, modbus_id);
  }

  return result;
}

ErrorCode ModbusPostponedWriteWrapper::readInputRegisters(int reg_num,
                                                          int reg_count,
                                                          std::vector<uint16_t> &values,
                                                          int modbus_id) {
  ErrorCode result = OPERATION_INTERRUPTED;

  if (_modbus_wrapper != nullptr) {
    result = _modbus_wrapper->readInputRegisters(reg_num, reg_count, values, modbus_id);
  }

  return result;
}

void ModbusPostponedWriteWrapper::addConnectable(const std::shared_ptr<Connectable> &connectable) {
  if (_modbus_wrapper != nullptr) {
    _modbus_wrapper->addConnectable(connectable);
  }
}

void ModbusPostponedWriteWrapper::sendConnectionStatus(bool connection_status) {
  if (_modbus_wrapper != nullptr) {
    _modbus_wrapper->sendConnectionStatus(connection_status);
  }
}

void ModbusPostponedWriteWrapper::process() {
  if (start_postponing) {
    start_postponing = false;
    _modbus_wrapper->writeHoldingRegisters(0, _tmp_holding_regs);
  }
}

void ModbusPostponedWriteWrapper::updateTempHoldingRegs() {
  if (!start_postponing) {
    start_postponing = true;

    if (_modbus_wrapper != nullptr) {
      _modbus_wrapper->process();
      _tmp_holding_regs = _modbus_wrapper->getHoldingRegs();
    }
  }
}

bool ModbusPostponedWriteWrapper::validateRegNum(int reg_num) {
  bool result = reg_num >= 0 && reg_num < _tmp_holding_regs.size();
  return result;
}

