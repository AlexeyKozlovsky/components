#ifndef SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_SOFTVALIDATIONSPINBOX_H_
#define SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_SOFTVALIDATIONSPINBOX_H_

#include <QAbstractSpinBox>
#include "widgets/export.h"


/*!
 * Класс предоставляет спинбокс, в который можно вводить любой текст.
 * Класс имеет собственную валидацию, которая не препятствует изменению введённого значений.
 * В соответствии с состоянием валидации у поля меняется цвет.
 * Так же имеется возможность проверки дополнительных условий помимо валидации.
 */
class WIDGETS_EXPORT SoftValidationSpinBox : public QAbstractSpinBox {
  Q_OBJECT
 public:
  /*!
   * Конструктор класса.
   * @param reg_exp регулярное выражение;
   * @param parent родительский виджет.
   */
  explicit SoftValidationSpinBox(const QRegExp& reg_exp, QWidget *parent = nullptr);
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
  QValidator::State getValidationState() const;

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
   * Валидация проводится по заранее заданному регулярному выражению. В случае, если необходимо рассмотреть
   * дополнительные условия, то необходимо переопределить данную функцию и описать эти условия в ней.
   * @return true - условия соблюдены;\n
   *         false - условия не соблюдены.
   */
  virtual bool additionalConditionCheck() { return true; };

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
  void initUI();
  void setConnections();
};

#endif //OU_1U_WIDGETS_BASIC_SOFTVALIDATIONSPINBOX_H_
