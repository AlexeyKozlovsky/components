#include "deviceattribute.h"

DeviceAttribute::DeviceAttribute(const std::string &name): name(name) {

}

void DeviceAttribute::setPollingCallback(const std::function<void(VARIANT&, ErrorCode*)> &callback) {
  polling_callback = callback;
}

void DeviceAttribute::setPollingPeriod(int polling, ErrorCode *error_code) {
  if (polling < 0) {
    *error_code = ErrorCode::INVALID_REQUEST;
    return;
  }

  polling_period = polling;
  *error_code = ErrorCode::SUCCESS;
}
