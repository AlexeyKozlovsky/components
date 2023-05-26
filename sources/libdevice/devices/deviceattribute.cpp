#include "deviceattribute.h"


DeviceAttribute::DeviceAttribute(const std::string &name, const std::shared_ptr<Device> &device)
  : name(name), device(device) {

}

void DeviceAttribute::setPollingCallback(const std::function<void(VARIANT__D&, ErrorCode*)> &callback) {
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
