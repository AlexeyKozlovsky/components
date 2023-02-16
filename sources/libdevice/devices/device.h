#ifndef DIALTEK_LIBDEVICE_DEVICES_DEVICE_H_
#define DIALTEK_LIBDEVICE_DEVICES_DEVICE_H_

#include <variant>
#include <string>
#include <set>
#include <memory>
#include <map>

#include "macros.h"
#include "enums.h"
#include "devices/property.h"
#include "devices/command.h"

using device::ErrorCode;
using device::DeviceState;

template <typename T>
struct IndexedAttrs {
  std::map<std::string, std::shared_ptr<T>> indexed_values;
  bool is_actual = false;
};


/**
 * Класс девайса, через который идет вся работа.
 * Аналог Tango девайса, но гораздо более упрощенный.
 */
class Device {
 public:
  Device(const Device &dev);
  ~Device() = default;

  void setName(const std::string &name);
  void setAlias(const std::string &alias);
  void setDescription(const std::string &description);

  inline const std::string &getName() const {
    return name;
  }

  const std::string &getAlias() const {
    return alias;
  }

  const std::string &getDescription() const {
    return description;
  }

  const DeviceState getState() const {
    return state;
  }

  void addProperty(std::shared_ptr<Property> property, ErrorCode *error_code = nullptr);
  void addCommand(std::shared_ptr<Command> commands, ErrorCode *error_code = nullptr);

  void setAvailableStates(const std::set<DeviceState> &states);

  void changeState(DeviceState state, ErrorCode *error_code = nullptr);

  std::shared_ptr<Property> getPropertyByName(const std::string &name, ErrorCode *error_code = nullptr);
  std::shared_ptr<Command> getCommandByName(const std::string &name, ErrorCode *error_code = nullptr);
  std::set<std::shared_ptr<DeviceAttribute>> getPollingAttributes();

  VARIANT readProperty(const std::string &property_name, ErrorCode *error_code = nullptr);
  VARIANT writeProperty(const std::string &property_name, const VARIANT &value, ErrorCode *error_code = nullptr);
  VARIANT executeCommand(const std::string &command_name, const VARIANT &argin, ErrorCode *error_code = nullptr);

 protected:
  /**
   * Условное имя девайса, которое должно быть уникально.
   * Девайсы не должны создаться самостоятельно.
   * Любое создание девайсов должно идти через фабрику-конфиг.
   * В пределах этого объекта конфига данное имя должно быть уникально.
   * К девайсу можно будет обратиться как по указателю
   * (непосредственно как к объекту), так и по имени
   * (по сути, получить по имени указатель на девайс и работать с ним)
   */
  std::string name;

  /**
   * Псевдоним девайса. Замена имени в более упрощенном варианте.
   * Это по сути user-friendly имя, которое будет отображяться.
   * Может быть и не уникальным
   */
  std::string alias;
  std::string description;
  std::set<std::shared_ptr<Property>> properties;
  std::set<std::shared_ptr<Command>> commands;
  std::set<DeviceState> available_states;

  /**
   * Текущее состояние девайса. Будет влиять на работу со свойствами
   */
  DeviceState state;

  IndexedAttrs<Property> indexed_properties;
  IndexedAttrs<Command> indexed_commands;

  Device();
  Device(const std::string &name);

  /**
   * Метод для того, чтобы проиндексировать все свойства и команды.
   * Т.е. заполнить кэш в виде std::map, где ключ -- имя команды или свойства,
   * а значение -- указатель на команду или свойство
   */
  void index();
};

#endif //DIALTEK_LIBDEVICE_DEVICES_DEVICE_H_
