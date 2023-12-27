#include "widgets/common/basic/standardlineedit.h"

#include "widgets/consts.h"


StandardLineEdit::StandardLineEdit(QWidget *parent): QLineEdit(parent) {
  initUI();
}

void StandardLineEdit::initUI() {
  setFont(default_font);
  setAlignment(Qt::AlignRight);
}

void StandardLineEdit::setReadOnlyMode(bool status) {
  setEnabled(!status);
}