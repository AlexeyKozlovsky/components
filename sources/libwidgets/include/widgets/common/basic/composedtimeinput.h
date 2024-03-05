#ifndef SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_COMPOSEDTIMEINPUT_H_
#define SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_COMPOSEDTIMEINPUT_H_

#include <QWidget>
#include <QSpinBox>
#include <QComboBox>

#include "widgets/enums.h"

#include "standardpropertylabel.h"
#include "readwritewidget.h"
#include "widgets/export.h"

class WIDGETS_EXPORT ComposedTimeInput: public QWidget, public ReadWriteWidget {
  Q_OBJECT
 public:
  explicit ComposedTimeInput(const QString &caption,
                             uint64_t ns_min, uint64_t ns_max,
                             uint64_t mks_min, uint64_t mks_max,
                             uint64_t ms_min, uint64_t ms_max,
                             QWidget *parent = nullptr,
                             Qt::Orientation orientation = Qt::Horizontal);

  inline uint64_t getValue() {
    updateValue();
    return value;
  }

  /**
 * Присваивает значение в тех единицах, которые указаны в данный момент (если значение можно представить в целых числах)
 * @param value -- значение в наносекундах
 */
  void setValue(uint64_t value, bool force = false);
  void setValueIsActual(bool status, bool force = false);

  void setReadOnlyMode(bool status) override;

  bool hasFocus() const;

 signals:
  void valueChanged();
  void unitChanged(int current_index);


 private:
  QMap<Units, QPair<uint64_t, uint64_t>> ranges;

  uint64_t value;
  Units unit;

  QDoubleSpinBox *value_spinbox;
  QComboBox *unit_combobox;

  QString caption;
  StandardPropertyLabel *header_label;

  bool _may_be_changed_by_event = true;

  void initUI(const QString &caption, Qt::Orientation orientation);

  /**
   * Метод для актуализации value с тем, что в spinbox
   */
  void updateValue();

 private slots:
  void valueChangedSlot(double value);
  void unitChangedSlot(int unit_combobox_index);
};

#endif //SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_COMPOSEDTIMEINPUT_H_
