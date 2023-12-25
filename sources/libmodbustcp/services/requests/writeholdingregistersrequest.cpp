#include <utils/modbusutils.h>
#include "writeholdingregistersrequest.h"

void WriteHoldingRegistersRequest::getPDU(uint8_t **buffer, uint16_t &buffer_size) {
  buffer_size = 7 + values.size();
  *buffer = new uint8_t[buffer_size];
  uint16_t reg_count = values.size();

  **buffer = slave_id;
  **(buffer + 1) = 0x10;
  modbus::toMsbLsb(reg_num, **(buffer + 2), **(buffer + 3));
  modbus::toMsbLsb(reg_count, **(buffer + 4), **(buffer + 5));

  uint8_t bytes_count = reg_count / 2;
  **(buffer + 6) = bytes_count;

  uint16_t buffer_shift = 7;
  for (auto value: values) {
    modbus::toMsbLsb(value, **(buffer + buffer_shift), **(buffer + buffer_shift + 1));
  }
}
