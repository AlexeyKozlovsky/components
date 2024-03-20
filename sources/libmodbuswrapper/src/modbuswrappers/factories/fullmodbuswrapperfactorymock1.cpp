#include "modbuswrappers/factories/fullmodbuswrapperfactorymock1.h"

#include "modbuswrappers/storages/modbuswrapperstorageimpl1.h"
#include "modbuswrappers/modbuswrappermodbusiddecorator/modbusclientmodbusiddecorator.h"
#include "modbuswrappers/modbuswrappermodbusiddecorator/modbusclientmodbusiddecoratorfactory.h"
#include "modbuswrappers/modbusasyncclientwrapper/modbusasyncclientwrapperfactory.h"
#include "modbuswrappers/mocks/modbuswrappermockfactory.h"


FullModbusWrapperFactoryMock1::FullModbusWrapperFactoryMock1() {
  auto modbus_wrapper_storage = std::make_shared<ModbusWrapperStorageImpl1>();
  _base_modbus_wrapper_factory = std::make_shared<ModbusWrapperMockFactory>();
  auto main_modbus_wrapper_factory = std::make_shared<ModbusClientModbusIDDecoratorFactory>(_base_modbus_wrapper_factory, modbus_wrapper_storage);
  _modbus_wrapper_factory = std::make_shared<ModbusAsyncClientWrapperFactory>(main_modbus_wrapper_factory);
}

std::shared_ptr<ModbusWrapper> FullModbusWrapperFactoryMock1::createModbusWrapper(const std::string &ip,
                                                                                  int port,
                                                                                  int modbus_id,
                                                                                  int holding_regs_count,
                                                                                  int input_regs_count) {
  std::shared_ptr<ModbusWrapper> result = nullptr;
  if (_modbus_wrapper_factory != nullptr) {
    result = _modbus_wrapper_factory->createModbusWrapper(ip, port, modbus_id, holding_regs_count, input_regs_count);
  }
  return result;
}


std::shared_ptr<ModbusWrapper> FullModbusWrapperFactoryMock1::createBaseModbusWrapper(const std::string &ip, int port) {
  std::shared_ptr<ModbusWrapper> result = nullptr;
  if (_base_modbus_wrapper_factory != nullptr) {
    result = _base_modbus_wrapper_factory->createBaseModbusWrapper(ip, port);
  }

  return result;
}
