#ifndef TEST_PROJECT_WITH_MODULE_ARCH_SERVICES_VALUECALLBACKS_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_SERVICES_VALUECALLBACKS_H_

#include <QObject>

#include <utils/baseutils.h>

#include "callbacks/export.h"

class CALLBACKS_EXPORT ValueCallback: public QObject {
  Q_OBJECT
 public:
  explicit ValueCallback(QObject *parent = nullptr);

 signals:
  void statusChangedError(const QString &error_message);
  void deviceStateChanged(DeviceState device_state);
};


class CALLBACKS_EXPORT BoolValueCallback: public ValueCallback {
  Q_OBJECT
 public:
  explicit BoolValueCallback(QObject *parent = nullptr);

 public:
  virtual void pushEvent(bool value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(bool status);
};


class CALLBACKS_EXPORT BoolValuesCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit BoolValuesCallback(QObject *parent = nullptr);
  virtual void pushEvent(const QVector<bool> &value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(const QVector<bool> &status);
};


class CALLBACKS_EXPORT UShortValueCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit UShortValueCallback(QObject *parent = nullptr);
  virtual void pushEvent(quint16 value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(quint16 status);
};

class CALLBACKS_EXPORT UShortValuesCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit UShortValuesCallback(QObject *parent = nullptr);
  virtual void pushEvent(const QVector<quint16> &value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(const QVector<quint16> &status);
};

class CALLBACKS_EXPORT ShortValueCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit ShortValueCallback(QObject *parent = nullptr);
  virtual void pushEvent(qint16 value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(qint16 status);
};

class CALLBACKS_EXPORT ShortValuesCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit ShortValuesCallback(QObject *parent = nullptr);
  virtual void pushEvent(const QVector<qint16> &value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(const QVector<qint16> &status);
};


class CALLBACKS_EXPORT ULongValueCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit ULongValueCallback(QObject *parent = nullptr);
  virtual void pushEvent(quint32 value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(quint32 status);
};

class CALLBACKS_EXPORT ULongValuesCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit ULongValuesCallback(QObject *parent = nullptr);
  virtual void pushEvent(const QVector<quint32> &value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(const QVector<quint32> &status);
};


class CALLBACKS_EXPORT LongValueCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit LongValueCallback(QObject *parent = nullptr);
  virtual void pushEvent(qint32 value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(qint32 status);
};

class CALLBACKS_EXPORT LongValuesCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit LongValuesCallback(QObject *parent = nullptr);
  virtual void pushEvent(const QVector<qint32> &value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(const QVector<qint32> &status);
};

class CALLBACKS_EXPORT ULong64ValueCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit ULong64ValueCallback(QObject *parent = nullptr);
  virtual void pushEvent(quint64 value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(quint64 status);
};

class CALLBACKS_EXPORT ULong64ValuesCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit ULong64ValuesCallback(QObject *parent = nullptr);
  virtual void pushEvent(const QVector<quint64> &value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(const QVector<quint64> &status);
};

class CALLBACKS_EXPORT Long64ValueCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit Long64ValueCallback(QObject *parent = nullptr);
  virtual void pushEvent(qint64 value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(qint64 status);
};

class CALLBACKS_EXPORT Long64ValuesCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit Long64ValuesCallback(QObject *parent = nullptr);
  virtual void pushEvent(const QVector<qint64> &value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(const QVector<qint64> &status);
};


class CALLBACKS_EXPORT StringValueCallback: public ValueCallback {
  Q_OBJECT
 public:
  explicit StringValueCallback(QObject *parent = nullptr);
  virtual void pushEvent(const QString &value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(const QString &status);
};

class CALLBACKS_EXPORT StringValuesCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit StringValuesCallback(QObject *parent = nullptr);
  virtual void pushEvent(const QVector<QString> &value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(const QVector<QString> &status);
};

class CALLBACKS_EXPORT DoubleValueCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit DoubleValueCallback(QObject *parent = nullptr);
  virtual void pushEvent(double value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(double status);
};

class CALLBACKS_EXPORT DoubleValuesCallback: public ValueCallback {
 Q_OBJECT
 public:
  explicit DoubleValuesCallback(QObject *parent = nullptr);
  virtual void pushEvent(const QVector<double> &value) {
    emit statusChanged(value);
  };

 signals:
  void statusChanged(const QVector<double> &status);
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_SERVICES_VALUECALLBACKS_H_
