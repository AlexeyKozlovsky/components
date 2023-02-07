#include "modbusproperty.h"

ModbusProperty::ModbusProperty(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client):
    Property(name), modbus_client(modbus_client) {
}
