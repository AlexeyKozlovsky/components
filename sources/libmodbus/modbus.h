#ifndef DIALTEK_COMPONENTS_LIBMODBUS_MODBUS_H_
#define DIALTEK_COMPONENTS_LIBMODBUS_MODBUS_H_

#include <boost/asio.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include "tcp_socket.h"

/**
 * Макрос для удобства обработки ошибок при чтении и записи по протоколу модбас через ModbusClient
 */
#define MODBUS_RW_ERROR_HANDLE(request_method, positive_instructions, negative_instructions, error_status) \
error_status = request_method; \
if (error_status == modbus::NO_ERROR) {positive_instructions} else { negative_instructions; }

/**
 * Пространство имен, содержащие основные функции и классы для взаимодействия танго девайса с физическим
 * устройством по протоколу Modbus RTU over TCP
 */
namespace modbus {

/**
 * Перечисление, характеризующее статус ответа клиенту по модбас
 */
enum ModbusResult {
  /**
   * Ошибок нет
   */
  NO_ERROR = 0,

  /**
   * Принятый код функции не может быть обработан.
   */
  ILLEGAL_FUNCTION = 1,

  /**
   * Адрес данных, указанный в запросе, недоступен.
   */
  ILLEGAL_DATA_ADDRESS = 2,

  /**
   * 	Значение, содержащееся в поле данных запроса, является недопустимой величиной.
   */
  ILLEGAL_DATA_VALUE = 3,

  /**
   * Невосстанавливаемая ошибка имела место, пока ведомое устройство
   * пыталось выполнить затребованное действие.
   */
  SERVER_DEVICE_FAILURE = 4,

  /**
   * Ведомое устройство приняло запрос и обрабатывает его, но это требует много времени.
   * Этот ответ предохраняет ведущее устройство от генерации ошибки тайм-аута.
   */
  ACKNOWLEDGE = 5,

  /**
   * 06	Ведомое устройство занято обработкой команды.
   * Ведущее устройство должно повторить сообщение позже, когда ведомое освободится.
   */
  SERVER_DEVICE_BUSY = 6,

  /**
   * Ведомое устройство не может выполнить программную функцию, заданную в запросе.
   * Этот код возвращается для неуспешного программного запроса,
   * использующего функции с номерами 13 или 14.
   * Ведущее устройство должно запросить диагностическую информацию
   * или информацию об ошибках от ведомого.
   */
  NEGATIVE_ACKNOWLEDGE = 7,

  /**
   * 	Ведомое устройство при чтении расширенной памяти обнаружило ошибку паритета.
   * 	Ведущее устройство может повторить запрос, но обычно в таких случаях требуется ремонт.
   */
  MEMORY_PARITY_ERROR = 8,

  /**
   * Шлюз неправильно настроен или перегружен запросами.
   */
  GATEWAY_PATH_UNAVAILABLE = 10,

  /**
   * Slave устройства нет в сети или от него нет ответа.
   */
  GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND = 11,

  //@section Далее идут ошибки, напрямую НЕ относяшиеся к modbus протоколу

  /**
   * Непонятная ошибка. Используется во всех тех случаях, под которые не подходит ни один
   * из пунктов данного перечисления
   */
  UNHANDLED_ERROR = 255,

  NO_SOCKET_CONNECTION = 254,

  /**
   * Ошибка таймаута, который вызван не обязательно самим мобдасом,
   * но может и самим соединением
   */
  TCP_TIMEOUT_ERROR = 253,

  /**
   * Ответ не является корректным с точки зрения модбас протокола
   */
  INVALID_RESPONSE = 252,

  /**
   * Запрос не является корректным, с точки зрения модбас протокола
   */
  INVALID_REQUEST = 251,

  /**
   * Ошибка контрольной суммы, которая обнаружена непосредственно на стороне клиента
   */
  CRC_ERROR = 250,
};


uint16_t getMask(uint8_t byte_num, uint8_t byte_count);
uint16_t readByteValue(uint8_t byte_num, uint8_t byte_count, uint16_t value);

bool writeByteValue(uint8_t byte_num, uint8_t byte_count,
                      uint16_t value_to_write, uint16_t &value);
/**
 * Функция для подсчета контрольной суммы для связи по протоколу modbus
 * @param buffer -- буфер для которого необходимо сформирвать CRC
 * @param buffer_size -- размер буфера
 * @param crc_msb -- старший байт полученной контрольной суммы
 * @param crc_lsb -- младший байт полученной контрольной суммы
 */
void crcRTU(const uint8_t *buffer, uint16_t buffer_size, uint8_t &crc_msb, uint8_t &crc_lsb);

/**
 * Функция для разбиения 16-битного числа на старший и младший байты
 * @param data -- исходное число
 * @param lsb -- младший байт
 * @param msb -- старший байт
 */
void toMsbLsb(uint16_t data, uint8_t &lsb, uint8_t &msb);

/**
 * Функция для получения 16-битного числа из старшего и младшего байтов
 * @param lsb -- младший байт
 * @param msb -- старший байт
 * @param data -- полученное 16-битное число
 */
void fromMsbLsb(uint8_t lsb, uint8_t msb, uint16_t &data);

/**
 * Функция для разбиения 16-битного числа на старший и младший байты
 * @param data -- исходное число
 * @param lsb -- младший байт
 * @param msb -- старший байт
 */
void toMsbLsb(uint32_t data, uint16_t &lsb, uint16_t &msb);

/**
 * Функция для получения 16-битного числа из старшего и младшего байтов
 * @param lsb -- младший байт
 * @param msb -- старший байт
 * @param data -- полученное 16-битное число
 */
void fromMsbLsb(uint16_t lsb, uint16_t msb, uint32_t &data);

/**
 * Функция для конвертирования буффера как массива байтов в стркутуру данных буфера, который
 * пригоден для работы с boost
 * @param asio_buffer -- результат конвертации, буфер для работы с asio
 * @param buff -- исходный буфер в виде массива байт
 * @param buff_size -- размер исходного буфера
 * @return --
 */
int make_stream_from_buffer(boost::asio::streambuf &asio_buffer, uint8_t *buff, size_t buff_size);


/**
 * Класс для осуществления работы с модбас устройством по протоколу Modbus RTU over TCP
 * Класс содержит только основные операции для использования, а т.е. чтение INPUT регистров
 * и чтение и запись HOLDING регистров.
 *
 * Так же, планируется предусмотреть обработку ошибок
 */
class ModbusClient {
 public:
  inline std::string getIP() const {
    return ip;
  };

  inline uint16_t getPort() const {
    return port;
  };

  /**
   * Присваивает IP. Не рекомендуется использовать вместе с setPort, если в обоих случаях to_update = true.
   * Будут происходить лишние обновления. В таком случае, если надо поменять и IP, и port, есть два варианта:
   *
   * Первый вариант:
   * \code
   *    setIP("192.168.0.90", false);
   *    setPort(4001, true);
   * \endcode
   *
   * Второй вариант:
   * \code
   *    setAddress("192.168.0.90", 4001);
   * \endcode
   * @param ip -- новый ip адрес
   * @param to_update -- указывает на то, следует ли обновить сокет после изменения
   * значения IP. Если true, то сокет обновляется, иначе -- нет.
   */
  inline void setIP(std::string ip, bool to_update = false) {
    this->ip = ip;
    if (to_update) update();
  };

  /**
   * Обновляет значение порта. Рекомендации к использованию аналогичны методу \code setIP(std::string, bool) \endcode
   *
   * @param port -- новое значение порта
   * @param to_update -- указывает на то, следует ли обновить сокет после изменения
   * значения порта. Если true, то сокет обновляется, иначе -- нет.
   */
  inline void setPort(uint16_t port, bool to_update = false) {
    this->port = port;
    if (to_update) update();
  };

  /**
   * Метод для изменения всего адреса
   * @param ip
   * @param port
   * @param to_update
   */
  inline void setAddress(std::string ip, uint16_t port, bool to_update = true) {
    this->ip = ip;
    this->port = port;
    if (to_update) update();
  };

  inline bool isConnected() {
    // КОСТЫЛЬ, потом поменять
    uint16_t value;
    return readInputRegister(0, value);
  };

  ModbusClient();

  ModbusClient(std::string ip, uint16_t port);

  /**
   * Метод для установки соединения с физическим устройством
   * @return true, если соединение установлено, false -- иначе
   */
  bool connect();

  /**
   * Метод для разрыва соединеня с физическим устройством
   */
  void disconnect();

  /**
   * Метод для того, чтобы задать таймаут сокету
   * @param timeout -- время таймаута в милисекундах
   */
  void setTimeout(int timeout);

  /**
   * Метод для чтения одного Input регистра. Рекомендуется использовать его, когда
   * необходимо за раз читать только один регистр по той принчине, что не создается бесполнезного
   * вектора
   * @param reg_num -- номер начального регистра
   * @param reg_count -- количество регистров, которое надо прочитать
   * @param result -- набор 16-битных значений, которые были прочитаны из регистров
   * @return true, если все прошло без ошибок, иначе -- false
   */
  modbus::ModbusResult readInputRegister(uint16_t reg_num, uint16_t &result);

  /**
   * Метод для чтения Input регистров. Можно читать как один, так и несколько регистров
   * @param reg_num -- номер начального регистра
   * @param reg_count -- количество регистров, которое надо прочитать
   * @param result -- набор 16-битных значений, которые были прочитаны из регистров
   * @return true, если все прошло без ошибок, иначе -- false
   */
  modbus::ModbusResult readInputRegisters(uint16_t reg_num, uint16_t reg_count, std::vector<uint16_t> &result);

  /**
    * Метод для чтения Holding регистра. Рекомендуется использовать его, когда
    * необходимо за раз читать только один регистр по той принчине, что не создается бесполнезного
    * вектора.
    * @param reg_count -- количество регистров, которое надо прочитать
    * @param result -- набор 16-битных значений, которые были прочитаны из регистров
    * @return true, если все прошло без ошибок, иначе -- false
    */
  modbus::ModbusResult readHoldingRegister(uint16_t reg_num, uint16_t &result);

  /**
    * Метод для чтения Holding регистров. Можно читать как один, так и несколько регистров
    * @param reg_num -- номер начального регистра
    * @param reg_count -- количество регистров, которое надо прочитать
    * @param result -- набор 16-битных значений, которые были прочитаны из регистров
    * @return true, если все прошло без ошибок, иначе -- false
    */
  modbus::ModbusResult readHoldingRegisters(uint16_t reg_num, uint16_t reg_count, std::vector<uint16_t> &result);

  /**
   * Метод для записи значения в Holding регистр
   * @param reg_num -- номер регистра
   * @param value -- значение для записи
   * @return true, если все прошло без ошибок, иначе -- false
   */
  modbus::ModbusResult writeHoldingRegister(uint16_t reg_num, uint16_t value);

  /**
   * Метод, который пишет несколько регистров за один запрос
   * @param reg_num
   * @param values
   * @return
   */
  modbus::ModbusResult writeHoldingRegistersTrue(uint16_t reg_num, std::vector<uint16_t> values);

  /**
   * Метод для записи значенией в Holding регистры (последовательно). За несколько запросов
   * @param reg_num начальный номер регистра
   * @param values вектор значений (будут записаны последовательно в регистры под номерами начиная
   * с первого переданного
   * @return true если запись прошла успешно, false -- иначе
   */
  modbus::ModbusResult writeHoldingRegisters(uint16_t reg_num, std::vector<uint16_t> values);

 private:

  /**
   * IP адрес, который присваивается по умолчанию при создании клиента
   * с помощью конструктора без параметров
   */
  static const std::string default_ip;

  /**
   * Порт, который присваивается по умолчанию при создании клиента
   * с помощью конструктора без параметров
   */
  static const uint16_t default_port;

  int timeout;

  /**
   * IP адрес физического устройства
   */
  std::string ip;

  /**
   * Порт, на котором физическое устройство слушает MODBUS запросы
   */
  uint16_t port;

  /**
   * Содержит информацию об ошибках на транспортном уровне
   */
  boost::system::error_code ec;

  /**
   * Контекст для установления и поддержки соединения через boost
   */
  boost::asio::io_context context;
  boost::asio::io_service service;

  TcpConnection connection;

  /**
   * Эндпоинт для соединения, по которому находится физическое устройство
   */
  boost::asio::ip::tcp::endpoint endpoint;

  /**
   * Сокет для взаимодействия с физическим устройством
   */
  boost::beast::tcp_stream socket;

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
                      uint8_t *raw_response, uint16_t &raw_response_size);

  /**
   * Метод для обновления ендпоинта и сокета в соответствие с актуальными значениями
   * IP и порта
   */
  void update();

  modbus::ModbusResult handleError(uint8_t *request,
                                   uint16_t request_size,
                                   uint8_t *response,
                                   uint16_t response_size);

};
}
#endif //DIALTEK_COMPONENTS_LIBMODBUS
