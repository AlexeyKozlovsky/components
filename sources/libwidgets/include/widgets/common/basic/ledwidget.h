#ifndef SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_LEDWIDGET_H_
#define SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_LEDWIDGET_H_

#include <QWidget>
#include <QMap>
#include <QPen>
#include <QBrush>


/**
 * Виджет лампочки для представления булевских свойств
 */
class LedWidget: public QWidget {
  Q_OBJECT
 public:
  explicit LedWidget(QColor true_color = QColor::fromRgb(0, 176, 80),
                     QColor false_color = QColor::fromRgb(255, 0, 0),
                     QWidget *parent = nullptr);

  void setState(bool state);
  bool getState();

 public slots:
  void stateChanged(bool state);

 protected:
  // Необходимые для перерисовки поля
  QPen border_pen;
  QBrush background_brush;

  /**
   * Соответствие состояний с закрашенными цветами
   */
  QMap<bool, QColor> states;

  /**
   * Текущее состояние
   */
  bool current_state;

  void paintEvent(QPaintEvent *event) override;
};


class EditableLedWidget: public LedWidget {
  Q_OBJECT
 public:
  explicit EditableLedWidget(QColor true_color, QColor false_color, QWidget *parent = nullptr);

 protected:
  void mousePressEvent(QMouseEvent *event) override;

 signals:
  void clicked(bool state);
};

#endif //SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_LEDWIDGET_H_
