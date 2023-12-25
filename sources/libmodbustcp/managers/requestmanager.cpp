#include "requestmanager.h"

#include <iostream>

RequestManager::RequestManager() {
  request_buffer_builder = std::make_shared<RequestBufferBuilder>();
}

void RequestManager::clearNonBufferedRequests() {
  auto it = std::remove_if(std::begin(requests), std::end(requests), [&](const auto &request_struct) {
    return !request_struct->isBuffered();
  });
  requests.erase(it, std::end(requests));
}

void RequestManager::clearBuffer() {
  request_buffer_builder->clearBuffer();
}

void RequestManager::clearAllRequests() {
  clearBuffer();
  requests.clear();
}

void RequestManager::addRequest(const std::shared_ptr<Request> &request) {
  requests.push_back(request);
  request_buffer_builder->addRequest(request);
}

void RequestManager::setResponsed(uint16_t transaction_num, uint16_t slave_id, VARIANT__D &value) {
  auto it = std::find_if(std::begin(requests), std::end(requests), [&](const auto &request) {
    return request->transaction_num == transaction_num;
  });

  if (it == std::end(requests)) {
    return;
  }

  std::shared_ptr<Request> request = *it;
  request->read_value = value;
  request->onResponsed();
}
