#include "device.h"

#include <algorithm>

static const std::string DEFAULT_DESCRIPTION_PREFIX = "Description of ";


Device::Device() {

}

Device::Device(const std::string &name):
  name(name), alias(name), description(DEFAULT_DESCRIPTION_PREFIX + name) {

}

Device::Device(const Device &dev) {

}

void Device::setName(const std::string &name) {
  this->name = name;
}

void Device::setAlias(const std::string &alias) {
  this->alias = alias;
}

void Device::setDescription(const std::string &description) {
  this->description = description;
}

void Device::addProperty(std::shared_ptr<Property> property, ErrorCode *error_code) {
  if (properties.count(property) != 0) *error_code = ErrorCode::PROPERTY_OR_COMMAND_ALREADY_EXISTS;
  else {
    properties.insert(property);
    *error_code = ErrorCode::SUCCESS;
  }
}

void Device::addCommand(std::shared_ptr<Command> command, ErrorCode *error_code) {
  if (commands.count(command) != 0) *error_code = ErrorCode::PROPERTY_OR_COMMAND_ALREADY_EXISTS;
  else {
    commands.insert(command);
    *error_code = ErrorCode::SUCCESS;
  }
}

void Device::setAvailableStates(const std::set<DeviceState> &states) {
  available_states = states;
}

void Device::changeState(DeviceState state, ErrorCode *error_code) {
  if (available_states.count(state) == 0) *error_code = ErrorCode::DEVICE_DOESNT_HAVE_ATTRIBUTE;
  else {
    this->state = state;
    SET_ERROR_CODE(error_code, ErrorCode::SUCCESS)
  }
}

VARIANT Device::readProperty(const std::string &property_name, ErrorCode *error_code) {
  std::shared_ptr<Property> property = getPropertyByName(property_name, error_code);
  if (property == nullptr) return VARIANT();

  auto result = property->readValue(error_code);
  return result;
}

VARIANT Device::writeProperty(const std::string &property_name,
                              const VARIANT &value,
                              ErrorCode * error_code) {
  std::shared_ptr<Property> property = getPropertyByName(property_name, error_code);
  if (property == nullptr) return VARIANT();

  property->writeValue(value, error_code);
  return value;
}
VARIANT Device::executeCommand(const std::string &command_name,
                               const VARIANT &argin,
                               ErrorCode * error_code) {
  std::shared_ptr<Command> command = getCommandByName(command_name, error_code);
  if (command == nullptr) return VARIANT();

  auto result = command->executeCommand(argin, error_code);
  return result;
}

std::shared_ptr<Property> Device::getPropertyByName(const std::string &property_name, ErrorCode *error_code) {
  // Проверяем, есть ли свойство, среди индексированных свойств девайса
  if (indexed_properties.indexed_values.count(property_name) == 0) {
    auto it = std::find_if(std::begin(properties), std::end(properties),
                           [&](const std::shared_ptr<Property> &prop) {
                             return prop->getName() == property_name;
                           });

    // Если свойства нет и среди неиндексированных, то метод заканчивает работу с ошибкой
    if (it == std::end(properties)) {
      *error_code = ErrorCode::DEVICE_DOESNT_HAVE_ATTRIBUTE;
      return nullptr;
    }

    // Если свойство нашлось, но не было индексировано, то оно индексируется
    indexed_properties.indexed_values.insert({property_name, *it});
  }

  std::shared_ptr<Property> property = indexed_properties.indexed_values.at(property_name);
  return property;
}
std::shared_ptr<Command> Device::getCommandByName(const std::string &command_name, ErrorCode *error_code) {
  // Проверяем, есть ли команды, среди индексированных команд девайса
  if (indexed_commands.indexed_values.count(command_name) == 0) {
    auto it = std::find_if(std::begin(commands), std::end(commands),
                           [&](const std::shared_ptr<Command> &prop) {
                             return prop->getName() == command_name;
                           });

    // Если свойства нет и среди неиндексированных, то метод заканчивает работу с ошибкой
    if (it == std::end(commands)) {
      *error_code = ErrorCode::DEVICE_DOESNT_HAVE_ATTRIBUTE;
      return nullptr;
    }

    // Если команда нашлось, но не была индексирована, то она индексируется
    indexed_commands.indexed_values.insert({command_name, *it});
  }

  std::shared_ptr<Command> command = indexed_commands.indexed_values.at(command_name);
  return command;
}

std::set<std::shared_ptr<DeviceAttribute>> Device::getPollingAttributes() {
  std::set<std::shared_ptr<DeviceAttribute>> result;
  std::for_each(std::begin(properties), std::end(properties),
                [&](const std::shared_ptr<Property> &property) {
    result.insert(property);
  });

  std::for_each(std::begin(commands), std::end(commands),
                [&](const std::shared_ptr<Command> &command) {
    result.insert(command);
  });

  return std::move(result);
}

void Device::index() {

}
