#include <utils/modbusutils.h>
#include "requestbufferbuilder.h"


///**
// * @deprecated
//
// */
//void RequestBufferBuilder::buildRequestBuffer(uint8_t **buffer, uint16_t &buffer_size) {
//  auto requests = request_manager->getRequests();
//  for (const auto &request: requests) {
//    pushTCPRequestBufferBack(request);
//  }
//
////  buffer_size = buffer_vector.size();
////
////  // TODO: добавить здесь и в аналогичных местах проверки на null
////  *buffer = new uint8_t[buffer_size];
////
////  for (int i = 0; i < buffer_vector.size(); i++) {
////    *(*(buffer) + i) = buffer_vector[i];
////  }
//
//  getBuffer(buffer, buffer_size);
//}

void RequestBufferBuilder::clearBuffer() {
  buffer_vector.clear();
}

void RequestBufferBuilder::addRequest(const std::shared_ptr<Request> &request) {
  pushTCPRequestBufferBack(request);
}

void RequestBufferBuilder::getBuffer(uint8_t **buffer, uint16_t &buffer_size) {
  buffer_size = buffer_vector.size();
  *buffer = new uint8_t[buffer_size];

  for (int i = 0; i < buffer_vector.size(); i++) {
    *(*(buffer) + i) = buffer_vector[i];
  }
}

void RequestBufferBuilder::pushTCPRequestBufferBack(const std::shared_ptr<Request> &request) {
  uint8_t *current_buffer = nullptr;
  uint16_t current_buffer_size;
  request->getPDU(&current_buffer, current_buffer_size);

  // TODO: возможно добавить сюдя логику перехода состояния запроса

  uint8_t transaction_id_msb;
  uint8_t transaction_id_lsb;
  uint16_t transaction_id = request->getTransactionID();
  modbus::toMsbLsb(transaction_id, transaction_id_msb, transaction_id_lsb);
  buffer_vector.push_back(transaction_id_msb);
  buffer_vector.push_back(transaction_id_lsb);

  uint8_t protocol_id_msb;
  uint8_t protocol_id_lsb;
  uint16_t protocol_id = 0x0;
  modbus::toMsbLsb(protocol_id, protocol_id_msb, protocol_id_lsb);
  buffer_vector.push_back(protocol_id_msb);
  buffer_vector.push_back(protocol_id_lsb);

  uint8_t message_size_msb;
  uint8_t message_size_lsb;
  uint16_t message_size = current_buffer_size;
  modbus::toMsbLsb(message_size, message_size_msb, message_size_lsb);
  buffer_vector.push_back(message_size_msb);
  buffer_vector.push_back(message_size_lsb);

  for (int i = 0; i < current_buffer_size; i++) {
    buffer_vector.push_back(*(current_buffer + i));
  }

  request->setBuffered(true);
}
