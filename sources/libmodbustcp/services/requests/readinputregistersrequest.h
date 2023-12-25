#ifndef MODBUSTCPD_SERVICES_REQUESTS_READINPUTREGISTERSREQUEST_H_
#define MODBUSTCPD_SERVICES_REQUESTS_READINPUTREGISTERSREQUEST_H_

#include "services/requests/request.h"

class RequestCreator;


class ReadInputRegistersRequest: public Request {
  friend class RequestCreator;
 public:
  void getPDU(uint8_t **buffer, uint16_t &buffer_size) override;

 private:
  uint16_t reg_num;
  uint16_t reg_count;

  ReadInputRegistersRequest(uint16_t reg_num, uint16_t reg_count,
      std::function<void(ErrorCode*, Request*)> on_responsed_callback);
 protected:
  void onResponsed() override;
};


#endif //MODBUSTCPD_SERVICES_REQUESTS_READINPUTREGISTERSREQUEST_H_
