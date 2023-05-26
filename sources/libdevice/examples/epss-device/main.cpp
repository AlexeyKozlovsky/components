#include <iostream>

#include "examples/epss-device/src/epssdevice.h"

#include <managers/deviceserver.h>
#include <managers/deviceconfig.h>


using device::ErrorCode;


int main(int argc, char *argv[]) {
  ErrorCode error_code;

  auto device_server_builder = DeviceServerBuilder::getInstance();
  auto device_server = device_server_builder->createDeviceServer();
  auto device_config = device_server->getDeviceConfig();

  auto epss_device = EPSSDevice::createEPSSDevice("tilt", "192.168.127.10", 4001, 1, &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cerr << "Error while creating EPSS device. Error code: " << error_code << std::endl;
    return EXIT_FAILURE;
  }

  device_config->addDevice(epss_device, &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cerr << "Error while adding EPSS device " << epss_device->getName() << " to config. Error code: " << error_code << std::endl;
    return EXIT_FAILURE;
  }

  auto connect_command_result = device_server->executeCommand(epss_device, "connect", true, &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cerr << "Error while executing CONNECT command with device: " << epss_device->getName() << ". Error code: " << error_code << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "AFTER CONNECT" << std::endl;
//  device_server->startPolling(&error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cerr << "Unable to start polling " << std::endl;
    return EXIT_FAILURE;
  }

  sleep(2);


  auto update_address_command_request = {SCALAR_VARIANT("192.168.127.6"), SCALAR_VARIANT(4001)};
  auto update_address_command_result = device_server->executeCommand(epss_device, "update_address", update_address_command_request, &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cerr << "Error whlie executing UPDATE_ADDRESS command with device " << epss_device->getName() << ". Error code: " << error_code << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "AFTER UPDATE" << std::endl;
  sleep(2);

  auto update_address_command_request_1 = {SCALAR_VARIANT("192.168.127.10"), SCALAR_VARIANT(4001)};
  update_address_command_result = device_server->executeCommand(epss_device, "update_address", update_address_command_request_1, &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cerr << "Error whlie executing UPDATE_ADDRESS command with device " << epss_device->getName() << ". Error code: " << error_code << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "AFTER UPDATE" << std::endl;
  sleep(2);

  connect_command_result = device_server->executeCommand(epss_device, "connect", true, &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cerr << "Error while executing CONNECT command with device: " << epss_device->getName() << ". Error code: " << error_code << std::endl;
    return EXIT_FAILURE;
  }

  auto inner_start_period = device_server->readProperty(epss_device, "inner_start_period", &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cerr << "Error while reading property INNER_START_PERIOD in device: " << epss_device->getName() << ". Error code: " << error_code << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Inner start period is: " << unsigned(std::get<uint64_t>(std::get<SCALAR_VARIANT>(inner_start_period))) << std::endl;

  device_server->writeProperty(epss_device, "inner_start_period", (uint64_t) 1000, &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cerr << "Error while writing property INNER_START_PERIOD in device " << epss_device->getName() << ". Error code: " << error_code << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Inner start period was successfully written" << std::endl;

  inner_start_period = device_server->readProperty(epss_device, "inner_start_period", &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cerr << "Error while reading property INNER_START_PERIOD in device: " << epss_device->getName() << ". Error code: " << error_code << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Inner start period is: " << unsigned(std::get<uint64_t>(std::get<SCALAR_VARIANT>(inner_start_period))) << std::endl;

  std::cout << "AFTER CONNECT" << std::endl;

  auto channel_delay = device_server->executeCommand(epss_device, "get_channel_delay", (int16_t) 1, &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cerr << "Error while executing command GET_CHANNEL_DELAY for device " << epss_device->getName() << ". Error code: " << error_code << std::endl;
    return EXIT_FAILURE;
  }

  auto response = std::get<uint64_t>(std::get<SCALAR_VARIANT>(channel_delay));
  std::cout << "Channel delay is " << unsigned(response) << std::endl;

  auto set_channel_delay_request = {SCALAR_VARIANT((int16_t) 1), SCALAR_VARIANT((uint64_t) 1000)};
  device_server->executeCommand(epss_device, "set_channel_delay", set_channel_delay_request, &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cerr << "Error while executing command SET_CHANNEL_DELAY for device " << epss_device->getName() << ". Error code: " << error_code << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "SET_CHANNEL_DELAY command was successfully executed" << std::endl;

  sleep(20);
  device_server->stopPolling(&error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cerr << "Unable to stop polling " << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}