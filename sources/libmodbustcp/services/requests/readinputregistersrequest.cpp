#include "readinputregistersrequest.h"

#include <utils/modbusutils.h>

#include <utility>

ReadInputRegistersRequest::ReadInputRegistersRequest(uint16_t reg_num,
                                                     uint16_t reg_count,
                                                     std::function<void(ErrorCode *,
                                                                                            Request*)> on_responsed_callback):
                                                                        reg_num(reg_num),
                                                                        reg_count(reg_count){
  this->on_responsed_callback = std::move(on_responsed_callback);
}


void ReadInputRegistersRequest::getPDU(uint8_t **buffer, uint16_t &buffer_size) {
  buffer_size = 6;

  if (*buffer == nullptr) {
    *buffer = new uint8_t[buffer_size];
  }

  *(*buffer) = slave_id;
  *(*(buffer) + 1) = 0x04;
  modbus::toMsbLsb(reg_num, *(*(buffer) + 2), *(*(buffer) + 3));
  modbus::toMsbLsb(reg_count, *(*(buffer) + 4), *(*(buffer) + 5));
}

void ReadInputRegistersRequest::onResponsed() {
  Request::onResponsed();
}
