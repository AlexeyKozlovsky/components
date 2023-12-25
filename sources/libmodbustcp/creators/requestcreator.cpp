#include "requestcreator.h"

#include <utility>


std::shared_ptr<Request> RequestCreator::createReadInputRegistersRequest(uint16_t reg_num,
                                                                         uint16_t reg_count, uint8_t slave_id,
                                                                         std::function<void(ErrorCode *,
                                                                                            Request*)> on_responsed_callback,
                                                                         std::function<void(ErrorCode *,
                                                                                            Request*)> on_requested_callback) {

  auto request = std::shared_ptr<ReadInputRegistersRequest>(new ReadInputRegistersRequest(reg_num, reg_count,
                                                                                          std::move(on_responsed_callback)));
  request->transaction_num = transaction_num++;
  request->slave_id = slave_id;
  return request;
}
std::shared_ptr<Request> RequestCreator::createReadHoldingRegistersRequest(uint16_t reg_num,
                                                                           uint16_t reg_count,
                                                                           std::function<void(ErrorCode *,
                                                                                            Request*)> on_responsed_callback,
                                                                           std::function<void(ErrorCode *,
                                                                                            Request*)> on_requested_callback) {
  return std::shared_ptr<Request>();
}
std::shared_ptr<Request> RequestCreator::createWriteHoldingRegistersRequest(uint16_t reg_num,
                                                                            const std::vector<uint8_t> &values,
                                                                            std::function<void(ErrorCode *,
                                                                                            Request*)> on_responsed_callback,
                                                                            std::function<void(ErrorCode *,
                                                                                            Request*)> on_requested_callback) {
  return std::shared_ptr<Request>();
}
