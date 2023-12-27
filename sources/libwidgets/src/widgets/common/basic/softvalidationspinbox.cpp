#include "widgets/common/basic/softvalidationspinbox.h"
#include "widgets/stylesheets/default.h"
#include "widgets/consts.h"

#include <QLineEdit>


SoftValidationSpinBox::SoftValidationSpinBox(const QRegExp& reg_exp,
                                             QWidget *parent) : QAbstractSpinBox(parent) {
  setButtonSymbols(ButtonSymbols::PlusMinus);
  setAlignment(Qt::AlignRight);
  this->reg_exp = QRegExp(reg_exp);
  reg_exp_validator = new QRegExpValidator(reg_exp, this);

  setConnections();
  initUI();
}

void SoftValidationSpinBox::setConnections() {
  QObject::connect(this->lineEdit(), &QLineEdit::textChanged,
                   this, &SoftValidationSpinBox::validate);
  QObject::connect(this, &SoftValidationSpinBox::validationStateChanged,
                   this, &SoftValidationSpinBox::changeStyleSheet);
}

void SoftValidationSpinBox::validate() {
  QString cur_text = this->lineEdit()->text().toLower();
  int pos = 0;
  QValidator::State new_validation_state = reg_exp_validator->validate(cur_text, pos);
  setValidationState(new_validation_state == QValidator::Acceptable
                               && !additionalConditionCheck()
                           ? QValidator::Invalid : new_validation_state);
}

void SoftValidationSpinBox::changeStyleSheet(QValidator::State new_validation_state) {
  lineEdit()->setStyleSheet(softValidationLineEditStyles.states[new_validation_state]);
}

bool SoftValidationSpinBox::getText(QString &text) const{
  text = lineEdit()->text();
  return validation_state == QValidator::Acceptable;
}

void SoftValidationSpinBox::setText(const QString &text) {
  lineEdit()->setText(text);
}

bool SoftValidationSpinBox::getCapturedText(QStringList &captured_text) const{
  captured_text.clear();
  QString text;
  getText(text);
  reg_exp.indexIn(text);
  captured_text.append(reg_exp.capturedTexts());
  return validation_state == QValidator::Acceptable;
}

void SoftValidationSpinBox::setValidationState(QValidator::State new_validation_state) {
  if (new_validation_state != validation_state) {
    validation_state = new_validation_state;
    emit validationStateChanged(validation_state);
  }
}

QValidator::State SoftValidationSpinBox::getValidationState() const {
  return validation_state;
}

void SoftValidationSpinBox::initUI() {
  setFont(default_font);
  setMinimumSize(100, 25);
}
