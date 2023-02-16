#include "epsscommands.h"
#include <services/enumconverter.h>

#include "epssdevice.h"


SetChannelDelayCommand::SetChannelDelayCommand(const std::string &name,
                                               const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT SetChannelDelayCommand::execute(const VARIANT &argin,
                                        ErrorCode *error_code) {
  uint16_t channel_num;
  uint64_t delay;
  REQUEST_PREPROCESS(
      auto request = std::get<std::vector<SCALAR_VARIANT>>(argin);
      if (request.size() != 2) {
        SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST)
        return {};
      }

      channel_num = std::get<uint16_t>(request[0]);
      delay = std::get<uint64_t>(request[1]);,
      {}, error_code
      )

  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->write_channel_delay(channel_num, delay),,,error_code);
  return {};
}

GetChannelDelayCommand::GetChannelDelayCommand(const std::string &name,
                                               const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT GetChannelDelayCommand::execute(const VARIANT &argin,
                                        ErrorCode *error_code) {
  uint16_t channel_num;

  REQUEST_PREPROCESS(
      auto request = std::get<SCALAR_VARIANT>(argin);
      channel_num = std::get<uint16_t>(request);,
      {}, error_code
      );

  uint64_t delay;
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_channel_delay(channel_num),
                                delay = spec_device->getChannelDelay(channel_num, error_code);,, error_code);
  return delay;
}

SetChannelWidthCommand::SetChannelWidthCommand(const std::string &name,
                                               const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT SetChannelWidthCommand::execute(const VARIANT &argin,
                                        ErrorCode *error_code) {
  uint16_t channel_num;
  uint64_t width;
  REQUEST_PREPROCESS(
      auto request = std::get<std::vector<SCALAR_VARIANT>>(argin);
      if (request.size() != 2) {
        SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST)
        return {};
      }

      channel_num = std::get<uint16_t>(request[0]);
      width = std::get<uint64_t>(request[1]);,
      {}, error_code
  )

  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->write_channel_width(channel_num, width),,,error_code);
  return {};
}

GetChannelWidthCommand::GetChannelWidthCommand(const std::string &name,
                                               const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT GetChannelWidthCommand::execute(const VARIANT &argin,
                                        ErrorCode *error_code) {
  uint16_t channel_num;

  REQUEST_PREPROCESS(
      auto request = std::get<SCALAR_VARIANT>(argin);
      channel_num = std::get<uint16_t>(request);,
      {}, error_code
  );

  uint64_t width;
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_channel_width(channel_num),
                                width = spec_device->getChannelDelay(channel_num, error_code);,, error_code);
  return width;
}

SetChannelStartSourceCommand::SetChannelStartSourceCommand(const std::string &name,
                                               const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT SetChannelStartSourceCommand::execute(const VARIANT &argin,
                                        ErrorCode *error_code) {
  uint16_t channel_num;
  int16_t start_source;
  REQUEST_PREPROCESS(
      auto request = std::get<std::vector<SCALAR_VARIANT>>(argin);
      if (request.size() != 2) {
        SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST)
        return {};
      }

      channel_num = std::get<uint16_t>(request[0]);
      start_source = std::get<int16_t>(request[1]);
      ,{},error_code
      );

  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->write_channel_source(channel_num, start_source),
                                ,,error_code);
  return {};
}

GetChannelStartSourceCommand::GetChannelStartSourceCommand(const std::string &name,
                                                           const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT GetChannelStartSourceCommand::execute(const VARIANT &argin,
                                              ErrorCode *error_code) {
  uint16_t channel_num;
  REQUEST_PREPROCESS(
      auto request = std::get<SCALAR_VARIANT>(argin);
      channel_num = std::get<uint16_t>(request);
      ,{},error_code);

  int16_t start_source;
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_channel_source(channel_num),
                                start_source = spec_device->getChannelStartSource(channel_num),,error_code);
  return start_source;
}

SetChannelStartModeCommand::SetChannelStartModeCommand(const std::string &name,
                                                           const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT SetChannelStartModeCommand::execute(const VARIANT &argin,
                                              ErrorCode *error_code) {
  uint16_t channel_num;
  int16_t start_mode;
  REQUEST_PREPROCESS(
      auto request = std::get<std::vector<SCALAR_VARIANT>>(argin);
      if (request.size() != 2) {
        SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST)
        return {};
      }

      channel_num = std::get<uint16_t>(request[0]);
      start_mode = std::get<int16_t>(request[1]);
  ,{},error_code
  );

  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->write_channel_mode(channel_num, start_mode),
  ,,error_code);
  return {};
}

GetChannelStartModeCommand::GetChannelStartModeCommand(const std::string &name,
                                                       const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT GetChannelStartModeCommand::execute(const VARIANT &argin,
                                            ErrorCode *error_code) {
  uint16_t channel_num;
  REQUEST_PREPROCESS(
      auto request = std::get<SCALAR_VARIANT>(argin);
      channel_num = std::get<uint16_t>(request);
  ,{},error_code);

  int16_t start_mode;
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_channel_source(channel_num),
                                start_mode = spec_device->getChannelStartMode(channel_num),,error_code);
  return start_mode;
}

SetChannelEnabledCommand::SetChannelEnabledCommand(const std::string &name,
                                                       const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT SetChannelEnabledCommand::execute(const VARIANT &argin,
                                            ErrorCode *error_code) {
  uint16_t channel_num;
  bool enabled;
  REQUEST_PREPROCESS(
      auto request = std::get<std::vector<SCALAR_VARIANT>>(argin);
      if (request.size() != 2) {
        SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST)
        return {};
      }

      channel_num = std::get<uint16_t>(request[0]);
      enabled = std::get<bool>(request[1]);
      ,{},error_code
      );

  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->write_channel_enabled(channel_num, enabled),,,error_code);
  return {};
}

IsChannelEnabledCommand::IsChannelEnabledCommand(const std::string &name,
                                                   const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT IsChannelEnabledCommand::execute(const VARIANT &argin,
                                          ErrorCode *error_code) {
  uint16_t channel_num;
  REQUEST_PREPROCESS(
      auto request = std::get<SCALAR_VARIANT>(argin);
      channel_num = std::get<uint16_t>(request);
      ,{},error_code
      );

  bool enabled;
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_channel_enabled(channel_num),
                                enabled = spec_device->getChannelEnabled(channel_num),{},error_code);
  return enabled;
}

SetChannelInvertedCommand::SetChannelInvertedCommand(const std::string &name,
                                                   const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT SetChannelInvertedCommand::execute(const VARIANT &argin,
                                          ErrorCode *error_code) {
  uint16_t channel_num;
  bool inverted;
  REQUEST_PREPROCESS(
      auto request = std::get<std::vector<SCALAR_VARIANT>>(argin);
      if (request.size() != 2) {
        SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST)
        return {};
      }

      channel_num = std::get<uint16_t>(request[0]);
      inverted = std::get<bool>(request[1]);
  ,{},error_code
  );

  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->write_channel_inverted(channel_num, inverted),,,error_code);
  return {};
}

IsChannelInvertedCommand::IsChannelInvertedCommand(const std::string &name,
                                                     const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT IsChannelInvertedCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  uint16_t channel_num;
  REQUEST_PREPROCESS(
      auto request = std::get<SCALAR_VARIANT>(argin);
      channel_num = std::get<uint16_t>(request);
  ,{},error_code
  );

  bool inverted;
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_channel_inverted(channel_num),
                                inverted = spec_device->getChannelEnabled(channel_num),{},error_code);
  return inverted;
}

SetChannelNameCommand::SetChannelNameCommand(const std::string &name,
                                                     const std::shared_ptr<Device> &modbus_device):
    Command(name, modbus_device) {

}

VARIANT SetChannelNameCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  uint16_t channel_num;
  std::string name;
  REQUEST_PREPROCESS(
      auto request = std::get<std::vector<SCALAR_VARIANT>>(argin);
      if (request.size() != 2) {
        SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST)
        return {};
      }

      channel_num = std::get<uint16_t>(request[0]);
      name = std::get<std::string>(request[1]);
      ,{},error_code
      );

  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  spec_device->setChannelName(channel_num, name, error_code);
  return {};
}

GetChannelNameCommand::GetChannelNameCommand(const std::string &name,
                                             const std::shared_ptr<Device> &modbus_device):
    Command(name, modbus_device) {

}

VARIANT GetChannelNameCommand::execute(const VARIANT &argin,
                                       ErrorCode *error_code) {
  uint16_t channel_num;
  REQUEST_PREPROCESS(
      auto request = std::get<SCALAR_VARIANT>(argin);
      channel_num = std::get<uint16_t>(request);
      ,{},error_code
      );

  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  auto name = spec_device->getChannelName(channel_num, error_code);
  return name;
}

SetInnerStartPeriodCommand::SetInnerStartPeriodCommand(const std::string &name,
                                                     const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT SetInnerStartPeriodCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  uint64_t period;
  REQUEST_PREPROCESS(
      auto request = std::get<SCALAR_VARIANT>(argin);
      period = std::get<uint64_t>(request);
      ,{},error_code
      );

  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->write_inner_start_period(period),,,error_code);
  return {};
}

GetInnerStartPeriodCommand::GetInnerStartPeriodCommand(const std::string &name,
                                                     const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT GetInnerStartPeriodCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  uint64_t period;
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_inner_start_period(),
                                period = spec_device->getInnerStartPeriod(error_code),,error_code);
  return period;
}

SetInnerStartWidthCommand::SetInnerStartWidthCommand(const std::string &name,
                                                     const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT SetInnerStartWidthCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  uint64_t width;
  REQUEST_PREPROCESS(
      auto request = std::get<SCALAR_VARIANT>(argin);
      width = std::get<uint64_t>(request);
  ,{},error_code
  );

  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->write_inner_start_width(width),,,error_code);
  return {};
}

GetInnerStartWidthCommand::GetInnerStartWidthCommand(const std::string &name,
                                                     const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT GetInnerStartWidthCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  uint64_t width;
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_inner_start_width(),
                                width = spec_device->getInnerStartPeriod(error_code),,error_code);
  return width;
}

SetInnerStartEnabledCommand::SetInnerStartEnabledCommand(const std::string &name,
                                                     const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT SetInnerStartEnabledCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  bool enabled;
  REQUEST_PREPROCESS(
      auto request = std::get<SCALAR_VARIANT>(argin);
      enabled = std::get<bool>(request);
      ,{},error_code
      );

  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->write_inner_start_enabled(enabled),,,error_code);
  return {};
}

IsInnerStartEnabledCommand::IsInnerStartEnabledCommand(const std::string &name,
                                                     const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT IsInnerStartEnabledCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  bool enabled;
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_inner_start_enabled(),
                                enabled = spec_device->getInnerStartEnabled(error_code),,error_code);
  return enabled;
}

SetInnerStartInvertedCommand::SetInnerStartInvertedCommand(const std::string &name,
                                                     const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT SetInnerStartInvertedCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  bool inverted;
  REQUEST_PREPROCESS(
      auto request = std::get<SCALAR_VARIANT>(argin);
      inverted = std::get<bool>(request);
  ,{},error_code
  );

  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->write_inner_start_inv(inverted),,,error_code);
  return {};
}

IsInnerStartInvertedCommand::IsInnerStartInvertedCommand(const std::string &name,
                                                     const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT IsInnerStartInvertedCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  bool inverted;
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_inner_start_inv(),
                                inverted = spec_device->getInnerStartEnabled(error_code),,error_code);
  return inverted;
}

GetSyncModuleStatusesCommand::GetSyncModuleStatusesCommand(const std::string &name,
                                                     const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT GetSyncModuleStatusesCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  return {};
}

GetRFModuleStatusesCommand::GetRFModuleStatusesCommand(const std::string &name,
                                                     const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT GetRFModuleStatusesCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  return {};
}

GetSyncSFPParamsCommand::GetSyncSFPParamsCommand(const std::string &name,
                                                     const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT GetSyncSFPParamsCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_sfp_sync_module_temperature(),,,error_code)
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_sfp_sync_module_voltage(),,,error_code)
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_sfp_sync_module_tx_amperage(),,,error_code)
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_sfp_sync_module_tx_power(),,,error_code)
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_sfp_sync_module_rx_power(),,,error_code)
  auto sfp_statuses = spec_device->getSyncSFPStatuses(error_code);
  IS_ERROR(error_code, return {})

  auto result = {
      SCALAR_VARIANT(sfp_statuses.temperature),
      SCALAR_VARIANT(sfp_statuses.voltage),
      SCALAR_VARIANT(sfp_statuses.tx_shift_amperage),
      SCALAR_VARIANT(sfp_statuses.tx_optical_power),
      SCALAR_VARIANT(sfp_statuses.rx_power)
  };

  return result;
}

GetRFSFPParamsCommand::GetRFSFPParamsCommand(const std::string &name,
                                                     const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT GetRFSFPParamsCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_sfp_rf_module_temperature(),,,error_code)
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_sfp_rf_module_voltage(),,,error_code)
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_sfp_rf_module_tx_amperage(),,,error_code)
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_sfp_rf_module_tx_power(),,,error_code)
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_sfp_rf_module_rx_power(),,,error_code)
  auto sfp_statuses = spec_device->getRFSFPStatuses(error_code);
  IS_ERROR(error_code, return {})

  auto result = {
      SCALAR_VARIANT(sfp_statuses.temperature),
      SCALAR_VARIANT(sfp_statuses.voltage),
      SCALAR_VARIANT(sfp_statuses.tx_shift_amperage),
      SCALAR_VARIANT(sfp_statuses.tx_optical_power),
      SCALAR_VARIANT(sfp_statuses.rx_power)
  };

  return result;
}

GetSyncDesLockCommand::GetSyncDesLockCommand(const std::string &name,
                                                     const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT GetSyncDesLockCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  return {};
}

GetSyncOscLockCommand::GetSyncOscLockCommand(const std::string &name,
                                                     const std::shared_ptr<ModbusDevice> &modbus_device):
    ModbusCommand(name, modbus_device) {

}

VARIANT GetSyncOscLockCommand::execute(const VARIANT &argin,
                                           ErrorCode *error_code) {
  return {};
}
