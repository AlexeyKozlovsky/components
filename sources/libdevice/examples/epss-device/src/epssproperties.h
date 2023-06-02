#ifndef LIBDEVICE_EXAMPLES_EPSS_DEVICE_PROPERTIES_H_
#define LIBDEVICE_EXAMPLES_EPSS_DEVICE_PROPERTIES_H_

#include <devices/modbus/modbusproperty.h>
#include <devices/modbus/modbusdevice.h>


class InnerStartPeriodProperty: public ModbusProperty {
 public:
  InnerStartPeriodProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};

class InnerStartWidthProperty: public ModbusProperty {
 public:
  InnerStartWidthProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};

class InnerStartOnProperty: public ModbusProperty {
 public:
  InnerStartOnProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};

class InnerStartInvProperty: public ModbusProperty {
 public:
  InnerStartInvProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};

class ChannelsDelayProperty: public ModbusProperty {
 public:
  ChannelsDelayProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};

class ChannelsWidthProperty: public ModbusProperty {
 public:
  ChannelsWidthProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};

class ChannelsOnProperty: public ModbusProperty {
 public:
  ChannelsOnProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};

class ChannelsInvProperty: public ModbusProperty {
 public:
  ChannelsInvProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};


class ChannelsStartSourceProperty: public ModbusProperty {
 public:
  ChannelsStartSourceProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};

class ChannelsStartModeProperty: public ModbusProperty {
 public:
  ChannelsStartModeProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};

class SyncModuleSFPStatusesProperty: public ModbusProperty {
 public:
  SyncModuleSFPStatusesProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};


class RFModuleSFPStatusesProperty: public ModbusProperty {
 public:
  RFModuleSFPStatusesProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};

class SyncModuleStatusesProperty: public ModbusProperty {
 public:
  SyncModuleStatusesProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};

class RFModuleStatusesProperty: public ModbusProperty {
 public:
  RFModuleStatusesProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};

class SyncModuleDesLockProperty: public ModbusProperty {
 public:
  SyncModuleDesLockProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};

class SyncModuleOscLockProperty: public ModbusProperty {
 public:
  SyncModuleOscLockProperty(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D read(ErrorCode *error_code = nullptr) override;
  void write(const VARIANT__D &value, ErrorCode *error_code = nullptr) override;
};





#endif //LIBDEVICE_EXAMPLES_EPSS_DEVICE_PROPERTIES_H_
