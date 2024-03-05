#ifndef SYNC_SYS_WIDGET_WIDGETS_COMMON_COMPOSED_DATASAVERSWIDGET_H_
#define SYNC_SYS_WIDGET_WIDGETS_COMMON_COMPOSED_DATASAVERSWIDGET_H_

#include <QWidget>

#include <QPushButton>
#include "widgets/export.h"

class WIDGETS_EXPORT DataSaverWidget: public QWidget {
  Q_OBJECT
 public:
  explicit DataSaverWidget(QWidget *parent = nullptr);

 signals:
  void saveDataToEPROMActionSignal();
  void saveDataToDBActionSignal();
  void saveNamedDataToDBActionSignal(const QString &mode_name);

 private:
  QPushButton *_save_to_eprom_button = nullptr;
  QPushButton *_save_to_db_button = nullptr;
  QPushButton *_save_named_to_db_button = nullptr;

  void initUI();
  void setConnections();

 private slots:
  void saveDataToEPROMButtonClickedBridgeSlot();
  void saveDataToDBButtonClickedBridgeSlot();
  void saveNamedDataToDBButtonClickedBridgeSlot();
};

#endif //SYNC_SYS_WIDGET_WIDGETS_COMMON_COMPOSED_DATASAVERSWIDGET_H_
