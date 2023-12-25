#ifndef MODBUSTCPD_CREATORS_REQUESTBUFFERBUILDER_H_
#define MODBUSTCPD_CREATORS_REQUESTBUFFERBUILDER_H_

#include <cstdint>

#include <memory>

#include "services/requests/request.h"


class RequestBufferBuilder {
 public:
//  void buildRequestBuffer(uint8_t **buffer, uint16_t &buffer_size);
  void addRequest(const std::shared_ptr<Request> &request);

  void clearBuffer();


  inline int getBufferSize() {
    return buffer_vector.size();
  }

  void getBuffer(uint8_t **buffer, uint16_t &buffer_size);

 private:
  std::vector<uint8_t> buffer_vector;

  void pushTCPRequestBufferBack(const std::shared_ptr<Request> &request);
};

#endif //MODBUSTCPD_CREATORS_REQUESTBUFFERBUILDER_H_
