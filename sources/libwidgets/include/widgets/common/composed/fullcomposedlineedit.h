#ifndef SYNC_SYS_DEVICE_WIDGET_WIDGETS_COMMON_COMPOSED_FULLCOMPOSEDLINEEDIT_H_
#define SYNC_SYS_DEVICE_WIDGET_WIDGETS_COMMON_COMPOSED_FULLCOMPOSEDLINEEDIT_H_

#include <QGroupBox>

#include "widgets/common/basic/readwritewidget.h"
#include "widgets/export.h"

class StandardLineEdit;
class StandardButton;


class WIDGETS_EXPORT FullComposedLineEdit : public QGroupBox, public ReadWriteWidget {
  Q_OBJECT
 public:
  explicit FullComposedLineEdit(const QString &caption,
                                QWidget *parent = nullptr,
                                Qt::Orientation orientation = Qt::Vertical);

  void setValue(const QString &text);
  QString getValue();

  void setReadOnlyMode(bool status) override;

 signals:
  void getValueActionSignal();
  void valueChangedSignal(const QString &name);

 private:
  StandardLineEdit *input_ledit;
  StandardButton *read_button;
  StandardButton *write_button;

  void initUI(const QString &caption, Qt::Orientation orientation);
  void setConnections();

 private slots:
  void valueChangedProxySlot();
};

#endif //SYNC_SYS_DEVICE_WIDGET_WIDGETS_COMMON_COMPOSED_FULLCOMPOSEDLINEEDIT_H_
