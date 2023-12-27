#include "widgets/common/basic/captionedbutton.h"

#include <QVBoxLayout>

#include "widgets/common/basic/standardpropertylabel.h"


CaptionedButton::CaptionedButton(const QString& above_caption, const QString& inside_caption, QWidget *parent): QWidget(parent) {
  initUI(above_caption, inside_caption);
}

void CaptionedButton::initUI(const QString &above_caption, const QString &inside_caption) {
  auto *main_layout = new QVBoxLayout(this);

  auto *above_caption_label = new StandardPropertyLabel(above_caption, 10, this);
  button = new StandardButton(inside_caption, this);

  main_layout->addWidget(above_caption_label);
  main_layout->addWidget(button);
  main_layout->setAlignment(Qt::AlignLeft);

//  main_layout->setSizeConstraint(QLayout::SetMaximumSize);

  QObject::connect(button, &StandardButton::pressed,
                   this, &CaptionedButton::clicked);
}

void CaptionedButton::setReadOnlyMode(bool status) {
  button->setReadOnlyMode(status);
}
