#include "modbuswrappers/mocks/modbuswrappermock1.h"

#include <utils/baseutils.h>

ModbusWrapperMock1::ModbusWrapperMock1(const std::string &ip, int port, int modbus_id):
  _ip(ip), _port(port), _modbus_id(modbus_id) {

}

std::string ModbusWrapperMock1::getIP() {
  return _ip;
}

int ModbusWrapperMock1::getPort() {
  return _port;
}

int ModbusWrapperMock1::getModbusID() {
  return _modbus_id;
}


ErrorCode ModbusWrapperMock1::connect() {
  std::cout << "TEST CONNECT MOCK " << __func__ << std::endl;
  return SUCCESS;
}

ErrorCode ModbusWrapperMock1::disconnect() {
  std::cout << "TEST DISCONNECT MOCK "  << __func__ << std::endl;
  return SUCCESS;
}

ErrorCode ModbusWrapperMock1::isConnected(bool &is_connected) {
  std::cout << "IS CONNECTED MOCK "  << __func__ << std::endl;
  is_connected = false;
  return SUCCESS;
}

ErrorCode ModbusWrapperMock1::readHoldingRegister(int reg_num, uint16_t &value, int modbus_id) {
  std::cout << "READ HOLDING REGSITER MOCK " << reg_num << " " << unsigned(value)  << __func__ << std::endl;
  return SUCCESS;
}


ErrorCode ModbusWrapperMock1::readHoldingRegisters(int reg_num,
                                                   int reg_count,
                                                   std::vector<uint16_t> &values,
                                                   int modbus_id) {
  std::cout << "READ HOLDING REGSITERS! MOCK " << reg_num << " " << reg_count  << __func__ << std::endl;
  return SUCCESS;
}

ErrorCode ModbusWrapperMock1::writeHoldingRegister(int reg_num, uint16_t value, int modbus_id) {
  std::cout << "TEST WRITE HOLDING REGSITER MOCK " << reg_num << " " << unsigned (value) << " " << __func__ << std::endl;
  return SUCCESS;
}

ErrorCode ModbusWrapperMock1::writeHoldingRegisters(int reg_num, std::vector<uint16_t> value, int modbus_id) {
  std::cout << "WRITE HOLDING REGSITERS! MOCK " << reg_num << " " << value.size()  << __func__ << std::endl;
  return SUCCESS;
}

ErrorCode ModbusWrapperMock1::readInputRegister(int reg_num, uint16_t &value, int modbus_id) {
  std::cout << "READ INPUT REGSITER MOCK " << reg_num << " " << value << __func__ << std::endl;
  return SUCCESS;
}

ErrorCode ModbusWrapperMock1::readInputRegisters(int reg_num,
                                                 int reg_count,
                                                 std::vector<uint16_t> &values,
                                                 int modbus_id) {
  std::cout << "READ INPUT REGSITERS! MOCK " << reg_num << " " << reg_count  << __func__ << std::endl;
  return SUCCESS;
}