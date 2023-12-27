#include "modbuswrappers/storages/modbuswrapperstorageimpl1.h"

std::shared_ptr<ModbusWrapper> ModbusWrapperStorageImpl1::getBaseModbusWrapper(const std::string &ip) {
  std::shared_ptr<ModbusWrapper> result;
  if (_base_modbus_wrappers.count(ip) != 0) {
    result = _base_modbus_wrappers[ip];
  }
  return result;
}

void ModbusWrapperStorageImpl1::addBaseModbusWrapper(const std::shared_ptr<ModbusWrapper> &modbus_wrapper,
                                                     const std::string &ip) {
  _base_modbus_wrappers.insert({ip, modbus_wrapper});
}
