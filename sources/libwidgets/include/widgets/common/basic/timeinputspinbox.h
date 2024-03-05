#ifndef SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_TIMEINPUTSPINBOX_H_
#define SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_TIMEINPUTSPINBOX_H_

#include "widgets/enums.h"
#include "widgets/common/basic/softvalidationspinbox.h"


#include "widgets/common/basic/readwritewidget.h"
#include "widgets/export.h"

/*!
 * Класс отвечает за поле ввода длины или задержки
 */
class WIDGETS_EXPORT TimeInputSpinBox : public SoftValidationSpinBox, public ReadWriteWidget {
  Q_OBJECT
 public:
  explicit TimeInputSpinBox(QWidget *parent = nullptr);
  /*!
 * Функция возвращает значение и единицу измерения.
 * @param time введённое в spinbox число;
 * @param unit введённые единицы измерения.
 * @return true - валидация пройдена успешно;\n
 *        false - валидация не пройдена.
 */
  bool getValueAndUnit(double time, Units unit) const;
  /*!
   * Функция возвращает введённое пользователем время в наносекундах.
   * @param nano наносекунды;
   * @return пройдена валидация, или нет.
   */
  bool getTimeInNano(uint64_t nano);

  /**
   * @return Возвращает время в наносекундах
   */
  uint64_t getTimeInNano();

  void setReadOnlyMode(bool status) override;

 protected:
  bool additionalConditionCheck() override;
  /*!
   * Функция для внутреннего применения. Возвращает значение и единицу измерения независимо от валидации.
   * Может произойти ошибка на конвертации пустой строки в число.
   * @param time введённое в spinbox число;
   * @param unit введённые единицы измерения.
   * @return true - валидация пройдена успешно;\n
   *        false - валидация не пройдена.
   */
  bool getValueAndUnitUnsafe(double time, Units unit) const;

 private:
  /*!
   * Функция собирает строку для регулярного выражение с учётом существующих единиц (из файла enums.h).
   * @return готовое регулярное выражение.
   */
  static QRegExp makeRegExp();

};

#endif //SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_TIMEINPUTSPINBOX_H_
