#ifndef MODBUSTCPD_MANAGERS_REQUESTMANAGER_H_
#define MODBUSTCPD_MANAGERS_REQUESTMANAGER_H_

#include <memory>

#include "services/requests/request.h"
#include "creators/requestbufferbuilder.h"


class RequestManager {
 public:
  RequestManager();

  inline int getBufferSize() const {
    return request_buffer_builder->getBufferSize();
  }

  inline void getBuffer(uint8_t **buffer, uint16_t &buffer_size) const {
    request_buffer_builder->getBuffer(buffer, buffer_size);
  }

  void addRequest(const std::shared_ptr<Request> &request);

  void clearBuffer();
  void clearAllRequests();
  void clearNonBufferedRequests();

  inline const std::vector<std::shared_ptr<Request>> &getRequests() {
    return requests;
  }

  void setResponsed(uint16_t transaction_num, uint16_t slave_id, VARIANT__D &value);

 private:
  std::shared_ptr<RequestBufferBuilder> request_buffer_builder;
  std::vector<std::shared_ptr<Request>> requests;
};

#endif //MODBUSTCPD_MANAGERS_REQUESTMANAGER_H_
