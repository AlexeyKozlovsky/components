#include <string>
#include <iostream>

#include <modbuswrappers/modbusasyncclientwrapper/modbusasyncclientwrapperfactory.h>
#include <modbuswrappers/modbuswrappermodbusiddecorator/modbusclientmodbusiddecoratorfactory.h>
#include <modbuswrappers/modbusclientwrapper/modbusclientwrapperfactory.h>
#include <modbuswrappers/storages/modbuswrapperstorageimpl1.h>

#include <modbuswrappers/modbuspostponedwritewrapper/modbuspostponedwritewrapperfactory.h>
#include <modbuswrappers/modbuspostponedwritewrapper/modbuspostponedwritewrapper.h>
#include "modbuswrappers/modbusclientwrapper/modbusclientwrapper.h"
#include "modbuswrappers/modbusclientwrapper/modbusclientdividablewrapper.h"
#include "modbuswrappers/modbusclientwrapper/modbusclientdividablewrapperfactory.h"

int main() {
  setlocale(LC_ALL, "Russian");

  std::string ip = "10.10.110.26";
  int port = 4001;
  int modbus_id = 4;
  int holding_regs_count = 83;
  int input_regs_count = 10;

  auto modbus_client = std::make_shared<modbus::ModbusClient>(ip, port);
//  modbus_client->connect();

//  auto result = modbus_client->writeHoldingRegistersTrue(10,{0, 0, 40, 0, 0, 68}, 4);
//  std::cout << result << "\t\t MODBUS RESULT--" << std::endl;

//
//  auto base_modbus_wrapper_factory = std::make_shared<ModbusClientWrapperFactory>();
//  auto base_modbus_wrapper = base_modbus_wrapper_factory->createBaseModbusWrapper(ip, port);

  int holding_start_reg = 0;
  int holding_max_reg = 83;
  int holding_regs_per_request = 30;
  int input_start_reg = 0;
  int input_max_reg = 12;
  int input_regs_per_request = 30;

  auto modbus_wrapper_storage = std::make_shared<ModbusWrapperStorageImpl1>();
  auto base_modbus_wrapper_factory = std::make_shared<ModbusClientWrapperFactory>();
//  auto base_modbus_wrapper_factory = std::make_shared<ModbusWrapperMockFactory>();
  auto main_modbus_wrapper_factory = std::make_shared<ModbusClientModbusIDDecoratorFactory>(base_modbus_wrapper_factory, modbus_wrapper_storage);

  auto dividable_modbus_wrapper_factory = std::make_shared<ModbusClientDividableWrapperFactory>(main_modbus_wrapper_factory);
  auto async_modbus_wrapper_factory = std::make_shared<ModbusAsyncClientWrapperFactory>(dividable_modbus_wrapper_factory);
  auto postponed_modbus_wrapper_factory = std::make_shared<ModbusPostponedWriteWrapperFactory>(async_modbus_wrapper_factory);


  auto modbus_wrapper_async = async_modbus_wrapper_factory->createModbusWrapper(ip, port, modbus_id, holding_regs_count, input_regs_count);
  auto modbus_wrapper_postponed = postponed_modbus_wrapper_factory->createModbusWrapper(ip, port, modbus_id, holding_regs_count, input_regs_count);


  modbus_wrapper_async->connect();
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  modbus_wrapper_async->process();

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  modbus_wrapper_postponed->writeHoldingRegisters(10, {0, 0, 40, 0, 68});
  modbus_wrapper_postponed->writeHoldingRegisters(15, {0, 0, 40, 0, 68});
  modbus_wrapper_postponed->writeHoldingRegisters(20, {0, 0, 40, 0, 68});
  modbus_wrapper_postponed->writeHoldingRegisters(25, {0, 0, 40, 0, 68});
  modbus_wrapper_postponed->process();

//  auto holding_reg_req_divider = std::make_shared<RegReadDivider>(holding_start_reg,
//                                                                  holding_max_reg,
//                                                                  holding_regs_per_request);
//  auto input_reg_req_divider = std::make_shared<RegReadDivider>(input_start_reg,
//                                                                input_max_reg,
//                                                                input_regs_per_request);
//  auto dividable_modbus_client_wrapper = std::make_shared<ModbusClientDividableWrapper>(base_modbus_wrapper,
//                                                                                       holding_reg_req_divider,
//                                                                                       input_reg_req_divider);


#if 0
  std::string ip = "10.10.110.26";
  int port = 4001;
  int modbus_id = 2;
  int holding_regs_count = 40;
  int input_regs_count = 10;

  auto modbus_wrapper_storage = std::make_shared<ModbusWrapperStorageImpl1>();
  auto base_modbus_wrapper_factory = std::make_shared<ModbusClientWrapperFactory>();
//  auto base_modbus_wrapper_factory = std::make_shared<ModbusWrapperMockFactory>();
  auto main_modbus_wrapper_factory = std::make_shared<ModbusClientModbusIDDecoratorFactory>(base_modbus_wrapper_factory, modbus_wrapper_storage);
  auto async_modbus_wrapper_factory = std::make_shared<ModbusAsyncClientWrapperFactory>(main_modbus_wrapper_factory);

  auto modbus_wrapper = async_modbus_wrapper_factory->createModbusWrapper(ip, port, modbus_id, holding_regs_count, input_regs_count);

  if (modbus_wrapper != nullptr) {
    auto async_modbus_wrapper = dynamic_pointer_cast<AbstractModbusAsyncClientWrapper>(modbus_wrapper);
    if (async_modbus_wrapper != nullptr) {
      auto postponed_modbus_wrapper = std::make_shared<ModbusPostponedWriteWrapper>(async_modbus_wrapper);
      modbus_wrapper->connect();

      postponed_modbus_wrapper->writeHoldingRegister(14, 69, modbus_id);
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
      postponed_modbus_wrapper->writeHoldingRegister(19, 69, modbus_id);
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
      postponed_modbus_wrapper->writeHoldingRegister(24, 69, modbus_id);
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
      postponed_modbus_wrapper->writeHoldingRegister(29, 69, modbus_id);
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
      postponed_modbus_wrapper->process();

      auto error_code = modbus_wrapper->writeHoldingRegister(17, 1);
      std::cout << error_code << "\t modbus error_code" << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(3000));
      error_code = modbus_wrapper->writeHoldingRegister(17, 0);
      std::cout << error_code << "\t modbus error_code" << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(3000));
      error_code = modbus_wrapper->writeHoldingRegister(17, 1);
      std::cout << error_code << "\t modbus error_code" << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
  }

#endif

  return 0;
}