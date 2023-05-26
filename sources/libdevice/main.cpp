#include <iostream>

#include "macros.h"
#include "enums.h"

#include "devices/device.h"
#include "devices/property.h"
#include "devices/command.h"

#include "managers/deviceconfig.h"
#include "managers/deviceserver.h"

#include "test/TestDevice.h"


int main() {
  auto device_server_builder = DeviceServerBuilder::getInstance();
  auto device_server = device_server_builder->createDeviceServer();
  auto device_config = device_server->getDeviceConfig();

  auto test_device = createTestDevice("192.168.127.5", 4001, 1);

  ErrorCode error_code;
  device_config->addDevice(test_device, &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cout << "ERROR while adding device: " << test_device->getName() << " to device config. "
      << error_code << std::endl;
  }

  auto connect_command_result = device_server->executeCommand(test_device, "connect", true, &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cout << "Error while executing CONNECT command from device " << test_device->getName() << ". " << error_code << std::endl;
  } else {
    std::cout << "CONNECT command result: " << std::get<bool>(connect_command_result) << std::endl;
  }

  auto period_property_result = device_server->readProperty(test_device, "period", &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cout << "Error while reading property PERIOD from device: " << test_device->getName() << ". " << error_code << std::endl;
  } else {
    std::cout << "PERIOD property result: " << std::get<uint16_t>(period_property_result) << std::endl;
  }

  device_server->startPolling(&error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cout << "UNABLE to start polling " << std::endl;
  }

  sleep(5);
  auto read_property_period_result = device_server->readProperty(test_device, "period", &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cout << "READ FROM READ_PROPERTY: " << std::get<uint16_t>(read_property_period_result) << std::endl;
  } else std::cout << "READ FROM READ_PROPERTY FAILED WITH ERROR CODE: " << error_code << std::endl;

  sleep(30);

//  modbus::ModbusClient client("192.168.127.5", 4001);
//  bool result = client.connect();
//  uint16_t value;
//  client.readHoldingRegister(0, value);
//

  return 0;
}
