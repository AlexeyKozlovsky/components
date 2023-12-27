#include "widgets/common/basic/ledwidget.h"

#include <iostream>

#include <QPainter>
#include <QDebug>


LedWidget::LedWidget(QColor true_color, QColor false_color, QWidget *parent): QWidget(parent), current_state(false) {
  states.insert(true, true_color);
  states.insert(false, false_color);

  border_pen.setColor(Qt::black);
  border_pen.setWidth(2);

  setState(current_state);

  setFixedSize(20, 20);
}


void LedWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  painter.setPen(border_pen);
  painter.setBrush(background_brush);

  const double half_border_pen_width = border_pen.width() / 2;

  QRectF rect(half_border_pen_width, half_border_pen_width,
              width() - border_pen.width(), height() - border_pen.width());
  painter.drawRect(rect);
  painter.fillRect(rect,  states[current_state]);

  QWidget::paintEvent(event);
}

void LedWidget::setState(bool state) {
  current_state = state;
  repaint();
}

bool LedWidget::getState() {
  return current_state;
}

void LedWidget::stateChanged(bool state) {
  setState(state);
  repaint();
}


EditableLedWidget::EditableLedWidget(QColor true_color, QColor false_color, QWidget *parent):
    LedWidget(true_color, false_color, parent){

}

void EditableLedWidget::mousePressEvent(QMouseEvent *event) {
  emit clicked(!current_state);
  qDebug() << "Clicked";
  QWidget::mousePressEvent(event);
}

