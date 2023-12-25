#ifndef MODBUSTCPD_MANAGERS_MODBUSTCPCLIENT_H_
#define MODBUSTCPD_MANAGERS_MODBUSTCPCLIENT_H_

#include "managers/modbusclient.h"

class ModbusTCPClient: public ModbusClient {
 public:
  ModbusTCPClient(const std::string &ip, uint16_t port);

  bool connect() override;
  void disconnect() override;

 protected:
  std::string ip;
  uint16_t port;
};

#endif //MODBUSTCPD_MANAGERS_MODBUSTCPCLIENT_H_
