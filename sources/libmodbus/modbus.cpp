#include <iostream>

#include "modbus.h"
#include "tcp_socket.h"

// TODO: Надо решить проблемы с некорреткным количеством байт в ответе по модбас, которое иногда возникает. В следствие чего, пока не понятно

using modbus::ModbusClient;

static const int DEFAULT_TIMEOUT = 5;

const std::string ModbusClient::default_ip = "192.168.127.1";
const uint16_t ModbusClient::default_port = 4001;


uint16_t modbus::getMask(uint8_t byte_num, uint8_t byte_count) {
  uint16_t mask_right = ((0xffff) << (byte_num + byte_count));
  uint16_t mask_left = ((0xffff) >> (15 - (byte_num - 1)));
  uint16_t mask = mask_left | mask_right;
  return mask;
}

uint16_t modbus::readByteValue(uint8_t byte_num, uint8_t byte_count, uint16_t value) {
  uint16_t mask = getMask(byte_num, byte_count) ^ 0xffff;
  uint16_t result = (value & mask) >> byte_num;

  return result;
}


bool modbus::writeByteValue(uint8_t byte_num, uint8_t byte_count, uint16_t value_to_write, uint16_t &value) {
  std::cout << "VALUE BEFORE: " << unsigned(value) << std::endl;
  uint16_t mask = getMask(byte_num, byte_count);
  uint16_t value_mask = (0xffff >> (15 - byte_count - 1));

//  if ((value_to_write & value_mask) != value_to_write) return false;

  std::cout << "VALUE TO WRITE BEFORE: " << unsigned(value_to_write) << std::endl;

  value_to_write = ((value_to_write & value_mask) << byte_num);

  std::cout << "VALUE TO WRITE AFTER: " << unsigned(value_to_write) << std::endl;
  value &= mask;
  value |= value_to_write;

  std::cout << "VALUE AFTER: " << unsigned(value) << std::endl;

  return true;

}

void modbus::toMsbLsb(uint16_t data, uint8_t &lsb, uint8_t &msb) {
  lsb = data >> 8;
  msb = data & 0x00FF;
}

void modbus::fromMsbLsb(uint8_t lsb, uint8_t msb, uint16_t &data) {
  data = lsb;
  data <<= 8;
  data = msb | data;
}

void modbus::toMsbLsb(uint32_t data, uint16_t &lsb, uint16_t &msb) {
  msb = data >> 16;
  lsb = data & 0xFFFF;
}

void modbus::fromMsbLsb(uint16_t lsb, uint16_t msb, uint32_t &data) {
  data = msb;
  data <<= 16;
  data = lsb | data;
}

void modbus::crcRTU(const uint8_t *buffer, uint16_t buffer_size, uint8_t &crc_msb, uint8_t &crc_lsb) {
  uint16_t pos;
  uint8_t i;
  uint16_t crc = 0xFFFF;

  for (pos = 0; pos < buffer_size; pos++){
    crc ^= (uint16_t)buffer[pos];          // XOR byte into least sig. byte of crc

    for (uint8_t i = 8; i != 0; i--){    // Loop over each bit
      if ((crc & 0x0001) != 0){      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }

  crc_lsb = crc >> 8;
  crc_msb = crc & 0x00FF;
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
}

int modbus::make_stream_from_buffer(boost::asio::streambuf &asio_buffer, uint8_t *buff, size_t buff_size) {
  auto out = std::ostreambuf_iterator<char>(&asio_buffer);
  for (size_t i = 0; i < buff_size; i++)
    *out++ = buff[i];

  return buff_size;
}

modbus::ModbusClient::ModbusClient(): ip(default_ip), port(default_port), socket(service) {
  update();
//  socket.socket(service)
  setTimeout(DEFAULT_TIMEOUT);

}

modbus::ModbusClient::ModbusClient(std::string ip, uint16_t port): ip(ip), port(port),
  socket(service) {
  update();
  setTimeout(DEFAULT_TIMEOUT);
}

bool modbus::ModbusClient::connect() {
  std::cout << "CONNECTION..." << std::endl;
//  typedef boost::asio::detail::socket_option::integer<SOL_SOCKET, SO_RCVTIMEO> rcv_timeout_option; //somewhere in your headers to be used everywhere you need it
//...
//  socket.socket().set_option(rcv_timeout_option{ 200 });
  endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(ip, ec), port);
//  service.run();
//  socket.expires_after(std::chrono::seconds(timeout));
//  socket.async_connect(endpoint, [](error_code _ec) {
//    std::cout << "TEEEEEEEEEEEEEEEST" << std::endl;
//    if (_ec == beast::error::timeout) {
//      std::cerr << "Timeout error while connection attempt" << std::endl;
//    }
//  });
//
//  service.stop();
////  socket.expires_never();

//  socket.socket().close();
  if (!socket.socket().is_open())
    socket.socket().open(tcp::v4());
//  std::cout<< "TIIIILT: " << socket.socket().is_open() << std::endl;
//  socket.socket().bind(endpoint);
//  socket.expires_after(std::chrono::seconds(timeout));

  auto log = [&](error_code ec, tcp::endpoint const& next) {
    std::cout << ec.message() << " next:" << next << " "
              << (socket.socket().is_open() ? "open" : "closed")
              << " bound:" << socket.socket().local_endpoint()
              << std::endl;
    return true;
  };


  boost::system::error_code connect_ec = boost::asio::error::would_block;
//  boost::asio::deadline_timer timer(service, boost::posix_time::seconds(timeout));
  boost::asio::steady_timer timer(service);
  std::cout << "timer defined" << std::endl;
  socket.socket().async_connect(endpoint, [&](auto &_ec) {
//    std::cout << " --> Final " << ec.message() << " local "
//              << socket.socket().local_endpoint() << " to "
//              << socket.socket().remote_endpoint() << "\n\n";
    timer.cancel();
    std::cout << "CCC" << _ec.message() << " " << _ec << std::endl;
    if (_ec.value() == 10061) {
      std::cout << "TIIIILT" << std::endl;
      service.stop();
    } else if (_ec.value() == 0) {
      std::cout << " --> Final " << _ec.message() << " local "
          << socket.socket().local_endpoint() << " to "
          << socket.socket().remote_endpoint() << "\n\n";
    }
  });

  std::cout << "socket started connection process" << std::endl;

//  boost::posix_time::time_duration time_duration = boost::posix_time::seconds(timeout);
  timer.expires_at(std::chrono::steady_clock::now() + std::chrono::seconds(timeout));
  timer.async_wait([&](auto &_ec) {
    std::cout << "_EC in timer " << _ec.message() << _ec << std::endl;
    if (_ec.value() == 0) {
      socket.socket().cancel();
      std::cout << "Socket cancel connection " << _ec.message() << " " << _ec << std::endl;
//      socket.socket().close();
      service.stop();
    }
//      socket.socket().close();
  });

  std::cout << "timer started" << std::endl;


  // !!!!!!!!!!!!!!! ЗДЕСЬ ОБЯЗАТЕЛЬНО reset перед run
  service.reset();
  service.run();
//  service.stop();
//  service.reset();

  std::cout << "service run" << std::endl;
//  while (connect_ec == boost::asio::error::would_block);

//  service.stop();

// TODO:
//
//  socket.async_connect(endpoint,
//                       [](error_code _ec) {
//    if (_ec == beast::error::timeout) {
//      std::cerr << "TIMEOUT ERROR WHILE CONNECTION ATTEMPT" << std::endl;
//    } else {
//      std::cout << "Connected to ep" << std::endl;
//    }
//  });

//  socket.expires_never();
//  auto future = socket.async_connect(endpoint, beast::net::use_future);
//  if (future.wait_for(std::chrono::seconds(timeout)) == std::future_status::timeout) {
//    std::cerr << "Timeout error while connection attempt" << std::endl;
//    socket.close();
//    return false;
//  }

//  connection.connect(socket, endpoint, service);
//  socket.socket().connect(endpoint, ec);
//  socket.socket().connect(endpoint, ec);
  return isConnected();
}

void modbus::ModbusClient::disconnect() {
  if (socket.socket().is_open()) socket.socket().close();
//  if (socket.socket().is_open()) socket.socket().shutdown();
}

void modbus::ModbusClient::setTimeout(int timeout) {
//  ::setsockopt(socket.socket().native_handle(), SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof timeout);//SO_SNDTIMEO for send ops
  this->timeout = timeout;
//  socket.expires_after(std::chrono::milliseconds(timeout));
}

modbus::ModbusResult modbus::ModbusClient::readInputRegisters(uint16_t reg_num,
                                                              uint16_t reg_count,
                                                              std::vector<uint16_t> &result,
                                                              uint8_t modbus_id,
                                                              uint8_t *raw_response,
                                                              uint8_t *raw_request) {
  result.resize(0);
  uint16_t request_size = 8;

//  uint8_t raw_request[request_size];
  raw_request = new uint8_t[request_size];
  *raw_request = modbus_id;
  *(raw_request + 1) = 0x04;
  toMsbLsb(reg_num, *(raw_request + 2), *(raw_request + 3));
  toMsbLsb(reg_count, *(raw_request + 4), *(raw_request + 5));
  crcRTU(raw_request, 6, *(raw_request + 6), *(raw_request + 7));

  // Здесь размер был 5 + 2 * reg_count
  uint16_t req_received_bytes = 5 + 2 * reg_count;
//  uint8_t raw_response[256];
  raw_response = new uint8_t[256];
  uint16_t recieved_bytes;

  bool is_connected = sendRawRequest(raw_request, 8, raw_response, recieved_bytes);
  if (!is_connected) return modbus::NO_SOCKET_CONNECTION;

  // Здесь делаем проверки на то, чтобы размер ответа соответствовал запросу
  if (recieved_bytes != req_received_bytes) return modbus::INVALID_RESPONSE;

  auto error_status = handleError(raw_request, request_size, raw_response, recieved_bytes);
  if (error_status != modbus::NO_MODBUS_ERROR) return error_status;

  uint16_t values_count = *(raw_response + 2) / 2;
  for (uint16_t i = 0; i < values_count; i++) {
    uint16_t current_value;
    fromMsbLsb(*(raw_response + 3 + i * 2), *(raw_response + 4 + i * 2), current_value);
    result.push_back(current_value);
  }

  return error_status;
}

modbus::ModbusResult modbus::ModbusClient::readInputRegister(uint16_t reg_num,
                                                             uint16_t &result,
                                                             uint8_t modbus_id,
                                                             uint8_t *raw_response,
                                                             uint8_t *raw_request) {
  uint16_t request_size = 8;
//  uint8_t raw_request[request_size];
  raw_request = new uint8_t[request_size];

  *raw_request = modbus_id;
  *(raw_request + 1) = 0x04;
  toMsbLsb(reg_num, *(raw_request + 2), *(raw_request + 3));
  toMsbLsb(1, *(raw_request + 4), *(raw_request + 5));
  crcRTU(raw_request, 6, *(raw_request + 6), *(raw_request + 7));

  // Здесь размер был 7
  uint16_t req_received_bytes = 7;
//  uint8_t raw_response[256];
  raw_response = new uint8_t[256];
  uint16_t recieved_bytes;

  if (!sendRawRequest(raw_request, request_size, raw_response, recieved_bytes))
    return modbus::NO_SOCKET_CONNECTION;

  if (recieved_bytes != req_received_bytes) return modbus::INVALID_RESPONSE;

  auto error_status = handleError(raw_request, request_size, raw_response, recieved_bytes);
  if (error_status != modbus::NO_MODBUS_ERROR) return error_status;

  fromMsbLsb(*(raw_response + 3), *(raw_response + 4), result);
  return error_status;
}

modbus::ModbusResult modbus::ModbusClient::readHoldingRegisters(uint16_t reg_num,
                                                                uint16_t reg_count,
                                                                std::vector<uint16_t> &result,
                                                                uint8_t modbus_id,
                                                                uint8_t *raw_response,
                                                                uint8_t *raw_request) {
  result.resize(0);
  uint16_t request_size = 8;

//  uint8_t raw_request[request_size];
  raw_request = new uint8_t[request_size];
  *raw_request = modbus_id;
  *(raw_request + 1) = 0x03;
  toMsbLsb(reg_num, *(raw_request + 2), *(raw_request + 3));
  toMsbLsb(reg_count, *(raw_request + 4), *(raw_request + 5));
  crcRTU(raw_request, 6, *(raw_request + 6), *(raw_request + 7));

  // Здесь размер был 5 + 2 * reg_count.
  uint16_t req_received_bytes = 5 + 2 * reg_count;
//  uint8_t raw_response[256];
  raw_response = new uint8_t[256];
  uint16_t recieved_bytes;
  if (!sendRawRequest(raw_request, request_size, raw_response, recieved_bytes))
    return modbus::NO_SOCKET_CONNECTION;

  if (recieved_bytes != req_received_bytes) return modbus::INVALID_RESPONSE;

  auto error_status = handleError(raw_request, request_size, raw_response, recieved_bytes);
  if (error_status != modbus::NO_MODBUS_ERROR) return error_status;

  uint16_t  values_count = *(raw_response + 2) / 2;
  for (uint16_t i = 0; i < values_count; i++) {
    uint16_t current_value;
    fromMsbLsb(*(raw_response + 3 + i * 2), *(raw_response + 4 + i * 2), current_value);
    result.push_back(current_value);
  }

  return error_status;
}

modbus::ModbusResult modbus::ModbusClient::readHoldingRegister(uint16_t reg_num,
                                                               uint16_t &result,
                                                               uint8_t modbus_id,
                                                               uint8_t *raw_response,
                                                               uint8_t *raw_request) {
  uint16_t request_size = 8;

//  uint8_t raw_request[request_size];
  raw_request = new uint8_t[request_size];
  *raw_request = modbus_id;
  *(raw_request + 1) = 0x03;
  toMsbLsb(reg_num, *(raw_request + 2), *(raw_request + 3));
  toMsbLsb(1, *(raw_request + 4), *(raw_request + 5));
  crcRTU(raw_request, 6, *(raw_request + 6), *(raw_request + 7));

  // Здесь был размер 7
  uint16_t req_received_bytes = 7;
//  uint8_t raw_response[256];
  raw_response = new uint8_t[256];
  uint16_t recieved_bytes;
  if (!sendRawRequest(raw_request, request_size, raw_response, recieved_bytes))
    return modbus::NO_SOCKET_CONNECTION;

  if (recieved_bytes != req_received_bytes) return modbus::INVALID_RESPONSE;

  auto error_status = handleError(raw_request, request_size, raw_response, recieved_bytes);
  if (error_status != modbus::NO_MODBUS_ERROR) return error_status;

  fromMsbLsb(*(raw_response + 3), *(raw_response + 4), result);
  return error_status;
}

modbus::ModbusResult modbus::ModbusClient::writeHoldingRegister(uint16_t reg_num,
                                                                uint16_t value,
                                                                uint8_t modbus_id,
                                                                uint8_t *raw_response,
                                                                uint8_t *raw_request) {
  uint16_t request_size = 8;
//  uint8_t raw_request[request_size];
  raw_request = new uint8_t[request_size];
  *raw_request = modbus_id;
  *(raw_request + 1) = 0x06;
  toMsbLsb(reg_num, *(raw_request + 2), *(raw_request + 3));
  toMsbLsb(value, *(raw_request + 4), *(raw_request + 5));
  crcRTU(raw_request, 6, *(raw_request + 6), *(raw_request + 7));

  // Здесь размер был 8
  uint16_t req_received_bytes = 8;
//  uint8_t raw_response[256];
  raw_response = new uint8_t[256];
  uint16_t recieved_bytes;

  if (!sendRawRequest(raw_request, request_size, raw_response, recieved_bytes))
    return modbus::NO_SOCKET_CONNECTION;

  if (recieved_bytes != req_received_bytes) return modbus::INVALID_RESPONSE;

  auto error_status = handleError(raw_request, request_size, raw_response, recieved_bytes);
  return error_status;
}

bool modbus::ModbusClient::sendRawRequest(uint8_t *raw_request,
                                          uint16_t raw_request_size,
                                          uint8_t *raw_response,
                                          uint16_t &raw_response_size) {
//  bool is_connected = socket.socket().is_open();
//  if (!is_connected) socket.socket().connect(endpoint, ec);

  comm_mutex.lock();
  beast::error_code _ec;
  socket.socket().remote_endpoint(_ec);
  if (!_ec) {
    static uint8_t read_buffer[256];
    boost::asio::streambuf asio_buffer;
    make_stream_from_buffer(asio_buffer, raw_request, raw_request_size);
    socket.socket().write_some(asio_buffer.data(), ec);

    // TODO: Непонятно, работает или нет. Лучше, наверное оставить, если не будет мешать.
    const std::chrono::time_point<std::chrono::steady_clock> time_point =
        std::chrono::steady_clock::now() + std::chrono::seconds(timeout);
    socket.expires_at(time_point);

    raw_response_size = connection.read_with_timeout(socket.socket(), boost::asio::buffer(read_buffer), timeout, service);
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

modbus::ModbusResult modbus::ModbusClient::writeHoldingRegistersTrue(uint16_t reg_num,
                                                                     std::vector<uint16_t> values,
                                                                     uint8_t modbus_id,
                                                                     uint8_t *raw_response,
                                                                     uint8_t *raw_request) {
  if (values.empty()) return modbus::INVALID_REQUEST;

  // адрес устройства (1 байт) + функц. код (1 байт) + адрес первого регистра (2 байта)
  // + количество регистров (2 байта) + количество байт далее (1 байт) + crc (2 байта) +
  // сами данные (2 * values.size()) = 9 + 2 * values.size()
  uint16_t request_size = 9 + 2 * values.size();
  if (raw_request == nullptr) {
    raw_request = new uint8_t[request_size];
  }

  raw_request[0] = modbus_id;
  raw_request[1] = 0x10;
  toMsbLsb(reg_num, raw_request[2], raw_request[3]);
  toMsbLsb((uint16_t) values.size(), raw_request[4], raw_request[5]);
  raw_request[6] = values.size() * 2;

  uint16_t current_index = 7;
  for (uint16_t value: values) {
    toMsbLsb(value, raw_request[current_index], raw_request[current_index + 1]);
    current_index += 2;
  }

  crcRTU(raw_request, current_index, raw_request[current_index], raw_request[current_index + 1]);

  // Здесь размер задавался явно и был равен 8. Сейчас, на всякий случай, установим размер с запасом
  uint16_t req_received_bytes = 8;

  if (raw_response == nullptr) {
    raw_response = new uint8_t[256];
  }

  uint16_t recieved_bytes;

  if (!sendRawRequest(raw_request, request_size, raw_response, recieved_bytes))
    return modbus::NO_SOCKET_CONNECTION;

  if (recieved_bytes != req_received_bytes) return modbus::INVALID_RESPONSE;

  auto error_status = handleError(raw_request, request_size, raw_response, recieved_bytes);
  return error_status;
}

modbus::ModbusResult modbus::ModbusClient::writeHoldingRegisters(uint16_t reg_num, std::vector<uint16_t> values,
                                                                 uint8_t modbus_id,
                                                                 uint8_t *raw_request, uint8_t *raw_response) {
  bool result = true;
  for (uint8_t i = 0; i < values.size(); i++) {
    auto error_status = writeHoldingRegister(reg_num + i, values[i], modbus_id);
    if (error_status != modbus::NO_MODBUS_ERROR) return error_status;
  }

  return modbus::NO_MODBUS_ERROR;
}

void modbus::ModbusClient::update() {
//  context.reset();
//  context.run();
//  if (socket.socket().is_open()) socket.socket().close();
  endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(ip, ec), port);
//  socket.socket().connect(endpoint, ec);
}


modbus::ModbusResult modbus::ModbusClient::handleError(uint8_t *request,
                                                       uint16_t request_size,
                                                       uint8_t *response,
                                                       uint16_t response_size) {
  if (request_size < 4) return modbus::INVALID_REQUEST;
  if (response_size < 5) return modbus::INVALID_RESPONSE;

  // Блок проверки на контрольную сумму
  uint8_t crc_msb;
  uint8_t crc_lsb;

  crcRTU(response, response_size - 2, crc_msb, crc_lsb);

  if (crc_msb != response[response_size - 2] || crc_lsb != response[response_size - 1]) {
    return modbus::CRC_ERROR;
  }

  // Блок проверки на modbus ошибки
  uint8_t request_func_code = request[1];
  uint8_t response_func_code = response[1];
  if (request_func_code != response_func_code) {
    if ((request_func_code | 128) == response_func_code) {
      auto result = static_cast<modbus::ModbusResult>(response[2]);
      return result;
    } else {
      return modbus::INVALID_RESPONSE;
    }
  }

  return modbus::NO_MODBUS_ERROR;
}