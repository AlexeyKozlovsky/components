#ifndef LIBDEVICE_TEST_TESTDEVICE_H_
#define LIBDEVICE_TEST_TESTDEVICE_H_

#include <csignal>
#include <memory>

#include <modbus.h>
#include <devices/device.h>
#include <devices/modbus/modbusproperty.h>
#include <devices/modbus/modbuscommand.h>
#include <devices/modbus/modbuscommandkit.h>


using modbus::ModbusClient;


class PeriodProperty: public ModbusProperty {
 public:
  PeriodProperty(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client);

  void poll() override;

 protected:
  void beforeRead(ErrorCode *error_code) override;
  VARIANT__D read(ErrorCode *error_code) override;
  void afterRead(ErrorCode *error_code) override;
  void beforeWrite(ErrorCode *error_code) override;
  void write(const VARIANT__D& value, ErrorCode * error_code) override;
  void afterWrite(ErrorCode *error_code) override;
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
