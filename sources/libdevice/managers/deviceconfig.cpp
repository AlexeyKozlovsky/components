#include "deviceconfig.h"

#include <algorithm>
#include <stdexcept>

DeviceConfig::DeviceConfig() {

}

std::shared_ptr<Device> DeviceConfig::createDevice(const std::string &name, ErrorCode *error_code) {
  if (devices.count(name) != 0) {
    *error_code = ErrorCode::DEVICE_ALREADY_EXISTS;
    return nullptr;
  }

  return nullptr;
}

void DeviceConfig::addDevice(const std::shared_ptr<Device> &device, ErrorCode *error_code) {
  checkDeviceNotInConfig(device, error_code);
  if (*error_code != ErrorCode::SUCCESS) return;

  devices.insert({device->getName(), device});
  *error_code = ErrorCode::SUCCESS;
}

void DeviceConfig::removeDevice(const std::string &name, ErrorCode *error_code) {
  if (devices.count(name) == 0) {
    *error_code = ErrorCode::DEVICE_DOESNT_EXIST;
    return;
  }

  // TODO: выяснить почему не работает std::remove_if
//  auto it = std::remove_if(std::begin(devices), std::end(devices),
//                           [&](const std::pair<std::string, std::shared_ptr<Device>> &dev) {
//    return dev.first == name;
//  });


  auto it = std::begin(devices);
  while (it->first != name && it != std::end(devices)) {
    it++;
  }

  devices.erase(it, std::end(devices));
}

std::shared_ptr<Device> DeviceConfig::getDeviceByName(const std::string &name, ErrorCode *error_code) {
  auto result = checkDeviceInConfig(name, error_code);
  return result;
}

std::shared_ptr<Property> DeviceConfig::getDevicePropertyByName(const std::shared_ptr<Device> &device,
                                                                const std::string &name,
                                                                ErrorCode *error_code) {
  checkDeviceInConfig(device, error_code);
  if (*error_code != ErrorCode::SUCCESS) return nullptr;

  auto result = device->getPropertyByName(name, error_code);
  return result;
}

std::shared_ptr<Command> DeviceConfig::getDeviceCommandByName(const std::shared_ptr<Device> &device,
                                                              const std::string &name,
                                                              ErrorCode *error_code) {
  checkDeviceInConfig(device, error_code);
  if (*error_code != ErrorCode::SUCCESS) return nullptr;

  auto result = device->getCommandByName(name, error_code);
  return result;
}

const std::map<std::string, std::shared_ptr<Device>> &DeviceConfig::getAllDevices() {
  return devices;
}

std::shared_ptr<Device> DeviceConfig::checkDeviceInConfig(const std::string &device_name, ErrorCode *error_code) {
  try {
    auto result = devices.at(device_name);
    *error_code = ErrorCode::SUCCESS;
    return result;
  } catch (std::out_of_range &error) {
    *error_code = ErrorCode::DEVICE_DOESNT_EXIST;
    return nullptr;
  }
}

std::shared_ptr<Device> DeviceConfig::checkDeviceInConfig(const std::shared_ptr<Device> &device, ErrorCode *error_code) {
  if (device == nullptr) {
    *error_code = ErrorCode::DEVICE_DOESNT_EXIST;
    return nullptr;
  }

  const std::string &device_name = device->getName();
  auto config_device = getDeviceByName(device_name, error_code);
  if (*error_code != ErrorCode::SUCCESS) {
    return nullptr;
  }

  // TODO: Надо перегрузить оператор сравнения для Device
  if (config_device != device) {

    // TODO: Добавить код ошибки для этого случая
    *error_code = ErrorCode::OPERATION_INTERRUPTED;
    return nullptr;
  }

  return device;
}

void DeviceConfig::checkDeviceNotInConfig(const std::shared_ptr<Device> &device, ErrorCode *error_code) {
  if (device == nullptr) {
    *error_code = ErrorCode::INVALID_REQUEST;
    return;
  }

  if (devices.count(device->getName()) != 0) {
    *error_code = ErrorCode::DEVICE_ALREADY_EXISTS;
    return;
  }

  *error_code = ErrorCode::SUCCESS;
}
