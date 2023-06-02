#include "modbuscommandkit.h"

#include "devices/modbus/modbusdevice.h"


ConnectCommand::ConnectCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {
}

VARIANT__D ConnectCommand::execute(const VARIANT__D &argin, ErrorCode * error_code) {
  // TODO: прописать catch для конкретной ошибки
  bool to_connect;
  try {
    auto request = std::get<SCALAR_VARIANT__D>(argin);
    to_connect = std::get<bool>(request);
  } catch (...) {
    SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST);
    return VARIANT__D();
  }

  auto modbus_device = static_pointer_cast<ModbusDevice>(device);
  auto modbus_client = modbus_device->getModbusClient();

  bool result;
  if (to_connect) {
    result = modbus_client->connect();
  } else {
    modbus_client->disconnect();
    result = true;
  }

//  bool result = modbus_client->isConnected();
  if (result) {
    device->changeState(DeviceState::OPEN);
    SET_ERROR_CODE(error_code, ErrorCode::SUCCESS)
  } else {
    device->changeState(DeviceState::CLOSE);
    SET_ERROR_CODE(error_code, ErrorCode::DEVICE_NOT_RESPONDING_LAN)
  }


//  SET_ERROR_CODE(error_code, ErrorCode::SUCCESS);
  return result;
}

UpdateAddressCommand::UpdateAddressCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_client)
    : ModbusCommand(name, modbus_client) {

}

VARIANT__D UpdateAddressCommand::execute(const VARIANT__D &argin, ErrorCode *error_code) {
  // TODO: Прописать catch для конкретной ошибки
  std::string new_ip;
  int new_port;
  try {
    auto request = std::get<std::vector<SCALAR_VARIANT__D>>(argin);
    new_ip = std::get<std::string>(request.at(0));
    new_port = std::get<int>(request.at(1));
  } catch (...) {
    SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST);
    return VARIANT__D();
  }

  auto modbus_device = static_pointer_cast<ModbusDevice>(device);
  auto modbus_client = modbus_device->getModbusClient();

  modbus_client->disconnect();
  modbus_client->setIP(new_ip);
  modbus_client->setPort(new_port);

  SET_ERROR_CODE(error_code, ErrorCode::SUCCESS);
  return VARIANT__D();
}

UpdateModbusIDCommand::UpdateModbusIDCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_client)
    : ModbusCommand(name, modbus_client) {

}

VARIANT__D UpdateModbusIDCommand::execute(const VARIANT__D &argin, ErrorCode *error_code) {
  SET_ERROR_CODE(error_code, ErrorCode::SUCCESS);
  return VARIANT__D();
}

GetIPCommand::GetIPCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_client) : ModbusCommand(
    name,
    modbus_client) {

}

VARIANT__D GetIPCommand::execute(const VARIANT__D &argin, ErrorCode *error_code) {
  auto modbus_device = static_pointer_cast<ModbusDevice>(device);
  auto modbus_client = modbus_device->getModbusClient();

  std::string result = modbus_client->getIP();
  SET_ERROR_CODE(error_code, ErrorCode::SUCCESS);
  return result;
}

GetPortCommand::GetPortCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_client)
    : ModbusCommand(name, modbus_client) {

}

VARIANT__D GetPortCommand::execute(const VARIANT__D &argin, ErrorCode *error_code) {
  auto modbus_device = static_pointer_cast<ModbusDevice>(device);
  auto modbus_client = modbus_device->getModbusClient();

  int result = modbus_client->getPort();
  SET_ERROR_CODE(error_code, ErrorCode::SUCCESS);
  return result;
}

GetConnectionStatusCommand::GetConnectionStatusCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_client)
    : ModbusCommand(name, modbus_client) {

}

VARIANT__D GetConnectionStatusCommand::execute(const VARIANT__D &argin, ErrorCode *error_code) {
  auto modbus_device = static_pointer_cast<ModbusDevice>(device);
  auto modbus_client = modbus_device->getModbusClient();

  bool result = modbus_client->isConnected();
  SET_ERROR_CODE(error_code, ErrorCode::SUCCESS);
  return result;
}
