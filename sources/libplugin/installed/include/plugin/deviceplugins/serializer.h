#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_SERIALIZER_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_SERIALIZER_H_

#include <string>
#include <memory>
#include <utils/baseutils.h>

/**
 * Задумывается, что он будет хранить указатель на конкретную сущность девайса и оттуда уже брать DTO
 */
class PluginSerializer {
 public:
  virtual std::string serialize() = 0;

  /**
   * Сразу сериализовывает данные в DTO девайса
   * @return
   */
  virtual ErrorCode deserialize(const std::string &data) = 0;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_SERIALIZER_H_
