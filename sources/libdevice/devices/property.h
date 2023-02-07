#ifndef DIALTEK_LIBDEVICE_DEVICES_PROPERTY_H_
#define DIALTEK_LIBDEVICE_DEVICES_PROPERTY_H_

#include <string>
#include <vector>

#include "macros.h"
#include "enums.h"

#include "devices/deviceattribute.h"

using device::DeviceState;
using device::ErrorCode;

/**
 * Класс, наследники которого будут характеризовывать атрибуты
 * и свойства девайса (если говорить в терминах танго).
 * По сути реализовывает расширенный паттерн команда.
 * Вместо одного метода execute, содержит
 * методы readValue и writeValue, которые,
 * по сути являются главными методами для клиента,
 * работающего с классом. Это базовый абстрактный класс,
 * для того, чтобы его использовать,
 * надо создать свой класс (каждое свойство или атрибут -- новый класс),
 * унаследовав его от данного и определить необходимые методы
 */
class Property: public DeviceAttribute {
 public:

  /**
   * Этот метод позволяет получить значение свойство,
   * которое сейчас ХРАНИТСЯ в объекте свйоства.
   * Никакого чтения не происходит (т.е. метод readValue не вызывается).
   * По сути, с помощью данного метода мы получаем закешированное
   * значение свойства. Если свойство ещё ни разу
   * не читалось (т.е. не вызывался метод readValue),
   * то getValue вернет значение "по умолчанию".
   * @param error_code -- код ошибки, при работе данного метода
   * @return закешированное значение свойства
   */
  VARIANT getValue(ErrorCode *error_code = nullptr);

  /**
   * Основной метод для переопределения.
   * Через него происходит чтение свойства.
   * Несмотря на публичный статус метода,
   * работа со свойствами протекает ИСКЛЮЧИТЕЛЬНО
   * через девайс. Тем не менее, именно в этом методе
   * реализовывается основная низкоуровневая логика,
   * связанная с чтением. Это может быть обращение к БД или
   * отправка запроса мобдас.
   * @param error_code -- код ошибки, при работе данного метода
   * @return прочитанное значение свойства
   */
  VARIANT readValue(ErrorCode *error_code = nullptr);

  /**
   * Аналогично предыдущему методу, но в данном случае речь про запись
   * @param value значение, которое необходимо записать
   * @param error_code код ошибки, при работе данного метода
   */
  void writeValue(const VARIANT &value, ErrorCode *error_code = nullptr);

  void poll() override;

 protected:
  /**
   * Само значение свойства. Хранится последний прочитанный вариант.
   * Именно это свойство возвращается в методе getValue.
   * В методе же readValue, перед возвращением свойства оно актуализируется
   */
  VARIANT value;

  Property(const std::string &name);

  /**
   * Оберточный метод для чтения свойства. Всегда срабатывает перед чтением.
   * @param error_code код ошибки, при работе данного метода
   */
  virtual void beforeRead(ErrorCode *error_code = nullptr);

  /**
   * Метод для определения логики чтения свойства
   * @param error_code код ошибки, при работе данного метода
   * @return прочитанное значение свойства
   */
  virtual VARIANT read(ErrorCode *error_code = nullptr) = 0;

  /**
   * Оберточный метод для чтения. Всегда срабатывает после чтения
   * @param error_code код ошибки, при работе данного метода
   */
  virtual void afterRead(ErrorCode *error_code = nullptr);

  /**
   * Оберточный метод для записи. Всегда срабатывает перед записью
   * @param error_code код ошибки, при работе данного метода
   */
  virtual void beforeWrite(ErrorCode *error_code = nullptr);

  /**
   * Метод для определения логики записи свойства
   * @param value значение, которое необходимо записать
   * @param error_code код ошибки, при работе данного метода
   */
  virtual void write(const VARIANT &value, ErrorCode *error_code = nullptr) = 0;

  /**
   * Оберточный метод для записи. Всегда срабатывает после записи
   * @param error_code код ошибки, при работе данного метода
   */
  virtual void afterWrite(ErrorCode *error_code = nullptr);
};

#endif //LIBMODBUS_DEVICES_PROPERTY_H_
