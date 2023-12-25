#ifndef MODBUSTCPD_SERVICES_REQUESTS_REQUEST_H_
#define MODBUSTCPD_SERVICES_REQUESTS_REQUEST_H_

#include <atomic>
#include <chrono>
#include <string>
#include <functional>
#include <memory>

#include <utils/baseutils.h>

enum RequestState {
  CREATED,
  REQUESTED,
  RESPONSED
};


class Request {
  friend class RequestManager;
 public:
  inline bool isBuffered() const {
    return buffered;
  }

  inline void setBuffered(bool buffered) {
    this->buffered = buffered;
  }

  inline RequestState getState() const {
    return state;
  }

  inline uint16_t getTransactionID() const {
    return transaction_num;
  }

  inline uint8_t getSlaveID() const {
    return slave_id;
  }

  inline VARIANT__D &getReadValue() {
    return read_value;
  }

  inline VARIANT__D &getWriteValue() {
    return write_value;
  }

  /**
   * Метод, возращающий буфер PDU
   */
  virtual void getPDU(uint8_t **buffer, uint16_t &buffer_size) = 0;

 protected:
  std::atomic<bool> buffered;
  std::atomic<bool> finished;

  std::chrono::time_point<std::chrono::system_clock> time_created;
  std::chrono::time_point<std::chrono::system_clock> time_requested;
  std::chrono::time_point<std::chrono::system_clock> time_responsed;

  int priority;

  uint16_t transaction_num;
  uint8_t slave_id;

  VARIANT__D read_value;
  VARIANT__D write_value;

  RequestState state;

  std::function<void(ErrorCode*, Request*)> on_requested_callback;
  std::function<void(ErrorCode*, Request*)> on_responsed_callback;

  virtual void onCreated();
  virtual void onRequested();
  virtual void onResponsed();
};

#endif //MODBUSTCPD_SERVICES_REQUESTS_REQUEST_H_
