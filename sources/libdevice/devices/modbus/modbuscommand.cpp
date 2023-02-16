#include "modbuscommand.h"

#include "modbusdevice.h"


ModbusCommand::ModbusCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device):
    Command(name, modbus_device) {
}
