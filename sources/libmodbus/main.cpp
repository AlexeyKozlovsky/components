#include <iostream>

#include "modbus.h"

using namespace modbus;

int main() {
  ModbusClient client("192.168.127.10", 4001);
  bool is_connected = client.connect();
  if (!is_connected) {
    std::cout << "Connection failure" << std::endl;
    return EXIT_FAILURE;
  }

//  sleep(7);

  uint16_t value;
  auto result = client.readHoldingRegister(0, value);
  std::cout << "RESULT CODE IS " << result << std::endl;

  return EXIT_SUCCESS;
}
