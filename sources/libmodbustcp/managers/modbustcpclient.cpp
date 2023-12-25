#include "modbustcpclient.h"


ModbusTCPClient::ModbusTCPClient(const std::string &ip, uint16_t port) : ip(ip), port(port) {

}

bool ModbusTCPClient::connect() {
  return communicator->connect();
}

void ModbusTCPClient::disconnect() {
  communicator->disconnect();
}
