#ifndef MODBUSTCPD_SERVICES_PARSERS_RESPONSEPARSER_H_
#define MODBUSTCPD_SERVICES_PARSERS_RESPONSEPARSER_H_

#include <cstdint>

#include <memory>

#include "managers/requestmanager.h"


class ResponseParser {
 public:
  static ResponseParser *getInstance(const std::shared_ptr<RequestManager> &request_manager);

  void parseResponse(uint8_t *buffer, uint16_t buffer_size);

 protected:
  void parsePDU(VARIANT__D &read_value, uint16_t pdu_size);

 private:
  static ResponseParser *instance;

  std::shared_ptr<RequestManager> request_manager;
  explicit ResponseParser(std::shared_ptr<RequestManager> request_manager);
};

#endif //MODBUSTCPD_SERVICES_PARSERS_RESPONSEPARSER_H_
