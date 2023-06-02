#ifndef LIBDEVICE_EXAMPLES_EPSS_DEVICE_COMMANDS_H_
#define LIBDEVICE_EXAMPLES_EPSS_DEVICE_COMMANDS_H_

#include <devices/modbus/modbuscommand.h>
#include <devices/modbus/modbusdevice.h>

class SetChannelDelayCommand: public ModbusCommand {
 public:
  SetChannelDelayCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class GetChannelDelayCommand: public ModbusCommand {
 public:
  GetChannelDelayCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class SetChannelWidthCommand: public ModbusCommand {
 public:
  SetChannelWidthCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class GetChannelWidthCommand: public ModbusCommand {
 public:
  GetChannelWidthCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class SetChannelStartSourceCommand: public ModbusCommand {
 public:
  SetChannelStartSourceCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class GetChannelStartSourceCommand: public ModbusCommand {
 public:
  GetChannelStartSourceCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class SetChanelStartModeCommand: public ModbusCommand {
 public:
  SetChanelStartModeCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class SetChannelStartModeCommand: public ModbusCommand {
 public:
  SetChannelStartModeCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class GetChannelStartModeCommand: public ModbusCommand {
 public:
  GetChannelStartModeCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};


class SetChannelEnabledCommand: public ModbusCommand {
 public:
  SetChannelEnabledCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class IsChannelEnabledCommand: public ModbusCommand {
 public:
  IsChannelEnabledCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class SetChannelInvertedCommand: public ModbusCommand {
 public:
  SetChannelInvertedCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class IsChannelInvertedCommand: public ModbusCommand {
 public:
  IsChannelInvertedCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class SetChannelNameCommand: public Command {
 public:
  SetChannelNameCommand(const std::string &name, const std::shared_ptr<Device> &device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class GetChannelNameCommand: public Command {
 public:
  GetChannelNameCommand(const std::string &name, const std::shared_ptr<Device> &device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class SetInnerStartPeriodCommand: public ModbusCommand {
 public:
  SetInnerStartPeriodCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class GetInnerStartPeriodCommand: public ModbusCommand {
 public:
  GetInnerStartPeriodCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class SetInnerStartWidthCommand: public ModbusCommand {
 public:
  SetInnerStartWidthCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class GetInnerStartWidthCommand: public ModbusCommand {
 public:
  GetInnerStartWidthCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class SetInnerStartEnabledCommand: public ModbusCommand {
 public:
  SetInnerStartEnabledCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class IsInnerStartEnabledCommand: public ModbusCommand {
 public:
  IsInnerStartEnabledCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class SetInnerStartInvertedCommand: public ModbusCommand {
 public:
  SetInnerStartInvertedCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class IsInnerStartInvertedCommand: public ModbusCommand {
 public:
  IsInnerStartInvertedCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class GetSyncModuleStatusesCommand: public ModbusCommand {
 public:
  GetSyncModuleStatusesCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class GetRFModuleStatusesCommand: public ModbusCommand {
 public:
  GetRFModuleStatusesCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class GetSyncSFPParamsCommand: public ModbusCommand {
 public:
  GetSyncSFPParamsCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class GetRFSFPParamsCommand: public ModbusCommand {
 public:
  GetRFSFPParamsCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class GetSyncDesLockCommand: public ModbusCommand {
 public:
  GetSyncDesLockCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

class GetSyncOscLockCommand: public ModbusCommand {
 public:
  GetSyncOscLockCommand(const std::string &name, const std::shared_ptr<ModbusDevice> &modbus_device);

 protected:
  VARIANT__D execute(const VARIANT__D &argin, ErrorCode *error_code = nullptr);
};

#endif //LIBDEVICE_EXAMPLES_EPSS_DEVICE_COMMANDS_H_
