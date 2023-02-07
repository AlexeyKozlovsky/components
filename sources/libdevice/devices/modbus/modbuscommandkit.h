#ifndef LIBDEVICE_DEVICES_MODBUS_MODBUSCOMMANDKIT_H_
#define LIBDEVICE_DEVICES_MODBUS_MODBUSCOMMANDKIT_H_

#include "devices/modbus/modbuscommand.h"


class ConnectCommand: public ModbusCommand {
 public:
  ConnectCommand(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client);

 protected:
  VARIANT execute(const VARIANT &argin, ErrorCode * error_code) override;
};

class UpdateAddressCommand: public ModbusCommand {
 public:
  UpdateAddressCommand(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client);

 protected:
  VARIANT execute(const VARIANT &argin, ErrorCode * error_code) override;
};

class UpdateModbusIDCommand: public ModbusCommand {
 public:
  UpdateModbusIDCommand(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client);

 protected:
  VARIANT execute(const VARIANT &argin, ErrorCode * error_code) override;
};

class GetIPCommand: public ModbusCommand {
 public:
  GetIPCommand(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client);

 protected:
  VARIANT execute(const VARIANT &argin, ErrorCode * error_code) override;
};

class GetPortCommand: public ModbusCommand {
 public:
  GetPortCommand(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client);

 protected:
  VARIANT execute(const VARIANT &argin, ErrorCode * error_code) override;
};

class GetConnectionStatusCommand: public ModbusCommand {
 public:
  GetConnectionStatusCommand(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client);

 protected:
  VARIANT execute(const VARIANT &argin, ErrorCode * error_code) override;
};


#endif //LIBDEVICE_DEVICES_MODBUS_MODBUSCOMMANDKIT_H_
