#include "modbus_client_test_samples.h"

#include <modbus.h>


testing::AssertionResult crcRTUCheck(uint8_t *raw_response,
                                  size_t response_size,
                                  uint8_t crc_msb,
                                  uint8_t crc_lsb) {
  uint8_t crc_msb_actual;
  uint8_t crc_lsb_actual;
  modbus::crcRTU(raw_response, response_size, crc_msb_actual, crc_lsb_actual);

  if (crc_msb_actual == crc_msb && crc_lsb_actual == crc_lsb) {
    return testing::AssertionSuccess();
  } else {
    return testing::AssertionFailure()
    << "crc_msb = " << crc_msb << ", crc_msb_actual = " << crc_msb_actual << "\t"
    << "crc_lsb = " << crc_lsb << ", crc_lsb_actual = " << crc_lsb_actual;
  }
}

testing::AssertionResult requestModbusFunctionCheck(uint8_t *raw_request,
                                                    uint8_t function) {
  uint8_t real_function = raw_request[1];
  if (real_function == function) {
    return testing::AssertionSuccess();
  } else {
    return testing::AssertionFailure() << "req_function is: " << function << "\t"
    << "real function is: " << real_function;
  }
}

testing::AssertionResult responseModbusFunctionCheck(uint8_t *raw_response,
                                                     uint8_t function) {
  uint8_t real_function = raw_response[1];
  if (real_function == function) {
    return testing::AssertionSuccess();
  } else {
    return testing::AssertionFailure() << "req_function is: " << function << "\t"
                                       << "real function is: " << real_function;
  }
}


/**
 * Проверка на корректное значения количества значащих байт в ответе на запрос
 *
 * \warning Используется при тестировании запросов на чтение
 *
 * \warning Подразумевается, что
 *
 * @param raw_response -- буфер ответа на запрос
 * @param reg_count -- количество регистров, которые необходимо было прочитать
 * @return
 */
testing::AssertionResult responseModbusByteCountCheck(uint8_t *raw_response,
                                                      uint8_t reg_count) {
  uint8_t function = raw_response[1];
  if (function == 3 || function == 4) {
    uint8_t byte_count = raw_response[2];

    if (byte_count == reg_count * 2) {
      return testing::AssertionSuccess();
    } else {
      return testing::AssertionFailure() << "req_byte_count is: " << reg_count * 2 << "\t"
      << "real byte count is: " << byte_count;
    }
  }

  return testing::AssertionSuccess();
}












