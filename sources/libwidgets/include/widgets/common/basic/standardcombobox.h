#ifndef SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_STANDARDCOMBOBOX_H_
#define SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_STANDARDCOMBOBOX_H_

#include <QComboBox>

#include "widgets/common/basic/readwritewidget.h"

#include "widgets/export.h"

class WIDGETS_EXPORT StandardUShortCombobox: public QComboBox, public ReadWriteWidget {
  Q_OBJECT
 public:
  explicit StandardUShortCombobox(const QMap<int, QString>& states, QWidget *parent = nullptr);

  int getState();
  void setState(int state);

  void updateStates(const QMap<int, QString> &states, int current_state = 0);

  void setReadOnlyMode(bool status) override;

 signals:
  void stateChanged(int state);

 protected:
  /*!
   * Переопределяем событие, чтобы во время прокрутки колёсика мыши смены индекса не происходило.
   * @param e
   */
  void wheelEvent(QWheelEvent *e) override;

 private:
  int current_state;
  QMap<int, QString> states;

  void initUI();
  void setConnections();

 private slots:
  void stateChangedSlot(const QString &state_text);
};

#endif //SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_STANDARDCOMBOBOX_H_
