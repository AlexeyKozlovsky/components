#include <iostream>
#include <memory>

#include <utils/services/uidgeneratorimpls/boost/uidgeneratorboostimpl.h>

int main(int argc, char *argv[]) {
  auto uid_generator = std::make_shared<UIDGeneratorBoostImpl>();
  auto uid_string = uid_generator->generateUIDString();

  std::cout << uid_string << std::endl;
  return 0;
}