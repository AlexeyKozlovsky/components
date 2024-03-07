#ifndef TEST_PROJECT_WITH_MODULE_ARCH_MODBUSWRAPPERS_MOCKS_MODBUSWRAPPERMOCK1_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_MODBUSWRAPPERS_MOCKS_MODBUSWRAPPERMOCK1_H_

#include "modbuswrappers/modbuswrapper.h"
#include <modbuswrappers/export.h>

class MODBUSWRAPPERS_EXPORT ModbusWrapperMock1: public ModbusWrapper {
 public:
  explicit ModbusWrapperMock1(const std::string &ip, int port, int modbus_id);

  std::string getIP() override;
  int getPort() override;
  int getModbusID() override;

  ErrorCode connect() override;
  ErrorCode disconnect() override;
  ErrorCode isConnected(bool &is_connected) override;

  ErrorCode readHoldingRegister(int reg_num, uint16_t &value, int modbus_id) override;
  ErrorCode readHoldingRegisters(int reg_num, int reg_count, std::vector<uint16_t> &values, int modbus_id) override;
  ErrorCode writeHoldingRegister(int reg_num, uint16_t value, int modbus_id = 1) override;
  ErrorCode writeHoldingRegisters(int reg_num, std::vector<uint16_t> value, int modbus_id) override;

  ErrorCode readInputRegister(int reg_num, uint16_t &value, int modbus_id) override;
  ErrorCode readInputRegisters(int reg_num, int reg_count, std::vector<uint16_t> &values, int modbus_id) override;

 private:
  std::string _ip;
  int _port = 4001;
  int _modbus_id = 1;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_MODBUSWRAPPERS_MOCKS_MODBUSWRAPPERMOCK1_H_
