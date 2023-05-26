#include <gtest/gtest.h>

#include <modbus.h>

#include "modbus_client_test_samples.h"


using modbus::ModbusClient;

namespace {
 class ModbusClientTest : public ::testing::TestWithParam<std::tuple<std::string, int, int>> {
  protected:
   std::string ip;
   int port;
   int timeout;
   ModbusClient *modbus_client;

   ModbusClientTest() {
     ip = std::get<0>(GetParam());
     port = std::get<1>(GetParam());
     timeout = std::get<2>(GetParam());

     std::cout << "timeout: " << timeout << ", ip: " << ip << ", port" << port << std::endl;
   }

   virtual ~ModbusClientTest() = default;

   virtual void SetUp() {
     modbus_client = new ModbusClient(ip, port);
     modbus_client->setTimeout(timeout);
   }

   virtual void TearDown() {
     delete modbus_client;
   }
 };


 TEST_P(ModbusClientTest, TestConnection) {
   std::cout << "MODBUS CLIENT: " << modbus_client->getIP() << " " << modbus_client->getPort() << std::endl;
   bool result = modbus_client->connect();
   std::cout << "After connect: " << result << std::endl;

   uint16_t value;
   modbus::ModbusResult request_status_code = modbus_client->readHoldingRegister(0, value);
   std::cout << "After request: " << request_status_code << std::endl;
   bool request_result = request_status_code != modbus::TCP_TIMEOUT_ERROR;

   ASSERT_EQ(result, request_result);
 }

 TEST_P(ModbusClientTest, TestReadHoldingRegister_1) {
  uint16_t reg_num = 1;
  uint16_t reg_count = 1;
  uint8_t modbus_id = 1;
  uint8_t function = 3;

  testRequestModbus(modbus_client, reg_num, reg_count, modbus_id, function);
 }

TEST_P(ModbusClientTest, TestReadHoldingRegister_5) {
  uint16_t reg_num = 5;
  uint16_t reg_count = 1;
  uint8_t modbus_id = 1;
  uint8_t function = 3;

  testRequestModbus(modbus_client, reg_num, reg_count, modbus_id, function);
}

TEST_P(ModbusClientTest, TestReadHoldingRegister_10) {
  uint16_t reg_num = 10;
  uint16_t reg_count = 1;
  uint8_t modbus_id = 1;
  uint8_t function = 3;

  testRequestModbus(modbus_client, reg_num, reg_count, modbus_id, function);
}

TEST_P(ModbusClientTest, TestReadHoldingRegister_20) {
  uint16_t reg_num = 20;
  uint16_t reg_count = 1;
  uint8_t modbus_id = 1;
  uint8_t function = 3;

  testRequestModbus(modbus_client, reg_num, reg_count, modbus_id, function);
}

TEST_P(ModbusClientTest, TestReadInputRegister_1) {
  uint16_t reg_num = 1;
  uint16_t reg_count = 1;
  uint8_t modbus_id = 1;
  uint8_t function = 4;

  testRequestModbus(modbus_client, reg_num, reg_count, modbus_id, function);
}

 INSTANTIATE_TEST_SUITE_P(
     ModbusClientTestsP,
     ModbusClientTest,
     ::testing::Values(
      std::tuple<std::string, int, int>({"192.168.127.2", 4001, 1}),
      std::tuple<std::string, int, int>({"192.168.127.3", 4001, 1}),
      std::tuple<std::string, int, int>({"192.168.127.4", 4001, 1})
      ));
}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}