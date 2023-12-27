#include "widgets/common/basic/composedtimeinput.h"

#include <cmath>
#include <QGridLayout>

#include <QDebug>

#include "widgets/consts.h"


ComposedTimeInput::ComposedTimeInput(const QString &caption,
                                     uint64_t ns_min, uint64_t ns_max,
                                     uint64_t mks_min, uint64_t mks_max,
                                     uint64_t ms_min, uint64_t ms_max,
                                     QWidget *parent,
                                     Qt::Orientation orientation) : QWidget(parent) {
  ranges.insert(Units::NS, QPair<uint64_t, uint64_t>(ns_min, ns_max));
  ranges.insert(Units::MKS, QPair<uint64_t, uint64_t>(mks_min, mks_max));
  ranges.insert(Units::MS, QPair<uint64_t, uint64_t>(ms_min, ms_max));
  initUI(caption, orientation);
}

void ComposedTimeInput::initUI(const QString &_caption, Qt::Orientation orientation) {
  auto *main_layout = new QGridLayout(this);

  this->caption = _caption;
  header_label = new StandardPropertyLabel(caption, 14, this);
  value_spinbox = new QDoubleSpinBox(this);
  unit_combobox = new QComboBox(this);

  value_spinbox->setFixedWidth(150);
  unit_combobox->addItems({"нс", "мкс", "мс"});

  value_spinbox->setFont(default_font);
  unit_combobox->setFont(default_font);

  value_spinbox->setAlignment(Qt::AlignRight);
  value_spinbox->setFixedWidth(125);
  unit_combobox->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  unit_combobox->setFocusPolicy(Qt::StrongFocus);

  if (orientation == Qt::Horizontal) {
    main_layout->addWidget(header_label, 0, 0);
    main_layout->addWidget(value_spinbox, 0, 1);
    main_layout->addWidget(unit_combobox, 0, 2);
  }
  else {
    main_layout->addWidget(header_label, 0, 0, 1, 2);
    main_layout->addWidget(value_spinbox, 1, 0);
    main_layout->addWidget(unit_combobox, 1, 1);
  }

  main_layout->setColumnStretch(0, 1);

  QObject::connect(unit_combobox, SIGNAL(currentIndexChanged(int)),
                   this, SLOT(unitChangedSlot(int)));
  QObject::connect(value_spinbox, SIGNAL(valueChanged(double)),
                   this, SLOT(valueChangedSlot(double)));

  unitChangedSlot(0);
  unit_combobox->setCurrentIndex(0);
}

void ComposedTimeInput::setReadOnlyMode(bool status) {
  value_spinbox->setEnabled(!status);
  unit_combobox->setEnabled(!status);
}

void ComposedTimeInput::unitChangedSlot(int unit_combobox_index) {
  if (unit_combobox_index >= 0 && unit_combobox_index < 3) {
    QPair<uint64_t, uint64_t> current_range = ranges[static_cast<Units>(unit_combobox_index)];
    value_spinbox->setRange(current_range.first, current_range.second);

    value_spinbox->setDecimals(unit_combobox->currentIndex() * 3);
    emit unitChanged(unit_combobox_index);
    updateValue();
  }
}

void ComposedTimeInput::updateValue() {
  value = value_spinbox->value() * pow(1000, unit_combobox->currentIndex());
  qDebug() << "value updated: " << value;
}

void ComposedTimeInput::setValueIsActual(bool status, bool force) {
  bool is_actual = status;

  if (is_actual) {
    if (!force) {
      if (hasFocus() || !_may_be_changed_by_event) return;
    }
  }

  _may_be_changed_by_event = is_actual;

  QFont font = header_label->font();
  font.setItalic(!is_actual);
  header_label->setFont(font);

  QString current_caption = caption;
  if (!is_actual) {
    current_caption += "*";
  }
  header_label->setText(current_caption);
}

void ComposedTimeInput::setValue(uint64_t new_value, bool force) {
  if (!force) {
    if (hasFocus() || !_may_be_changed_by_event) return;
  }

  value = new_value;
  if (new_value != 0) {
    auto combobox_current_index = unit_combobox->currentIndex();
    while (new_value < pow(1000, combobox_current_index) && combobox_current_index > 0 && value != 0) {
      unit_combobox->setCurrentIndex(combobox_current_index - 1);
      combobox_current_index = unit_combobox->currentIndex();
    }
  }

  double p = pow(1000, unit_combobox->currentIndex());
//  qDebug() << "Value for spinbox: " << value_for_spinbox << "; New value: " << (double) new_value << "; pow: " << p;
  value_spinbox->setValue(new_value / p);
}

void ComposedTimeInput::valueChangedSlot(double value) {
  emit valueChanged();
}

bool ComposedTimeInput::hasFocus() const {
  auto result = QWidget::hasFocus();
  if (value_spinbox != nullptr) {
    result |= value_spinbox->hasFocus();
  }

  if (unit_combobox != nullptr) {
    result |= unit_combobox->hasFocus();
//    unit_combobox->;
  }

  return result;
}
