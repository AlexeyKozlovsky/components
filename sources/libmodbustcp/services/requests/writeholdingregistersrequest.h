#ifndef MODBUSTCPD_SERVICES_REQUESTS_WRITEHOLDINGREGISTERSREQUEST_H_
#define MODBUSTCPD_SERVICES_REQUESTS_WRITEHOLDINGREGISTERSREQUEST_H_

#include "services/requests/request.h"

#include <vector>

class WriteHoldingRegistersRequest: public Request {
 public:
  void getPDU(uint8_t **buffer, uint16_t &buffer_size) override;

 private:
  uint16_t reg_num;
  std::vector<uint8_t> values;

};

#endif //MODBUSTCPD_SERVICES_REQUESTS_WRITEHOLDINGREGISTERSREQUEST_H_
