
#include "modbuswrappers/modbusasyncclientwrapper/modbusasyncclientwrapperfactory.h"
#include "modbuswrappers/modbusasyncclientwrapper/modbusasyncclientwrapper.h"

ModbusAsyncClientWrapperFactory::ModbusAsyncClientWrapperFactory(const std::shared_ptr<ModbusWrapperFactory> &modbus_wrapper_factory):
  _base_modbus_wrapper_factory(modbus_wrapper_factory) {

}

std::shared_ptr<ModbusWrapper> ModbusAsyncClientWrapperFactory::createModbusWrapper(const std::string &ip,
                                                                                    int port,
                                                                                    int modbus_id,
                                                                                    int holding_regs_count,
                                                                                    int input_regs_count) {
  std::shared_ptr<ModbusWrapper> result = nullptr;
  if (_base_modbus_wrapper_factory != nullptr) {
    auto base_modbus_wrapper = _base_modbus_wrapper_factory->createModbusWrapper(ip, port, modbus_id, holding_regs_count, input_regs_count);
    if (base_modbus_wrapper != nullptr) {
      result = std::make_shared<ModbusAsyncClientWrapper>(base_modbus_wrapper, holding_regs_count, input_regs_count);
    }
  }
  return result;
}


std::shared_ptr<ModbusWrapper> ModbusAsyncClientWrapperFactory::createBaseModbusWrapper(const std::string &ip,
                                                                                        int port) {
  std::shared_ptr<ModbusWrapper> result = nullptr;
  std::cerr << "Cannot create modbus wrapper of AsyncClientWrapper decorator without MODBUS ID and holding and input regs count " << std::endl;
  return result;
}

