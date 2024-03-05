#ifndef SYNCSYS_DEVICE_WIDGET_WIDGETS_EPSS_COMPOSED_FULLCOMPOSEDTIMEINPUT_H_
#define SYNCSYS_DEVICE_WIDGET_WIDGETS_EPSS_COMPOSED_FULLCOMPOSEDTIMEINPUT_H_

#include <QWidget>
#include <QLabel>

#include "widgets/common/basic/readwritewidget.h"
#include "widgets/export.h"

class ComposedTimeInput;
class QLabel;


class WIDGETS_EXPORT FullComposedTimeInput: public QWidget, public ReadWriteWidget {
  Q_OBJECT
 public:
  explicit FullComposedTimeInput(const QString &caption,
                                 uint64_t ns_min, uint64_t ns_max,
                                 uint64_t mks_min, uint64_t mks_max,
                                 uint64_t ms_min, uint64_t ms_max,
                                 QWidget *parent = nullptr,
                                 Qt::Orientation orientation = Qt::Vertical);

  inline ComposedTimeInput *timeInput() {
    return time_input;
  }

  uint64_t getValue() const;
  void setValue(uint64_t value);

  void setStatusLabel(bool status);

  void setReadOnlyMode(bool status) override;

 signals:
  void readButtonClicked();
  void writeButtonClicked(uint64_t value);

 private:
  QLabel *status_label = nullptr;
  ComposedTimeInput *time_input = nullptr;

  bool _may_be_changed_by_event = true;

  void initUI(const QString &caption,
              uint64_t ns_min, uint64_t ns_max,
              uint64_t mks_min, uint64_t mks_max,
              uint64_t ms_min, uint64_t ms_max,
              Qt::Orientation orientation);

 private slots:
  void valueChangedSlot();
  void unitChangedSlot(int current_index);

  void readButtonBridgeSlot();
  void writeButtonClickedBridgeSlot();
};

#endif //SYNCSYS_DEVICE_WIDGET_WIDGETS_EPSS_COMPOSED_FULLCOMPOSEDTIMEINPUT_H_
