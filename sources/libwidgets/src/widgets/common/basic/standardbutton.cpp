#include "widgets/common/basic/standardbutton.h"

#include <QPainter>

#include "widgets/consts.h"


StandardButton::StandardButton(const QString& caption, QWidget *parent):
  QPushButton(caption, parent){
  initUI();
}

void StandardButton::initUI() {
  setFont(default_font);
}

void StandardButton::setReadOnlyMode(bool status) {
  setEnabled(!status);
}

void StandardButton::paintEvent(QPaintEvent *event) {
  QPushButton::paintEvent(event);
}

