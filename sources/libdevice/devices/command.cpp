#include "command.h"

Command::Command(const std::string &name, const std::shared_ptr<Device> &device): DeviceAttribute(name, device) {

}

VARIANT__D Command::executeCommand(const VARIANT__D & value, ErrorCode *error_code) {
//  exec_mutex.lock();
  beforeExecute(error_code);
  auto result = execute(value, error_code);
  afterExecute(error_code);
//  exec_mutex.unlock();
  return result;
}

void Command::beforeExecute(ErrorCode *error_code) {

}

void Command::afterExecute(ErrorCode *error_code) {

}

void Command::poll() {

}
