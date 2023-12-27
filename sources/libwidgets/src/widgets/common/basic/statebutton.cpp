#include "widgets/common/basic/statebutton.h"

#include <utility>


StateButton::StateButton(const QString &button_true_state_caption,
                         QColor button_true_state_color,
                         const QString &button_false_state_caption,
                         QColor button_false_state_color,
                         QWidget *parent): QPushButton(parent) {
  button_states.insert(true, {button_true_state_caption, std::move(button_true_state_color)});
  button_states.insert(false, {button_false_state_caption, std::move(button_false_state_color)});
  initUI();
  setState(false);
}

void StateButton::initUI() {
  setFlat(true);
  setFont(QFont("Segoe UI", 14));

  QObject::connect(this, &StateButton::released,
                   this, &StateButton::releasedSlot);
}

void StateButton::setReadOnlyMode(bool status) {
  setEnabled(!status);
}

void StateButton::releasedSlot() {
  emit stateChanged(!current_state);
}
