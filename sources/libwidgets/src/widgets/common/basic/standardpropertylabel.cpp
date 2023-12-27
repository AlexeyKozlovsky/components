#include "widgets/common/basic/standardpropertylabel.h"

#include "widgets/consts.h"


StandardPropertyLabel::StandardPropertyLabel(const QString& caption, int font_size, QWidget *parent):
  QLabel(caption, parent) {
  initUI(font_size);
}

StandardPropertyLabel::StandardPropertyLabel(const QString &caption, QWidget *parent):
  QLabel(caption, parent) {
  initUI(14);
}

void StandardPropertyLabel::initUI(int font_size) {
  setFont(default_font);
}
