#include "property.h"

#include <thread>
#include <future>
#include <iostream>

Property::Property(const std::string &name): DeviceAttribute(name) {

}

VARIANT Property::getValue(ErrorCode *error_code) {
  return value;
}

VARIANT Property::readValue(ErrorCode *error_code) {
  beforeRead(error_code);
  value = read(error_code);
  afterRead(error_code);
  return getValue(error_code);
}

void Property::writeValue(const VARIANT &value, ErrorCode * error_code) {
  beforeWrite(error_code);
  write(value, error_code);
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
  auto now = std::chrono::system_clock::now();
  if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_polled_time).count() >= polling_period) {
    last_polled_time = now;
    auto *error_code = new ErrorCode();
    auto result = readValue(error_code);

    // TODO: Сделать здесь асинхронный вызов коллбека, либо отправить этот вызов в третий поток
    // Пока что для отладки оставим просто вывод

    std::cout << "READ from polling " << name << std::endl;
  }
}
