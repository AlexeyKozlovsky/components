#ifndef MODBUSTCPD_CREATORS_REQUESTCREATOR_H_
#define MODBUSTCPD_CREATORS_REQUESTCREATOR_H_

#include <vector>
#include <memory>
#include <functional>

#include <services/requests/request.h>
#include <services/requests/readinputregistersrequest.h>

class RequestCreator {
 public:
  std::shared_ptr<Request> createReadInputRegistersRequest(uint16_t reg_num, uint16_t reg_count, uint8_t slave_id,
                                                           std::function<void(ErrorCode*, Request*)> on_responsed_callback,
                                                           std::function<void(ErrorCode*, Request*)> on_requested_callback = nullptr);
  std::shared_ptr<Request> createReadHoldingRegistersRequest(uint16_t reg_num, uint16_t reg_count,
                                                             std::function<void(ErrorCode*, Request*)> on_responsed_callback,
                                                             std::function<void(ErrorCode*, Request*)> on_requested_callback = nullptr);
  std::shared_ptr<Request> createWriteHoldingRegistersRequest(uint16_t reg_num, const std::vector<uint8_t> &values,
                                                              std::function<void(ErrorCode*, Request*)> on_responsed_callback,
                                                              std::function<void(ErrorCode*, Request*)> on_requested_callback = nullptr);

 private:
  uint16_t transaction_num;
};


#endif //MODBUSTCPD_CREATORS_REQUESTCREATOR_H_
