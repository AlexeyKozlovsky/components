#include "widgets/common/basic/softvalidationspinbox2.h"

#include <utility>

#include "widgets/stylesheets/default.h"
#include "widgets/common/basic/softvalidationlineedit.h"


SoftValidationSpinBox2::SoftValidationSpinBox2(const QRegExp& reg_exp,
                                               std::function<bool()> additionalCheck,
                                               QWidget *parent) : QAbstractSpinBox(parent) {

  initUI(std::move(additionalCheck));

  this->reg_exp = QRegExp(reg_exp);
  reg_exp_validator = new QRegExpValidator(reg_exp, this);
}

bool SoftValidationSpinBox2::getText(QString &text) const{
  return this->line_edit_->getText(text);
}

void SoftValidationSpinBox2::setText(const QString &text) {
  this->line_edit_->setText(text);
}

bool SoftValidationSpinBox2::getCapturedText(QStringList &captured_text) const{
  return this->line_edit_->getCapturedText(captured_text);
}

void SoftValidationSpinBox2::initUI(std::function<bool()> additionalCheck) {
  this->setButtonSymbols(ButtonSymbols::PlusMinus);
  this->setMinimumSize(100, 25);

  line_edit_ = new SoftValidationLineEdit(reg_exp, std::move(additionalCheck), this);
  this->setLineEdit(line_edit_);

  QObject::connect(line_edit_, &SoftValidationLineEdit::validationStateChanged,
                   this, &SoftValidationSpinBox2::validationStateChanged);
}
