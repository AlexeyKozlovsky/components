#ifndef LIBMODBUSTCP_SERVICES_TCPCOMMUNICATOR_H_
#define LIBMODBUSTCP_SERVICES_TCPCOMMUNICATOR_H_

#include <string>

#include <boost/asio.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <mutex>

#include "services/tcp_socket.h"
#include "services/communicator.h"


class TCPCommunicator: public Communicator {
 public:
  void setIP(const std::string &ip, bool to_update = false);
  std::string getIP() const;
  void setPort(uint16_t port, bool to_update = false);
  uint16_t getPort() const;

  void setAddress(const std::string &ip, uint16_t port, bool to_update = false);

  bool connect() override;
  void disconnect() override;

  /**
   * Вспомогательный метод для отправки сырого запроса по MODBUS.
   * Можно послать любой запрос, достаточно просто сформировать буфер
   * @param raw_request -- буфер сырого запроса
   * @param raw_request_size -- размер буфера сырого запроса
   * @param raw_response -- буфер сырого ответа
   * @param raw_response_size -- размер буфера сырого ответа
   * @return true, если все прошло без ошибок, иначе -- false
   */
  bool sendRawRequest(uint8_t *raw_request, uint16_t raw_request_size,
                      uint8_t *raw_response, uint16_t &raw_response_size) override;

  void update();
 private:
  std::string ip;
  int port;

  boost::asio::io_service service;
  TcpConnection connection;

  boost::asio::ip::tcp::endpoint endpoint;
  boost::beast::tcp_stream socket;

  std::mutex comm_mutex;
};

#endif //LIBMODBUSTCP_SERVICES_TCPCOMMUNICATOR_H_
