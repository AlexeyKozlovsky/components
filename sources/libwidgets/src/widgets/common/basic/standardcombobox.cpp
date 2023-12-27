#include "widgets/common/basic/standardcombobox.h"

#include "widgets/consts.h"

#include <QDebug>


StandardUShortCombobox::StandardUShortCombobox(const QMap<int, QString>& states, QWidget *parent):
  QComboBox(parent), states(states), current_state(states.firstKey())  {
  initUI();
  setConnections();
}

void StandardUShortCombobox::initUI() {
  setFont(default_font);
  this->setFocusPolicy(Qt::StrongFocus);

  updateStates(states);
}

void StandardUShortCombobox::setReadOnlyMode(bool status) {
  setEnabled(!status);
}

void StandardUShortCombobox::setConnections() {
  QObject::connect(this, SIGNAL(currentIndexChanged(const QString &)),
                   this, SLOT(stateChangedSlot(const QString &)));
}

void StandardUShortCombobox::stateChangedSlot(const QString &state_text) {
  qDebug() << "Standard Combobox stateChangedSlot!::   " << state_text;
  current_state = states.key(state_text);
  emit stateChanged(current_state);
}

void StandardUShortCombobox::wheelEvent(QWheelEvent *e) { }

int StandardUShortCombobox::getState() {
  return current_state;
}

void StandardUShortCombobox::setState(int state) {
  if (states.contains(state)) {
    blockSignals(true);
    setCurrentText(states.value(state));
    current_state = state;
    blockSignals(false);
  }
}

void StandardUShortCombobox::updateStates(const QMap<int, QString> &states, int current_state) {
  blockSignals(true);
  clear();

  for (const auto& state: states) addItem(state);
  setCurrentText(states[current_state]);

  this->states = states;
  blockSignals(false);
}
