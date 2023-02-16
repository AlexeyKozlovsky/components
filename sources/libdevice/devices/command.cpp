#include "command.h"

Command::Command(const std::string &name, const std::shared_ptr<Device> &device): DeviceAttribute(name, device) {

}

VARIANT Command::executeCommand(const VARIANT & value, ErrorCode *error_code) {
  beforeExecute(error_code);
  auto result = execute(value, error_code);
  afterExecute(error_code);
  return result;
}

void Command::beforeExecute(ErrorCode *error_code) {

}

void Command::afterExecute(ErrorCode *error_code) {

}

void Command::poll() {

}
