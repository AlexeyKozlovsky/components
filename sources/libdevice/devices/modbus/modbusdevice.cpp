#include "modbusdevice.h"

#include "devices/modbus/modbuscommandkit.h"


std::shared_ptr<ModbusDevice> ModbusDevice::createModbusDevice(const std::string &name,
                                                               const std::string &ip,
                                                               int port,
                                                               int modbus_id,
                                                               ErrorCode *error_code) {
  // TODO: Потом добавить сюда проверки на ip и порт (валидуацию)
  auto modbus_client = std::make_shared<ModbusClient>(ip, port);
  auto device = std::shared_ptr<ModbusDevice>(new ModbusDevice(name, modbus_client));

  ModbusDevice::createModbusDevice(device, error_code);

  return device;
}

void ModbusDevice::createModbusDevice(std::shared_ptr<ModbusDevice> &device,
                                      ErrorCode *error_code) {
  auto connect_command = std::make_shared<ConnectCommand>("connect", device);
  auto update_address_command = std::make_shared<UpdateAddressCommand>("update_address", device);
  auto update_modbus_id_command = std::make_shared<UpdateModbusIDCommand>("update_modbus_id", device);
  auto get_ip_command = std::make_shared<GetIPCommand>("get_ip", device);
  auto get_port_command = std::make_shared<GetPortCommand>("get_port", device);
  auto get_connection_status_command = std::make_shared<GetConnectionStatusCommand>("get_connection_status", device);

  device->addCommand(connect_command, error_code);
  IS_ERROR__D(
      error_code,
      return;
  );

  device->addCommand(update_address_command, error_code);
  IS_ERROR__D(
      error_code,
      return;
  );

  device->addCommand(update_modbus_id_command, error_code);
  IS_ERROR__D(
      error_code,
      return;
  );

  device->addCommand(get_ip_command, error_code);
  IS_ERROR__D(
      error_code,
      return;
  );

  device->addCommand(get_port_command, error_code);
  IS_ERROR__D(
      error_code,
      return;
  );

  device->addCommand(get_connection_status_command, error_code);
  IS_ERROR__D(
      error_code,
      return;
  );

  device->setAvailableStates({DeviceState::OPEN, DeviceState::CLOSE});
  device->changeState(DeviceState::CLOSE);

}

ModbusDevice::ModbusDevice(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client):
  Device(name), modbus_client(modbus_client) {

}

void ModbusDevice::init() {
  Device::init();
}

const std::shared_ptr<ModbusClient> &ModbusDevice::getModbusClient() {
  return modbus_client;
}

std::string ModbusDevice::getIP() const {
  return std::move(modbus_client->getIP());
}
int ModbusDevice::getPort() const {
  return modbus_client->getPort();
}
int ModbusDevice::getModbusID() const {
  return modbus_id;
}
