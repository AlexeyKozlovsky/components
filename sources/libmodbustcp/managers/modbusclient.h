#ifndef MODBUSTCPD_SERVICES_MODBUSCLIENT_H_
#define MODBUSTCPD_SERVICES_MODBUSCLIENT_H_

#include <chrono>
#include <memory>
#include <thread>

#include <creators/requestcreator.h>
#include <creators/requestbufferbuilder.h>

#include "services/communicator.h"

#include "services/requests/request.h"
#include "requestmanager.h"

class ModbusClient {
 public:
  bool connect();
  void disconnect();

  bool start();
  void stop();

  virtual std::shared_ptr<Request> readInputRegister(uint16_t reg_num,
                                                     uint8_t &value,
                                                     uint8_t slave_id = 1,
                                                     std::function<void(ErrorCode*, Request*)> callback = nullptr,
                                                     uint8_t **raw_response = nullptr,
                                                     uint8_t **raw_request = nullptr);

  virtual std::shared_ptr<Request> readInputRegisters(uint16_t reg_num,
                                                      uint16_t reg_count,
                                                      std::vector<uint16_t> &result,
                                                      uint8_t slave_id = 1,
                                                      std::function<void(ErrorCode*, Request*)> callback = nullptr,
                                                      uint8_t **raw_response = nullptr,
                                                      uint8_t **raw_request = nullptr);

  virtual std::shared_ptr<Request> readHoldingRegister(uint16_t reg_num,
                                                       uint8_t &value,
                                                       uint8_t slave_id = 1,
                                                       std::function<void(ErrorCode*, Request*)> callback = nullptr,
                                                       uint8_t **raw_response = nullptr,
                                                       uint8_t **raw_request = nullptr);

  virtual std::shared_ptr<Request> readHoldingRegisters(uint16_t reg_num,
                                                        uint16_t reg_count,
                                                        std::vector<uint16_t> &result,
                                                        uint8_t slave_id = 1,
                                                        std::function<void(ErrorCode*, Request*)> callback = nullptr,
                                                        uint8_t **raw_response = nullptr,
                                                        uint8_t **raw_request = nullptr);

  virtual std::shared_ptr<Request> writeHoldingRegister(uint16_t reg_num,
                                                        uint8_t value,
                                                        uint8_t slave_id = 1,
                                                        std::function<void(ErrorCode*, Request*)> callback = nullptr,
                                                        uint8_t **raw_response = nullptr,
                                                        uint8_t **raw_request = nullptr);

  virtual std::shared_ptr<Request> writeHoldingRegisters(uint16_t reg_num,
                                                         uint8_t value,
                                                         uint8_t slave_id = 1,
                                                         std::function<void(ErrorCode*, Request*)> callback = nullptr,
                                                         uint8_t **raw_response = nullptr,
                                                         uint8_t **raw_request = nullptr);

 protected:
  std::shared_ptr<Communicator> communicator;

  std::shared_ptr<RequestCreator> request_creator;
  std::shared_ptr<RequestManager> request_manager;

  /**
   * Параметр, характеризующий период отправок запросов
   */
  int period;

  /**
   * Параметр, характеризующий максимальный размер буфера, при котором надо уже осуществлять отправку
   */
  int max_buffer_size;

  /**
   * Такт работы цикла фонового потока, чтобы проверять буффер на размер и т.д.
   */
  int _tact;

  uint8_t *buffer;
  uint16_t actual_buffer_size;

  std::atomic<bool> to_stop;
  std::atomic<bool> is_running;

  std::chrono::system_clock::time_point last_requested_time;

  std::thread working_thread;

  ModbusClient();

  void process();
  virtual void sendRequestParseResponse() = 0;
};

#endif //MODBUSTCPD_SERVICES_MODBUSCLIENT_H_
