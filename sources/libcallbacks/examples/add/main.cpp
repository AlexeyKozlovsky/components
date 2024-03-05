#include <iostream>

#include <QApplication>
#include <QVector>

#include <callbacks/models/valuecallbacks.h>
#include <widgets/common/basic/standardlineedit.h>


int main(int argc, char *argv[])
{
  qRegisterMetaType<QVector<quint64>>("QVector<quint64>");
  qRegisterMetaType<QVector<bool> >("QVector<bool>");
  qRegisterMetaType<QVector<bool> >("QVector<quint16>");
  qRegisterMetaType<QVector<bool> >("QVector<qint16>");
  qRegisterMetaType<QVector<bool> >("QVector<quint32>");
  qRegisterMetaType<QVector<bool> >("QVector<qint32>");
  QApplication a(argc, argv);
  auto bool_callback = std::make_shared<BoolValuesCallback>();
  QVector<bool> aa = {true};
  bool_callback->pushEvent(aa);

  auto line_edit = std::make_shared<StandardLineEdit>();
  line_edit->show();


  QObject::connect(bool_callback.get(), &BoolValuesCallback::statusChanged,
                   line_edit.get(), [&](const QVector<bool> &tilt) {

  });


  return a.exec();
}
