#include "TestDevice.h"

#include "modbus.h"

ModbusProperty::ModbusProperty(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client):
    Property(name), modbus_client(modbus_client) {
}

PeriodProperty::PeriodProperty(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client):
  ModbusProperty(name, modbus_client) {
}

void PeriodProperty::poll() {
  Property::poll();
}

void PeriodProperty::beforeRead(ErrorCode *error_code) {
  Property::beforeRead(error_code);
}

VARIANT PeriodProperty::read(ErrorCode * error_code) {
  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readHoldingRegister(0, value),
      std::cout << "READ: " << std::endl;,
      std::cout << "NOT READ " << std::endl;,
      error_status
  );

  return value;
}

void PeriodProperty::afterRead(ErrorCode *error_code) {
  Property::afterRead(error_code);
}

void PeriodProperty::beforeWrite(ErrorCode *error_code) {
  Property::beforeWrite(error_code);
}

void PeriodProperty::write(const VARIANT &value, ErrorCode * error_code) {

}

void PeriodProperty::afterWrite(ErrorCode *error_code) {
  Property::afterWrite(error_code);
}


TestDevice::TestDevice(const std::string &ip, int port, int modbus_id): Device() {
  modbus_client = std::make_shared<ModbusClient>(ip, port);
}

const std::shared_ptr<ModbusClient> &TestDevice::getModbusClient() const {
  return modbus_client;
}

ModbusCommand::ModbusCommand(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client):
  Command(name), modbus_client(modbus_client) {
}

ConnectCommand::ConnectCommand(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client):
    ModbusCommand(name, modbus_client) {
}

VARIANT ConnectCommand::execute( const VARIANT &argin, ErrorCode * error_code) {
  bool argin_value = std::get<bool>(argin);

  bool result = true;
  if (argin_value) {
    result = modbus_client->connect();
  } else modbus_client->disconnect();

  return result;
}

std::shared_ptr<TestDevice> createTestDevice(const std::string &ip, int port, int modbus_id) {
  auto result = std::make_shared<TestDevice>(ip, port, modbus_id);

  auto modbus_client = result->getModbusClient();
  auto period_property = std::make_shared<PeriodProperty>("period", modbus_client);
  auto connect_command = std::make_shared<ConnectCommand>("connect", modbus_client);

  ErrorCode error_code;
  result->addCommand(connect_command, &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cout << "ERROR while adding command " << connect_command->getName() << " " << error_code << std::endl;
  }

  result->addProperty(period_property, &error_code);
  if (error_code != ErrorCode::SUCCESS) {
    std::cout << "ERROR while adding property " << period_property->getName() << " " << error_code << std::endl;
  }

  period_property->setPollingPeriod(1000, &error_code);

  return result;
}

