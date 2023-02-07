#include "modbuscommand.h"

ModbusCommand::ModbusCommand(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client):
    Command(name), modbus_client(modbus_client) {
}
