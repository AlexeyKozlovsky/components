#ifndef LIBMODBUS_TESTS_MODBUS_CLIENT_TEST_SAMPLES_H_
#define LIBMODBUS_TESTS_MODBUS_CLIENT_TEST_SAMPLES_H_

#include <gtest/gtest.h>
#include "modbus.h"

testing::AssertionResult crcRTUCheck(uint8_t *buffer,
                                     size_t buffer_size,
                                     uint8_t crc_msb,
                                     uint8_t crc_lsb);

testing::AssertionResult requestModbusFunctionCheck(uint8_t *raw_request,
                                                    uint8_t function);

testing::AssertionResult responseModbusFunctionCheck(uint8_t *raw_response,
                                                     uint8_t function);

testing::AssertionResult responseModbusByteCountCheck(uint8_t *raw_response,
                                                      uint8_t reg_count);

void testRequestModbus(modbus::ModbusClient *modbus_client,
                       uint16_t reg_num,
                       uint16_t reg_count,
                       uint8_t modbus_id,
                       uint8_t function) {

  if (modbus_client->isConnected()) {
    bool result = modbus_client->connect();
    ASSERT_EQ(result, true);
  }

  uint16_t value;

  size_t raw_request_size = 8;
  uint8_t raw_request[raw_request_size];

  size_t raw_response_size = 5 + reg_count * 2;
  uint8_t raw_response[raw_response_size];

  uint8_t *actual_raw_request = nullptr;
  uint8_t *actual_raw_response = nullptr;


  uint8_t reg_num_msb;
  uint8_t reg_num_lsb;
  modbus::toMsbLsb(reg_num, reg_num_msb, reg_num_lsb);

  uint8_t reg_count_msb;
  uint8_t reg_count_lsb;
  modbus::toMsbLsb(reg_count, reg_count_msb, reg_count_lsb);

  uint8_t crc_msb;
  uint8_t crc_lsb;
  modbus::crcRTU(raw_request, raw_request_size, crc_msb, crc_lsb);

  raw_request[0] = modbus_id;
  raw_request[1] = function;
  raw_request[2] = reg_num_msb;
  raw_request[3] = reg_num_lsb;
  raw_request[4] = reg_count_msb;
  raw_request[5] = reg_count_lsb;
  raw_request[6] = crc_msb;
  raw_request[7] = crc_lsb;

  raw_response[0] = modbus_id;
  raw_response[1] = function;
  raw_response[2] = reg_count * 2;

  modbus::ModbusResult result;

  if (function == 3) {
    result = modbus_client->readInputRegister(reg_num,
                                                value,
                                                modbus_id,
                                                actual_raw_response,
                                                actual_raw_request);
  } else if (function == 4) {
    result = modbus_client->readHoldingRegister(reg_num,
                                                value,
                                                modbus_id,
                                                actual_raw_response,
                                                actual_raw_request);
  } else {
    ASSERT_TRUE(false);
  }


  ASSERT_NE(actual_raw_request, nullptr);
  ASSERT_NE(actual_raw_response, nullptr);
  EXPECT_EQ(result != modbus::TCP_TIMEOUT_ERROR, modbus_client->isConnected());

  for (int i = 0; i < raw_request_size; i++) {
    EXPECT_EQ(raw_request[i], actual_raw_request[i]);
  }

  if (result == modbus::NO_MODBUS_ERROR) {
    for (int i = 0; i < 3; i++) {
      EXPECT_EQ(raw_response[i], actual_raw_response[i]);
    }

    auto crc_result = crcRTUCheck(raw_response, raw_response_size,
                                  raw_response[raw_request_size - 2], raw_response[raw_response_size - 1]);
    EXPECT_TRUE(crc_result);
  }

  delete actual_raw_response;
  delete actual_raw_request;
}


#endif //LIBMODBUS_TESTS_MODBUS_CLIENT_TEST_SAMPLES_H_
