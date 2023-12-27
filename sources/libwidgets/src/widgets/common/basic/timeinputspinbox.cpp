#include "widgets/common/basic/timeinputspinbox.h"

#include <QValidator>

#include "widgets/enums.h"
#include "widgets/services.h"


bool TimeInputSpinBox::additionalConditionCheck(){
  double value = 0;

  // TODO: ??
  Units unit;
  getValueAndUnitUnsafe(value, unit);

  return toNano(value, unit) >= 100;
}

bool TimeInputSpinBox::getValueAndUnit(double time, Units unit) const{
  return this->validation_state == QValidator::Acceptable && getValueAndUnitUnsafe(time, unit);
}

bool TimeInputSpinBox::getValueAndUnitUnsafe(double time, Units unit) const {
  QStringList captured_text;
  bool state = this->getCapturedText(captured_text);

  time = captured_text[1].toDouble();
  unit = units_names[captured_text[3]];

  return state;
}

QRegExp TimeInputSpinBox::makeRegExp() {
  QString time_input_regexp = "([0-9]+(\\.[0-9]+)?)\\s*(";

  for (auto unit : units_names){
    time_input_regexp.append(unit.first);
    time_input_regexp.append(unit.first != (--units_names.end())->first ? "|" : "");
  }
  time_input_regexp.append(")");

  return QRegExp(time_input_regexp);
}

TimeInputSpinBox::TimeInputSpinBox(QWidget *parent): SoftValidationSpinBox(reg_exp, parent) {
  this->reg_exp = this->makeRegExp();
  this->reg_exp_validator = new QRegExpValidator(this->reg_exp, this);

  setToolTip(QString("Введите значение вида:\n"
                     "100 нс\n"
                     "52 мкс\n"
                     "123 мс"));
}

bool TimeInputSpinBox::getTimeInNano(uint64_t nano) {
  return false;
}

uint64_t TimeInputSpinBox::getTimeInNano() {
  return 0;
}


void TimeInputSpinBox::setReadOnlyMode(bool status) {
  setEnabled(!status);
}