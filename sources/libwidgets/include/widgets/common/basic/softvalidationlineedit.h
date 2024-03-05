#ifndef SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_SOFTVALIDATIONLINEEDIT_H_
#define SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_SOFTVALIDATIONLINEEDIT_H_

#include <QLineEdit>
#include <QRegExpValidator>
#include <functional>
#include "widgets/export.h"

class WIDGETS_EXPORT SoftValidationLineEdit : public QLineEdit {
  Q_OBJECT
 public:
  /*!
   * Конструктор класса.
   * @param reg_exp регулярное выражение;
   * @param parent родительский виджет.
   */
  explicit SoftValidationLineEdit(const QRegExp& reg_exp,
                                  std::function<bool()> additionalCheck = []() { return true; },
                                  QWidget *parent = nullptr);
  /*!
   * Функция возвращает текст, введённый в поле.
   * @param text параметр, в который осуществится запись текста из поля;
   * @return true - текст прошёл валидацию;\n
   * false - текст не прошёл валидацию.
   */
  bool getText(QString &text) const;
  /*!
   * Функция возвращает список подстрок, вохдящих во введённый текст. Возвращает пустые строки, если валидация
   * не пройдена.
   * @param captured_text Параметр, в который будут записаны подстроки.
   * @return true - текст прошёл валидацию;\n
   * false - текст не прошёл валидацию.
   */
  bool getCapturedText(QStringList &captured_text) const;

 signals:
  /*!
   * Сигнал, испускаемый в случае изменения состояния валидации.
   * @param new_validation_state Новое состояние валидации.
   */
  void validationStateChanged(QValidator::State new_validation_state) const;

 protected:
  /*!
   * Регулярное выражение, по которому проводится валидация.
   */
  QRegExp reg_exp;
  /*!
   * Валидатор, который использует указанное выше регулярное выражение.
   */
  QRegExpValidator *reg_exp_validator;

  /*!
   * Текущее остояние валидатора:\n
   * QValidator::Invalid = 0;\n
   * QValidator::Intermediate = 1;\n
   * QValidator::Acceptable = 2.
   */
  QValidator::State validation_state = QValidator::Invalid;

  /*!
 * Сеттер для поля validation_state.
 * @param new_validation_state новое значение состояния валидации.
 */
  void setValidationState(QValidator::State new_validation_state);

 protected slots:
  /*!
   * Функция проводит валидацию введённого значения каждый раз, когда текст в поле изменяется.
   * В случае, если состояние проверки изменилось, то результат записывается в переменную и испускается сигнал.
   */
  void validate();
  /*!
   * Функция меняет цвет фона в зависимости от состояния валидации.
   * @param new_validation_state Новое состояние валидации.
   */
  void changeStyleSheet(QValidator::State new_validation_state);

 private:
  std::function<bool()> addCheck;

  void initUI();
  void setConnections();
};

#endif //SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_SOFTVALIDATIONLINEEDIT_H_
