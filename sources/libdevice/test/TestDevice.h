#ifndef LIBDEVICE_TEST_TESTDEVICE_H_
#define LIBDEVICE_TEST_TESTDEVICE_H_

#include <csignal>
#include <memory>

#include <modbus.h>
#include <devices/device.h>

using modbus::ModbusClient;

class ModbusProperty: public Property {
 public:
  ModbusProperty(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client);

 protected:
  std::shared_ptr<ModbusClient> modbus_client;
};


class PeriodProperty: public ModbusProperty {
 public:
  PeriodProperty(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client);

  void poll() override;

 protected:
  void beforeRead(ErrorCode *error_code) override;
  VARIANT read(ErrorCode *error_code) override;
  void afterRead(ErrorCode *error_code) override;
  void beforeWrite(ErrorCode *error_code) override;
  void write(const VARIANT& value, ErrorCode * error_code) override;
  void afterWrite(ErrorCode *error_code) override;
};

class ModbusCommand: public Command {
 public:
  ModbusCommand(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client);

 protected:
  std::shared_ptr<ModbusClient> modbus_client;
};


class ConnectCommand: public ModbusCommand {
 public:
  ConnectCommand(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client);

 protected:
  VARIANT execute(const VARIANT &argin, ErrorCode * error_code) override;
};


class TestDevice: public Device {
 public:
  TestDevice(const std::string &ip, int port, int modbus_id);

  const std::shared_ptr<ModbusClient> &getModbusClient() const;

 private:
  std::string ip;
  int port;
  int modbus_id;

  std::shared_ptr<ModbusClient> modbus_client;
};


std::shared_ptr<TestDevice> createTestDevice(const std::string &ip, int port, int modbus_id);

#endif //LIBDEVICE_TEST_TESTDEVICE_H_
