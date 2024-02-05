#include "modbuswrappers/modbuspostponedwritewrapper/modbuspostponedwritewrapperfactory.h"
#include "modbuswrappers/modbusasyncclientwrapper/modbusasyncclientwrapper2.h"
#include "modbuswrappers/modbuspostponedwritewrapper/modbuspostponedwritewrapper.h"

#include <iostream>

ModbusPostponedWriteWrapperFactory::ModbusPostponedWriteWrapperFactory(const std::shared_ptr<ModbusWrapperFactory> &base_modbus_wrapper_factory):
  _base_modbus_wrapper_factory(base_modbus_wrapper_factory) {

}

std::shared_ptr<ModbusWrapper> ModbusPostponedWriteWrapperFactory::createModbusWrapper(const std::string &ip,
                                                                                       int port,
                                                                                       int modbus_id,
                                                                                       int holding_regs_count,
                                                                                       int input_regs_count) {
  std::shared_ptr<ModbusWrapper> result = nullptr;
  if (_base_modbus_wrapper_factory != nullptr) {
    auto base_modbus_wrapper = _base_modbus_wrapper_factory->createModbusWrapper(ip, port, modbus_id, holding_regs_count, input_regs_count);
    if (base_modbus_wrapper != nullptr) {
      auto async_client_wrapper = std::make_shared<ModbusAsyncClientWrapper2>(base_modbus_wrapper, holding_regs_count, input_regs_count);
      result = std::make_shared<ModbusPostponedWriteWrapper>(async_client_wrapper);
    }
  }
  return result;
}


std::shared_ptr<ModbusWrapper> ModbusPostponedWriteWrapperFactory::createBaseModbusWrapper(const std::string &ip,
                                                                                           int port) {
  std::shared_ptr<ModbusWrapper> result = nullptr;
  std::cerr << "Cannot create modbus wrapper of PostponedWriteModbusWrapper decorator without MODBUS ID and holding and input regs count " << std::endl;
  return result;
}
