#include "property.h"

#include <thread>
#include <future>
#include <iostream>

Property::Property(const std::string &name, const std::shared_ptr<Device> &device): DeviceAttribute(name, device) {

}

VARIANT__D Property::getValue(ErrorCode *error_code) {
  return value;
}

VARIANT__D Property::readValue(ErrorCode *error_code) {
//  read_mutex.lock();
  beforeRead(error_code);
  IS_ERROR__D(error_code, return {};)
  value = read(error_code);
  IS_ERROR__D(error_code, return {};)
  afterRead(error_code);
//  read_mutex.unlock();
  return getValue(error_code);
}

void Property::writeValue(const VARIANT__D &value, ErrorCode * error_code) {
//  write_mutex.lock();
  beforeWrite(error_code);
  IS_ERROR__D(error_code, return)
  write(value, error_code);
  IS_ERROR__D(error_code, return)
//  write_mutex.unlock();
  afterWrite(error_code);
}

void Property::beforeRead(ErrorCode *error_code) {

}

void Property::afterRead(ErrorCode *error_code) {

}

void Property::beforeWrite(ErrorCode *error_code) {

}

void Property::afterWrite(ErrorCode *error_code) {

}

void Property::poll() {
  if (polling_period == 0) return;
  auto now = std::chrono::system_clock::now();
  if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_polled_time).count() >= polling_period) {
    last_polled_time = now;
    auto *error_code = new ErrorCode();
    auto result = readValue(error_code);

    // TODO: Сделать здесь асинхронный вызов коллбека, либо отправить этот вызов в третий поток
    // Пока что для отладки оставим просто вывод

    if (polling_callback != nullptr) polling_callback(result, error_code);
    std::cout << "READ from polling " << name << std::endl;
  }
}
