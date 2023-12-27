#include "widgets/common/basic/lampwidget.h"

LampWidget::LampWidget(QWidget *parent) : QWidget(parent) {
  initUI();
  setState(LAMP_OFF);
}

void LampWidget::setState(LampStates new_state) {
  this->state = new_state;
  this->setNewStyleSheet();
}

void LampWidget::setState(bool new_state) {
  state = new_state ? LAMP_GOOD : LAMP_BAD;
  setState(state);
}


LampStates LampWidget::getState() const {
  return state;
}
void LampWidget::setNewStyleSheet() {
  this->setStyleSheet(lampWidgetStyles[state]);
}

void LampWidget::initUI() {
  setStyleSheet("background-color: green; border: 1px solid black;");
  setFixedSize(20, 20);
}
