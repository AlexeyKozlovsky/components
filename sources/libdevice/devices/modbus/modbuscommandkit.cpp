#include "modbuscommandkit.h"

#include "devices/modbus/modbusdevice.h"


ConnectCommand::ConnectCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {
}

VARIANT ConnectCommand::execute( const VARIANT &argin, ErrorCode * error_code) {
  // TODO: прописать catch для конкретной ошибки
  bool to_connect;
  try {
    auto request = std::get<SCALAR_VARIANT>(argin);
    to_connect = std::get<bool>(request);
  } catch (...) {
    SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST);
    return VARIANT();
  }

  auto modbus_device = static_pointer_cast<ModbusDevice>(device);
  auto modbus_client = modbus_device->getModbusClient();

  if (to_connect) {
    modbus_client->connect();
  } else modbus_client->disconnect();

  bool result = modbus_client->isConnected();
  if (result) device->changeState(DeviceState::OPEN);
  else device->changeState(DeviceState::CLOSE);

  SET_ERROR_CODE(error_code, ErrorCode::SUCCESS);
  return result;
}

UpdateAddressCommand::UpdateAddressCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_client)
    : ModbusCommand(name, modbus_client) {

}

VARIANT UpdateAddressCommand::execute(const VARIANT &argin, ErrorCode *error_code) {
  // TODO: Прописать catch для конкретной ошибки
  std::string new_ip;
  int new_port;
  try {
    auto request = std::get<std::vector<SCALAR_VARIANT>>(argin);
    new_ip = std::get<std::string>(request.at(0));
    new_port = std::get<int>(request.at(1));
  } catch (...) {
    SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST);
    return VARIANT();
  }

  auto modbus_device = static_pointer_cast<ModbusDevice>(device);
  auto modbus_client = modbus_device->getModbusClient();

  modbus_client->disconnect();
  modbus_client->setIP(new_ip);
  modbus_client->setPort(new_port);

  SET_ERROR_CODE(error_code, ErrorCode::SUCCESS);
  return VARIANT();
}

UpdateModbusIDCommand::UpdateModbusIDCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_client)
    : ModbusCommand(name, modbus_client) {

}

VARIANT UpdateModbusIDCommand::execute(const VARIANT &argin, ErrorCode *error_code) {
  SET_ERROR_CODE(error_code, ErrorCode::SUCCESS);
  return VARIANT();
}

GetIPCommand::GetIPCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_client) : ModbusCommand(
    name,
    modbus_client) {

}

VARIANT GetIPCommand::execute(const VARIANT &argin, ErrorCode *error_code) {
  auto modbus_device = static_pointer_cast<ModbusDevice>(device);
  auto modbus_client = modbus_device->getModbusClient();

  std::string result = modbus_client->getIP();
  SET_ERROR_CODE(error_code, ErrorCode::SUCCESS);
  return result;
}

GetPortCommand::GetPortCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_client)
    : ModbusCommand(name, modbus_client) {

}

VARIANT GetPortCommand::execute(const VARIANT &argin, ErrorCode *error_code) {
  auto modbus_device = static_pointer_cast<ModbusDevice>(device);
  auto modbus_client = modbus_device->getModbusClient();

  int result = modbus_client->getPort();
  SET_ERROR_CODE(error_code, ErrorCode::SUCCESS);
  return result;
}

GetConnectionStatusCommand::GetConnectionStatusCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_client)
    : ModbusCommand(name, modbus_client) {

}

VARIANT GetConnectionStatusCommand::execute(const VARIANT &argin, ErrorCode *error_code) {
  auto modbus_device = static_pointer_cast<ModbusDevice>(device);
  auto modbus_client = modbus_device->getModbusClient();

  bool result = modbus_client->isConnected();
  SET_ERROR_CODE(error_code, ErrorCode::SUCCESS);
  return result;
}
