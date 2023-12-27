#include "widgets/common/composed/fullcomposedlineedit.h"

#include "widgets/consts.h"
#include "widgets/common/basic/standardbutton.h"
#include "widgets/common/basic/standardlineedit.h"

#include <QGridLayout>


FullComposedLineEdit::FullComposedLineEdit(const QString &caption,
                                           QWidget *parent,
                                           Qt::Orientation orientation) : QGroupBox(parent) {
  initUI(caption, orientation);
  setConnections();
}

void FullComposedLineEdit::initUI(const QString &caption, Qt::Orientation orientation) {
  setTitle(caption);
  setFont(default_font);
  auto *main_layout = new QGridLayout(this);

  input_ledit = new StandardLineEdit(this);
  input_ledit->setAlignment(Qt::AlignLeft);

  read_button = new StandardButton("Прочитать", this);
  write_button = new StandardButton("Записать", this);

  if (orientation == Qt::Vertical) {
    main_layout->addWidget(input_ledit, 0, 0, 1, 2);
    main_layout->addWidget(read_button, 1, 0);
    main_layout->addWidget(write_button, 1, 1);
  }
  else {
    main_layout->addWidget(input_ledit, 0, 0, 1, 3);
    main_layout->addWidget(read_button, 1, 1);
    main_layout->addWidget(write_button, 1, 2);
  }
}

void FullComposedLineEdit::setConnections() {
  QObject::connect(read_button, &QAbstractButton::released,
                   this, &FullComposedLineEdit::getValueActionSignal);
  QObject::connect(write_button, &QAbstractButton::released,
                   this, &FullComposedLineEdit::valueChangedProxySlot);
}

void FullComposedLineEdit::valueChangedProxySlot() {
  emit valueChangedSignal(getValue());
}

void FullComposedLineEdit::setValue(const QString &text) {
  input_ledit->setText(text);
}

QString FullComposedLineEdit::getValue() {
  return input_ledit->text();
}


void FullComposedLineEdit::setReadOnlyMode(bool status) {
  input_ledit->setReadOnlyMode(status);
}