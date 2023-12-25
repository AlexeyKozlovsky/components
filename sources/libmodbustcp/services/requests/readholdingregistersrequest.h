#ifndef MODBUSTCPD_SERVICES_REQUESTS_READHOLDINGREGISTERSREQUEST_H_
#define MODBUSTCPD_SERVICES_REQUESTS_READHOLDINGREGISTERSREQUEST_H_

#include "services/requests/request.h"


class ReadHoldingRegistersRequest: public Request {
 public:
  void getPDU(uint8_t **buffer, uint16_t &buffer_size) override;

 private:
  uint16_t reg_num;
  uint16_t reg_count;
};

#endif //MODBUSTCPD_SERVICES_REQUESTS_READHOLDINGREGISTERSREQUEST_H_
