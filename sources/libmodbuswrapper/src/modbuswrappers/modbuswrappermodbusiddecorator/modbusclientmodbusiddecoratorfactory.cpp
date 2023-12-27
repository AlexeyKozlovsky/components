
#include "modbuswrappers/modbuswrappermodbusiddecorator/modbusclientmodbusiddecoratorfactory.h"
#include "modbuswrappers/modbuswrappermodbusiddecorator/modbusclientmodbusiddecorator.h"

ModbusClientModbusIDDecoratorFactory::ModbusClientModbusIDDecoratorFactory(const std::shared_ptr<ModbusWrapperFactory> &base_modbus_wrapper_factory,
                                                                           const std::shared_ptr<ModbusWrapperStorage> &modbus_wrapper_storage):
                                                                           _modbus_wrapper_storage(modbus_wrapper_storage),
                                                                           _base_modbus_wrapper_factory(base_modbus_wrapper_factory) {

}

std::shared_ptr<ModbusWrapper> ModbusClientModbusIDDecoratorFactory::createModbusWrapper(const std::string &ip,
                                                                                         int port,
                                                                                         int modbus_id,
                                                                                         int holding_regs_count,
                                                                                         int input_regs_count) {
  std::shared_ptr<ModbusWrapper> result = nullptr;
  if (_modbus_wrapper_storage != nullptr) {
    auto base_modbus_wrapper = _modbus_wrapper_storage->getBaseModbusWrapper(ip);
    if (base_modbus_wrapper == nullptr) {
      if (_base_modbus_wrapper_factory != nullptr) {
        base_modbus_wrapper = _base_modbus_wrapper_factory->createBaseModbusWrapper(ip, port);
      }
    }

    if (base_modbus_wrapper != nullptr) {
      result = std::make_shared<ModbusClientModbusIDDecorator>(base_modbus_wrapper, modbus_id);
      _modbus_wrapper_storage->addBaseModbusWrapper(base_modbus_wrapper, ip);
    }
  }

  return result;
}
std::shared_ptr<ModbusWrapper> ModbusClientModbusIDDecoratorFactory::createBaseModbusWrapper(const std::string &ip,
                                                                                             int port) {
  std::cerr << "MODBUS WRAPPER SHOULD HAS MODBUS ID TO BE CREATED VIA THIS FACTORY " << __func__ << std::endl;
  return nullptr;
}
