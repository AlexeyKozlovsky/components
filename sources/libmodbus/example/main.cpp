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
  std::vector<uint16_t> values(4);
  for (int i = 0; i < 100; i++) {
    result = client.readHoldingRegister(1, value);
    std::cout << i << " " << 0 << std::endl;
    result = client.readHoldingRegister(5, value);
    std::cout << i << " " << 1 << std::endl;
    result = client.readInputRegister(5, value);
    std::cout << i << " " << 2 << std::endl;
    result = client.readInputRegister(1, value);
    std::cout << i << " " << 3 << std::endl;

    // Возможно падает на множественном чтении
    result = client.readInputRegisters(1, 4, values);
    std::cout << i << " " << 4 << std::endl;
//    result = client.readHoldingRegisters(1, 5, values);
//    std::cout << i << " " << 5 << std::endl;
  }

  std::cout << "RESULT CODE IS " << result << std::endl;

  return EXIT_SUCCESS;
}
