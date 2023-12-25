#include "responseparser.h"

#include <utility>
#include <utils/modbusutils.h>


static const uint16_t HEADER_SIZE = 6;

ResponseParser *ResponseParser::instance = nullptr;


ResponseParser::ResponseParser(std::shared_ptr<RequestManager> request_manager): request_manager(std::move(request_manager)) {

}

ResponseParser *ResponseParser::getInstance(const std::shared_ptr<RequestManager> &request_manager) {
  if (instance == nullptr) {
    instance = new ResponseParser(request_manager);
  }
  return instance;
}

void ResponseParser::parsePDU(VARIANT__D &read_value, uint16_t pdu_size) {

}

void ResponseParser::parseResponse(uint8_t *buffer, uint16_t buffer_size) {
  uint16_t start_res_pos = 0;     // Позиция начала ответа (одного из)

  // Часть с парсингом хедеров

  uint16_t transaction_num;
  modbus::fromMsbLsb(*(buffer + start_res_pos), *(buffer + start_res_pos + 1), transaction_num);

  uint16_t protocol_id;
  modbus::fromMsbLsb(*(buffer + start_res_pos + 2) , *(buffer + start_res_pos + 3), protocol_id);

  if (protocol_id != 0) {
    std::cerr << "ERROR" << std::endl;
    return;
  }

  uint16_t message_length;
  modbus::fromMsbLsb(*(buffer + start_res_pos + 4), *(buffer + start_res_pos + 5), message_length);


  uint16_t current_pos = start_res_pos + HEADER_SIZE;


  // Добавить сюда ещё проверки на длину буфера
  if (message_length < 2) {
    std::cerr << "ERROR" << std::endl;
  }

  uint8_t slave_id;
  slave_id = *(buffer + current_pos);

  uint8_t function_code;
  function_code = *(buffer + current_pos + 1);


  VARIANT__D read_value = std::vector<SCALAR_VARIANT__D>();

  switch (function_code) {
    case 0x04:
      uint8_t byte_count;
      byte_count = *(buffer + current_pos + 2);

      std::vector<SCALAR_VARIANT__D> values;

      for (uint8_t byte_num = 0; byte_num < byte_count - 1; byte_num += 2) {
        uint16_t current_reg_value;
        modbus::fromMsbLsb(*(buffer + current_pos + 3 + byte_num),
                           *(buffer + current_pos + 3 + byte_num + 1),
                           current_reg_value);
        values.emplace_back(current_reg_value);
      }

      read_value = values;
      break;
  }

  request_manager->setResponsed(transaction_num, slave_id, read_value);

//  for (uint16_t i = 0; i < message_length; i++) {
//    *(buffer + current_pos)
//  }

}