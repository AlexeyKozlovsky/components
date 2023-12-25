#include <iostream>

#include <creators/requestcreator.h>
#include <creators/requestbufferbuilder.h>
#include <managers/requestmanager.h>
#include <thread>
#include <services/responses/responseparser.h>

void testCallback(ErrorCode *error_code, Request *request);


int main(int argc, char *argv[]) {
  auto request_creator = std::make_shared<RequestCreator>();
  auto request_manager = std::make_shared<RequestManager>();

  for (int i = 0; i < 1; i++) {
    uint16_t reg_num = 1;
    uint16_t reg_count = 5;
    uint8_t slave_id = 1;
    auto request_1_callback = std::bind(&testCallback, std::placeholders::_1, std::placeholders::_2);
    auto request_1 = request_creator->createReadInputRegistersRequest(reg_num,
                                                                      reg_count,
                                                                      slave_id,
                                                                      request_1_callback);
    request_manager->addRequest(request_1);

    reg_num = 1;
    reg_count = 5;
    slave_id = 1;
    auto request_2_callback = std::bind(&testCallback, std::placeholders::_1, std::placeholders::_2);
    auto request_2 = request_creator->createReadInputRegistersRequest(reg_num,
                                                                      reg_count,
                                                                      slave_id,
                                                                      request_1_callback);
    request_manager->addRequest(request_2);

    reg_num = 1;
    reg_count = 5;
    slave_id = 1;
    auto request_3_callback = std::bind(&testCallback, std::placeholders::_1, std::placeholders::_2);
    auto request_3 = request_creator->createReadInputRegistersRequest(reg_num,
                                                                      reg_count,
                                                                      slave_id,
                                                                      request_1_callback);
    request_manager->addRequest(request_3);



    uint8_t *buffer = nullptr;
    uint16_t buffer_size;
    request_manager->getBuffer(&buffer, buffer_size);

    for (int i = 0; i < buffer_size; i++) {
      std::cout << unsigned(*(buffer + i)) << " ";
    }

    std::cout << std::endl;


    VARIANT__D tilt = std::vector<SCALAR_VARIANT__D> {
        SCALAR_VARIANT__D(1), SCALAR_VARIANT__D(2), SCALAR_VARIANT__D(3), SCALAR_VARIANT__D(4), SCALAR_VARIANT__D(4)
    };
//    request_manager->setResponsed(0, 1, tilt);
//    request_manager->setResponsed(2, 1, tilt);
//    request_manager->setResponsed(3, 1, tilt);
//    request_manager->clearAllRequests();

//    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }


  auto parser = ResponseParser::getInstance(request_manager);

  uint8_t test_buffer[] {
      0, 0, 0, 0, 0, 13, 1, 4, 4, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10
  };

  parser->parseResponse(test_buffer, 19);

  return EXIT_SUCCESS;
}


void testCallback(ErrorCode *error_code, Request *request) {
//  auto vector = std::get<std::vector<SCALAR_VARIANT__D>>(value);
//  for (auto el: vector) {
//    auto current_el = std::get<uint16_t>(el);
//    std::cout << unsigned(current_el) << " ";
//  }

  std::cout << request->getTransactionID() << " " << request->getSlaveID();
  std::cout << "\t";
  std::cout << "PAm PAM" << std::endl;
}

