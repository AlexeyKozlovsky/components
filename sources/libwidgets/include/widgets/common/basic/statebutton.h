#ifndef SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_STATEBUTTON_H_
#define SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_STATEBUTTON_H_

#include <QPushButton>
#include <QMap>

#include "widgets/common/basic/readwritewidget.h"

#include <QDebug>
#include "widgets/export.h"

struct ButtonState {
  QString button_caption;
  QColor button_color;
};

class WIDGETS_EXPORT StateButton: public QPushButton, public ReadWriteWidget {
  Q_OBJECT
 public:
  explicit  StateButton(const QString &button_true_state_caption,
                        QColor button_true_state_color,
                        const QString &button_false_state_caption,
                        QColor button_false_State_color, QWidget *parent = nullptr);

  void setState(bool state) {
    current_state = state;


//    if (button_states.contains(current_state)) {
//      auto current_color = button_states[current_state].button_color;
//      auto current_caption = button_states[current_state].button_caption;
//
//      auto stylesheet = QString("background-color: %1;").arg(current_color.name());
//      setStyleSheet(stylesheet);
//      setText(current_caption);
//    } else {
//      qWarning() << "Current state color is undefined " << __func__;
//    }

//    if (button_states.contains(current_state)) {
//      auto current_color = button_states[current_state].button_color;
//      auto current_caption = button_states[current_state].button_caption;
//
//      QPalette pal = palette();
//      pal.setColor(QPalette::Button, QColor(current_color));
//      pal.setColor(QPalette::Background, QColor(current_color));
//      pal.setColor(QPalette::Base, QColor(current_color));
//
//      setAutoFillBackground(true);
//      setPalette(pal);
//      setText(current_caption);
//      update();
//    } else {
//      qWarning() << "Current state color is undefined " << __func__;
//    }

    if (button_states.contains(current_state)) {
      auto current_color = button_states[current_state].button_color;
      auto current_caption = button_states[current_state].button_caption;

      auto current_color_pressed = current_color.darker(105);
      auto stylesheet = QString("QPushButton {"
//                                "margin: 1px;"
                                "padding: 8px;"
                                "border-color: #0c457e;"
                                "border-style: outset;"
                                "border-radius: 3px;"
                                "border-width: 1px;"
                                "color: black;"
                                "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 %1, stop: 1 %2);"
                                "}"
                                "QPushButton:pressed {"
                                "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 %2, stop: 1 %1);"
                                "}").arg(current_color.name(), current_color_pressed.name());
      setStyleSheet(stylesheet);
      setText(current_caption);
      update();
    } else {
      qWarning() << "Current state color is undefined " << __func__;
    }

//    palette.setColor(QPalette::Base, button_states[current_state].button_color);
//    setPalette(palette);
//    setText(button_states[current_state].button_caption);
  }

  inline bool getState() const {
    return current_state;
  };

  void setReadOnlyMode(bool status) override;

 signals:
  void stateChanged(bool state);

 private:
  QMap<bool, ButtonState> button_states;
  bool current_state;

  void initUI();

 private slots:
  void releasedSlot();
};

#endif //SYNCSYS_DEVICE_WIDGET_WIDGETS_COMMON_BASIC_STATEBUTTON_H_
