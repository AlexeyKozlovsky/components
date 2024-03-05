#ifndef SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_SOFTVALIDATIONSPINBOX2_H_
#define SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_SOFTVALIDATIONSPINBOX2_H_

#include <QAbstractSpinBox>

#include "widgets/export.h"

class SoftValidationLineEdit;


class WIDGETS_EXPORT SoftValidationSpinBox2 : public QAbstractSpinBox{
  Q_OBJECT
  friend SoftValidationLineEdit;
 public:
  /*!
 * Конструктор класса.
 * @param reg_exp регулярное выражение;
 * @param parent родительский виджет.
 */
  explicit SoftValidationSpinBox2(const QRegExp& reg_exp,
                                  std::function<bool()> additionalCheck = []() -> bool { return true; },
                                  QWidget *parent = nullptr);
  /*!
   * Функция возвращает текст, введённый в поле.
   * @param text параметр, в который осуществится запись текста из поля;
   * @return true - текст прошёл валидацию;\n
   * false - текст не прошёл валидацию.
   */
  bool getText(QString &text) const;
  /*!
   * Функция устанавливает текст в поле.
   * @param text новый текст.
   */
  void setText(const QString &text);
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
  SoftValidationLineEdit *line_edit_;
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
   * Валидация проводится по заранее заданному регулярному выражению. В случае, если необходимо рассмотреть
   * дополнительные условия, то необходимо переопределить данную функцию и описать эти условия в ней.
   * @return true - условия соблюдены;\n
   *         false - условия не соблюдены.
   */
  virtual bool additionalConditionCheck() { return true; };

 private:
  void initUI(std::function<bool()> additionalCheck);
};

#endif //OU_1U_WIDGETS_BASIC_SOFTVALIDATIONSPINBOX2_H_
