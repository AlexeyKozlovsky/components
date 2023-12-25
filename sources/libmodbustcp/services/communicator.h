#ifndef MODBUSTCPD_SERVICES_COMMUNICATOR_H_
#define MODBUSTCPD_SERVICES_COMMUNICATOR_H_

class Communicator {
 public:
  inline void setConnectTimeout(int timeout) {
    connect_timeout = timeout;
  }

  inline void setRequestTimeout(int timeout) {
    request_timeout = timeout;
  }

  virtual bool connect() = 0;
  virtual void disconnect() = 0;

  virtual bool sendRawRequest(uint8_t *raw_request, uint16_t raw_request_size,
                              uint8_t *raw_response, uint16_t &raw_response_size) = 0;

 protected:
  int connect_timeout;
  int request_timeout;

};

#endif //MODBUSTCPD_SERVICES_COMMUNICATOR_H_
