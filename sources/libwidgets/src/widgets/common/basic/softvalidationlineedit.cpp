#include "widgets/common/basic/softvalidationlineedit.h"

#include <utility>
#include "widgets/stylesheets/default.h"


SoftValidationLineEdit::SoftValidationLineEdit(const QRegExp& reg_exp,
                                               std::function<bool()> additionalCheck,
                                               QWidget *parent) : QLineEdit(parent) {
  this->reg_exp = QRegExp(reg_exp);
  reg_exp_validator = new QRegExpValidator(reg_exp, this);
  addCheck = std::move(additionalCheck);

  initUI();
  setConnections();
}

void SoftValidationLineEdit::setConnections() {
  QObject::connect(this, &QLineEdit::textChanged,
                   this, &SoftValidationLineEdit::validate);
  QObject::connect(this, &SoftValidationLineEdit::validationStateChanged,
                   this, &SoftValidationLineEdit::changeStyleSheet);
}

void SoftValidationLineEdit::validate() {
  QString cur_text = this->text().toLower();
  int pos = 0;
  QValidator::State new_validation_state = reg_exp_validator->validate(cur_text, pos);
  this->setValidationState(new_validation_state == QValidator::Acceptable
                           && !this->addCheck()
                           ? QValidator::Invalid : new_validation_state);
}

void SoftValidationLineEdit::changeStyleSheet(QValidator::State new_validation_state) {
  this->setStyleSheet(softValidationLineEditStyles.states[new_validation_state]);
}

bool SoftValidationLineEdit::getText(QString &text) const{
  text = this->text();
  return validation_state == QValidator::Acceptable;
}

bool SoftValidationLineEdit::getCapturedText(QStringList &captured_text) const{
  captured_text.clear();
  QString text;
  this->getText(text);
  reg_exp.indexIn(text);
  captured_text.append(reg_exp.capturedTexts());
  return validation_state == QValidator::Acceptable;
}

void SoftValidationLineEdit::setValidationState(QValidator::State new_validation_state) {
  if (new_validation_state != this->validation_state) {
    this->validation_state = new_validation_state;
    emit validationStateChanged(validation_state);
  }
}

void SoftValidationLineEdit::initUI() {
  setMinimumSize(100, 25);
}
