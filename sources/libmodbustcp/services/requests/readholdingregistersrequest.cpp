#include "readholdingregistersrequest.h"

#include <utils/modbusutils.h>


void ReadHoldingRegistersRequest::getPDU(uint8_t **buffer, uint16_t &buffer_size) {
  buffer_size = 6;
  *buffer = new uint8_t[buffer_size];

  **buffer = slave_id;
  **(buffer + 1) = 0x03;
  modbus::toMsbLsb(reg_num, **(buffer + 2), **(buffer + 3));
  modbus::toMsbLsb(reg_count, **(buffer + 4), **(buffer + 5));
}
