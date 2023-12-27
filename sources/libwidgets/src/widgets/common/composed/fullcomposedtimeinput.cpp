#include "widgets/common/composed/fullcomposedtimeinput.h"

#include <QGridLayout>
#include <QDebug>

#include "widgets/common/basic/standardbutton.h"
#include "widgets/consts.h"
#include "widgets/common/basic/composedtimeinput.h"


FullComposedTimeInput::FullComposedTimeInput(const QString &caption,
                                             uint64_t ns_min, uint64_t ns_max,
                                             uint64_t mks_min, uint64_t mks_max,
                                             uint64_t ms_min, uint64_t ms_max,
                                             QWidget *parent,
                                             Qt::Orientation orientation) : QWidget(parent) {
  initUI(caption, ns_min, ns_max, mks_min, mks_max, ms_min, ms_max, orientation);
}

void FullComposedTimeInput::initUI(const QString &caption,
                                   uint64_t ns_min, uint64_t ns_max,
                                   uint64_t mks_min, uint64_t mks_max,
                                   uint64_t ms_min, uint64_t ms_max,
                                   Qt::Orientation orientation) {
  auto *main_layout = new QGridLayout(this);
  main_layout->setAlignment(Qt::AlignLeft);

  time_input = new ComposedTimeInput(caption, ns_min, ns_max, mks_min, mks_max, ms_min, ms_max,
                                     this, orientation);
  auto *read_button = new StandardButton(tr("Прочитать"), this);
  auto *write_button = new StandardButton(tr("Записать"), this);

  read_button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  write_button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

  time_input->layout()->setSizeConstraint(QLayout::SetMaximumSize);
  time_input->layout()->setContentsMargins(0, 0, 0, 0);

  if (orientation == Qt::Horizontal) {
    main_layout->addWidget(time_input, 0, 0, 1, 3);
    main_layout->addWidget(read_button, 1, 1);
    main_layout->addWidget(write_button, 1, 2);
  }
  else {
    main_layout->addWidget(time_input, 0, 0, 1, 2);
    main_layout->addWidget(read_button, 1, 0);
    main_layout->addWidget(write_button, 1, 1);
  }

  main_layout->setSizeConstraint(QLayout::SetMaximumSize);

  QObject::connect(read_button, &StandardButton::released,
                   this, &FullComposedTimeInput::readButtonBridgeSlot);
  QObject::connect(write_button, &StandardButton::released,
                   this, &FullComposedTimeInput::writeButtonClickedBridgeSlot);

  QObject::connect(time_input, &ComposedTimeInput::unitChanged,
                   this, &FullComposedTimeInput::unitChangedSlot);
  QObject::connect(time_input, &ComposedTimeInput::valueChanged,
                   this, &FullComposedTimeInput::valueChangedSlot);
}

void FullComposedTimeInput::setReadOnlyMode(bool status) {
  time_input->setReadOnlyMode(status);
}

void FullComposedTimeInput::valueChangedSlot() {
  time_input->setValueIsActual(false);
}

void FullComposedTimeInput::unitChangedSlot(int current_index) {
  time_input->setValueIsActual(false);
}

void FullComposedTimeInput::readButtonBridgeSlot() {
  _may_be_changed_by_event = true;
  emit readButtonClicked();
}

void FullComposedTimeInput::writeButtonClickedBridgeSlot() {
  _may_be_changed_by_event = true;
  emit writeButtonClicked(time_input->getValue());
}

void FullComposedTimeInput::setStatusLabel(bool status) {
//  status_label->setVisible(status);
//  time_input->setValueIsActual(!status);
}

uint64_t FullComposedTimeInput::getValue() const {
  return time_input->getValue();
}

void FullComposedTimeInput::setValue(uint64_t value) {
  if (time_input != nullptr) {
    time_input->blockSignals(true);
    time_input->setValue(value, _may_be_changed_by_event);
    time_input->blockSignals(false);
//  setStatusLabel(false);

    time_input->setValueIsActual(true, _may_be_changed_by_event);
    _may_be_changed_by_event = false;
//    qDebug() << "time input value: " << __func__;
  }
}

