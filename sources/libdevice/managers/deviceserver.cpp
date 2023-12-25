#include <iostream>
#include "deviceserver.h"

#include <utils/baseutils.h>
#include <utils/deviceutils.h>

static const int DEFAULT_POLLING_TACT = 500;


DeviceServer::DeviceServer(): polling_tact(DEFAULT_POLLING_TACT), polling_processing_flag(false) {

}

VARIANT__D DeviceServer::readProperty(const std::shared_ptr<Device> &device,
                                      const std::string &property_name,
                                      ErrorCode *error_code) {
  CHECK_DEVICE_INIT(error_code, device, {})

  auto property = device_config->getDevicePropertyByName(device, property_name, error_code);
  if (*error_code != ErrorCode::SUCCESS) return VARIANT__D();

  polling_mutex.lock();
  auto result = property->readValue(error_code);
  polling_mutex.unlock();
  return result;
}
void DeviceServer::writeProperty(const std::shared_ptr<Device> &device,
                                 const std::string &property_name,
                                 const VARIANT__D &value,
                                 ErrorCode * error_code) {
  CHECK_DEVICE_INIT(error_code, device,)

  auto property = device_config->getDevicePropertyByName(device, property_name, error_code);
  if (*error_code != ErrorCode::SUCCESS) return;

  polling_mutex.lock();
  property->writeValue(value, error_code);
  polling_mutex.unlock();
}
VARIANT__D DeviceServer::executeCommand(const std::shared_ptr<Device> &device,
                                        const std::string &command_name,
                                        const VARIANT__D &value,
                                        ErrorCode * error_code) {
  CHECK_DEVICE_INIT(error_code, device, {})

  auto command = device_config->getDeviceCommandByName(device, command_name, error_code);
  if (*error_code != ErrorCode::SUCCESS) return VARIANT__D();

  polling_mutex.lock();
  auto result = command->executeCommand(value, error_code);
  polling_mutex.unlock();
  return result;
}

void DeviceServer::startPolling(ErrorCode *error_code) {
  polling_processing_flag = true;
  polling_thread = std::thread(&DeviceServer::polling, this);
}

void DeviceServer::stopPolling(ErrorCode *error_code) {
  polling_processing_flag = false;
  polling_thread.join();
}

void DeviceServer::polling() {
  while (polling_processing_flag) {
//    polling_mutex.lock();

      for (auto device_pair: device_config->getAllDevices()) {
      auto device = device_pair.second;
      if (device == nullptr) continue;

      auto polling_attributes = device->getPollingAttributes();
      std::for_each(std::begin(polling_attributes), std::end(polling_attributes),
                    [&](const std::shared_ptr<DeviceAttribute> &polling_attribute) {
        polling_mutex.lock();
        polling_attribute->poll();
        polling_mutex.unlock();
      });
    }
    // TODO: вот здесь надо актуализировать POlling attrs или брать их из другого места
//    std::for_each(std::begin(polling_attrs), std::end(polling_attrs),
//                  [&](const std::shared_ptr<DeviceAttribute> &attr) {
//      attr->poll();
//      std::cout << attr->getName() << " POLLED" << std::endl;
//    });
//    polling_mutex.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(polling_tact));
  }
}

std::shared_ptr<DeviceServerBuilder> DeviceServerBuilder::instance = nullptr;

DeviceServerBuilder::DeviceServerBuilder() {

}

std::shared_ptr<DeviceServerBuilder> DeviceServerBuilder::getInstance() {
  if (instance == nullptr) instance = std::shared_ptr<DeviceServerBuilder>(new DeviceServerBuilder);
  return instance;
}

std::shared_ptr<DeviceServer> DeviceServerBuilder::createDeviceServer() {
  auto device_server = std::shared_ptr<DeviceServer>(new DeviceServer);
  auto device_config = std::shared_ptr<DeviceConfig>(new DeviceConfig);

  device_server->device_config = device_config;

  return device_server;
}

