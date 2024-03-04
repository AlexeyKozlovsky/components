#ifndef MODBUSWRAPPERS_LIBMODBUSWRAPPER_INCLUDE_MODBUSWRAPPERS_MOCKS_MODBUSWRAPPERMOCK2_H_
#define MODBUSWRAPPERS_LIBMODBUSWRAPPER_INCLUDE_MODBUSWRAPPERS_MOCKS_MODBUSWRAPPERMOCK2_H_

#include <vector>
#include <map>


#include "modbuswrappers/modbuswrapper.h"

using RegCardType = std::map<int, std::vector<uint16_t>>;

class ModbusWrapperMock2: public ModbusWrapper {
 public:
  ~ModbusWrapperMock2() override = default;
  ErrorCode connect() override;
  ErrorCode disconnect() override;
  ErrorCode isConnected(bool &is_connected) override;
  ErrorCode readHoldingRegister(int reg_num, uint16_t &value, int modbus_id) override;
  ErrorCode readHoldingRegisters(int reg_num, int reg_count, std::vector<uint16_t> &values, int modbus_id) override;
  ErrorCode writeHoldingRegister(int reg_num, uint16_t value, int modbus_id) override;
  ErrorCode writeHoldingRegisters(int reg_num, std::vector<uint16_t> value, int modbus_id) override;
  ErrorCode readInputRegister(int reg_num, uint16_t &value, int modbus_id) override;
  ErrorCode readInputRegisters(int reg_num, int reg_count, std::vector<uint16_t> &values, int modbus_id) override;
  void addConnectable(const std::shared_ptr<Connectable> &connectable) override;
  void sendConnectionStatus(bool connection_status) override;
  void process() override;

 private:
  bool _is_connected = false;

  RegCardType _holding_reg_values;
  RegCardType _input_reg_values;

  ErrorCode readRegCard(int reg_num, uint16_t &value, int modbus_id, RegCardType &reg_card);
  ErrorCode writeRegCard(int reg_num, uint16_t value, int modbus_id, RegCardType &reg_card);

  void checkConnectionStatusByResponse(modbus::ModbusResult response);
};

#endif //MODBUSWRAPPERS_LIBMODBUSWRAPPER_INCLUDE_MODBUSWRAPPERS_MOCKS_MODBUSWRAPPERMOCK2_H_
