#include "tcpcommunicator.h"

#include <utils/modbusutils.h>


void TCPCommunicator::setIP(const std::string &ip, bool to_update) {
  this->ip = ip;
  if (to_update) update();
}

std::string TCPCommunicator::getIP() const {
  return ip;
}

void TCPCommunicator::setPort(uint16_t port, bool to_update) {
  this->port = port;
  if (to_update) update();
}

uint16_t TCPCommunicator::getPort() const {
  return port;
}

void TCPCommunicator::setAddress(const std::string &ip, uint16_t port, bool to_update) {

}

bool TCPCommunicator::connect() {
  std::cout << "CONNECTION..." << std::endl;
  boost::system::error_code ec;
  endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(ip, ec), port);

  if (!socket.socket().is_open())
    socket.socket().open(tcp::v4());

  auto log = [&](error_code ec, tcp::endpoint const& next) {
    std::cout << ec.message() << " next:" << next << " "
              << (socket.socket().is_open() ? "open" : "closed")
              << " bound:" << socket.socket().local_endpoint()
              << std::endl;
    return true;
  };


  bool connected = false;
  boost::system::error_code connect_ec = boost::asio::error::would_block;
  boost::asio::steady_timer timer(service);
  socket.socket().async_connect(endpoint, [&](auto &_ec) {
    timer.cancel();
    std::cout << "CCC" << _ec.message() << " " << _ec << std::endl;
    if (_ec.value() == 10061) {
      std::cout << "TIIIILT" << std::endl;
      service.stop();
    } else if (_ec.value() == 0) {
      std::cout << " --> Final " << _ec.message() << " local "
                << socket.socket().local_endpoint() << " to "
                << socket.socket().remote_endpoint() << "\n\n";
      connected = true;
    }
  });

  timer.expires_at(std::chrono::steady_clock::now() + std::chrono::seconds(connect_timeout));
  timer.async_wait([&](auto &_ec) {
    if (_ec.value() == 0) {
      socket.socket().cancel();
      service.stop();
    }
  });
  // !!!!!!!!!!!!!!! ЗДЕСЬ ОБЯЗАТЕЛЬНО reset перед run
  service.reset();
  service.run();
  return connected;
}
void TCPCommunicator::disconnect() {
  if (socket.socket().is_open()) {
    boost::system::error_code ec;
    socket.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    socket.socket().close();
  }
}

bool TCPCommunicator::sendRawRequest(uint8_t *raw_request,
                                     uint16_t raw_request_size,
                                     uint8_t *raw_response,
                                     uint16_t &raw_response_size) {
  comm_mutex.lock();
  beast::error_code _ec;
  service.stop();
  socket.socket().remote_endpoint(_ec);
  std::cout << "Remote endpoint ec: " << _ec.message() << _ec << std::endl;
  if (!_ec) {
    static uint8_t read_buffer[256];
    boost::asio::streambuf asio_buffer;
    modbus::make_stream_from_buffer(asio_buffer, raw_request, raw_request_size);
    socket.socket().write_some(asio_buffer.data(), _ec);

    // TODO: Непонятно, работает или нет. Лучше, наверное оставить, если не будет мешать.
    const std::chrono::time_point<std::chrono::steady_clock> time_point =
        std::chrono::steady_clock::now() + std::chrono::seconds(request_timeout);
    socket.expires_at(time_point);

    raw_response_size = connection.read_with_timeout(socket.socket(), boost::asio::buffer(read_buffer), request_timeout, service);
//    raw_response_size = socket.read_some(boost::asio::buffer(read_buffer), ec);
//    raw_response_size = 0;
    if (raw_response_size == 0) {
      comm_mutex.unlock();
      return false;
    }

    // Здесь будет блок кода, который возвращает false, если ответ по таймауту не пришел
    std::cout << "[LIBMODBUS LOG] REQUEST: ";
    for (size_t i = 0; i < raw_request_size; i++) {
      std::cout << unsigned (raw_request[i]) << " ";
    }

    std::cout << "\tRESPONSE: ";
    for (size_t i = 0; i < raw_response_size; i++) {
      std::cout << unsigned (read_buffer[i]) << " ";
      raw_response[i] = read_buffer[i];
    }

    std::cout << std::endl;
  } else {
    comm_mutex.unlock();
    return false;
  }

  comm_mutex.unlock();

  return true;
}

void TCPCommunicator::update() {

}
