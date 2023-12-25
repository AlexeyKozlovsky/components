#include "modbusclient.h"

static const int DEFAULT_PERIOD = 2000;
static const int DEFAULT_MAX_BUFFER_SIZE = 2048;
static const int DEFAULT_TACT = 500;


ModbusClient::ModbusClient(): period(DEFAULT_PERIOD),
                              max_buffer_size(DEFAULT_MAX_BUFFER_SIZE),
                              _tact(DEFAULT_TACT),
                              to_stop(false),
                              last_requested_time(std::chrono::system_clock::now()) {
  request_creator = std::make_shared<RequestCreator>();
  request_manager = std::make_shared<RequestManager>();
}

bool ModbusClient::connect() {
  return communicator->connect();
}
void ModbusClient::disconnect() {
  communicator->disconnect();
}

bool ModbusClient::start() {
  if (!is_running) {
    working_thread = std::thread(&ModbusClient::process, this);
    return true;
  } else return false;
}

void ModbusClient::stop() {
  to_stop = false;
}


void ModbusClient::process() {
  is_running = true;

  while (!to_stop) {
    auto now = std::chrono::system_clock::now();
    auto ms_spent = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_requested_time).count();
    if (ms_spent >= period || request_manager->getBufferSize() >= max_buffer_size) {
      last_requested_time = now;
      request_manager->getBuffer(&buffer, actual_buffer_size);
      sendRequestParseResponse();
      request_manager->clearBuffer();
    }

    if (buffer != nullptr) delete []buffer;
    std::this_thread::sleep_for(std::chrono::milliseconds(_tact));
  }

  is_running = false;
}

std::shared_ptr<Request> ModbusClient::readInputRegister(uint16_t reg_num,
                                                         uint8_t &value,
                                                         uint8_t slave_id,
                                                         std::function<void(ErrorCode *,
                                                                                            Request*)> callback,
                                                         uint8_t **raw_response,
                                                         uint8_t **raw_request) {
  return std::shared_ptr<Request>();
}
std::shared_ptr<Request> ModbusClient::readInputRegisters(uint16_t reg_num,
                                                          uint16_t reg_count,
                                                          std::vector<uint16_t> &result,
                                                          uint8_t slave_id,
                                                          std::function<void(ErrorCode *,
                                                                                            Request*)> callback,
                                                          uint8_t **raw_response,
                                                          uint8_t **raw_request) {

  auto request_1_callback = std::bind(callback, std::placeholders::_1, std::placeholders::_2);
  auto request_1 = request_creator->createReadInputRegistersRequest(reg_num,
                                                                    reg_count,
                                                                    slave_id,
                                                                    request_1_callback);
  request_manager->addRequest(request_1);
  return std::shared_ptr<Request>();
}
std::shared_ptr<Request> ModbusClient::readHoldingRegister(uint16_t reg_num,
                                                           uint8_t &value,
                                                           uint8_t slave_id,
                                                           std::function<void(ErrorCode *,
                                                                                            Request*)> callback,
                                                           uint8_t **raw_response,
                                                           uint8_t **raw_request) {
  return std::shared_ptr<Request>();
}
std::shared_ptr<Request> ModbusClient::readHoldingRegisters(uint16_t reg_num,
                                                            uint16_t reg_count,
                                                            std::vector<uint16_t> &result,
                                                            uint8_t slave_id,
                                                            std::function<void(ErrorCode *,
                                                                                            Request*)> callback,
                                                            uint8_t **raw_response,
                                                            uint8_t **raw_request) {
  return std::shared_ptr<Request>();
}
std::shared_ptr<Request> ModbusClient::writeHoldingRegister(uint16_t reg_num,
                                                            uint8_t value,
                                                            uint8_t slave_id,
                                                            std::function<void(ErrorCode *,
                                                                                            Request*)> callback,
                                                            uint8_t **raw_response,
                                                            uint8_t **raw_request) {
  return std::shared_ptr<Request>();
}
std::shared_ptr<Request> ModbusClient::writeHoldingRegisters(uint16_t reg_num,
                                                             uint8_t value,
                                                             uint8_t slave_id,
                                                             std::function<void(ErrorCode *,
                                                                                            Request*)> callback,
                                                             uint8_t **raw_response,
                                                             uint8_t **raw_request) {
  return std::shared_ptr<Request>();
}