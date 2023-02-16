#include "epssproperties.h"

#include "services/enumconverter.h"

#include "epssdevice.h"


InnerStartPeriodProperty::InnerStartPeriodProperty(const std::string &name,
                                                   const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}
VARIANT InnerStartPeriodProperty::read(ErrorCode *error_code) {
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_inner_start_period(),
                                return spec_device->getInnerStartPeriod();,,error_code)
  return VARIANT();
}

void InnerStartPeriodProperty::write(const VARIANT &value,
                                     ErrorCode *error_code) {
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  uint64_t request = std::get<uint64_t>(std::get<SCALAR_VARIANT>(value));
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->write_inner_start_period(request),,,error_code)
}

InnerStartWidthProperty::InnerStartWidthProperty(const std::string &name,
                                                 const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}

VARIANT InnerStartWidthProperty::read(ErrorCode *error_code) {
  return VARIANT();
}

void InnerStartWidthProperty::write(const VARIANT &value,
                                    ErrorCode *error_code) {

}

InnerStartOnProperty::InnerStartOnProperty(const std::string &name,
                                                   const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}
VARIANT InnerStartOnProperty::read(ErrorCode *error_code) {
  return VARIANT();
}

void InnerStartOnProperty::write(const VARIANT &value,
                                     ErrorCode *error_code) {

}

InnerStartInvProperty::InnerStartInvProperty(const std::string &name,
                                             const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}

VARIANT InnerStartInvProperty::read(ErrorCode *error_code) {
  return VARIANT();
}

void InnerStartInvProperty::write(const VARIANT &value,
                                  ErrorCode *error_code) {

}

ChannelsDelayProperty::ChannelsDelayProperty(const std::string &name,
                                                   const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}
VARIANT ChannelsDelayProperty::read(ErrorCode *error_code) {
  return VARIANT();
}

void ChannelsDelayProperty::write(const VARIANT &value,
                                     ErrorCode *error_code) {

}


ChannelsWidthProperty::ChannelsWidthProperty(const std::string &name,
                                                   const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}
VARIANT ChannelsWidthProperty::read(ErrorCode *error_code) {
  return VARIANT();
}

void ChannelsWidthProperty::write(const VARIANT &value,
                                     ErrorCode *error_code) {

}

ChannelsOnProperty::ChannelsOnProperty(const std::string &name,
                                                   const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}
VARIANT ChannelsOnProperty::read(ErrorCode *error_code) {
  return VARIANT();
}

void ChannelsOnProperty::write(const VARIANT &value,
                                     ErrorCode *error_code) {

}

ChannelsInvProperty::ChannelsInvProperty(const std::string &name,
                                                   const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}
VARIANT ChannelsInvProperty::read(ErrorCode *error_code) {
  return VARIANT();
}

void ChannelsInvProperty::write(const VARIANT &value,
                                     ErrorCode *error_code) {

}

ChannelsStartSourceProperty::ChannelsStartSourceProperty(const std::string &name,
                                                   const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}
VARIANT ChannelsStartSourceProperty::read(ErrorCode *error_code) {
  return VARIANT();
}

void ChannelsStartSourceProperty::write(const VARIANT &value,
                                     ErrorCode *error_code) {

}

ChannelsStartModeProperty::ChannelsStartModeProperty(const std::string &name,
                                                   const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}

VARIANT ChannelsStartModeProperty::read(ErrorCode *error_code) {
  return VARIANT();
}

void ChannelsStartModeProperty::write(const VARIANT &value,
                                     ErrorCode *error_code) {

}

SyncModuleSFPStatusesProperty::SyncModuleSFPStatusesProperty(const std::string &name,
                                                   const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}
VARIANT SyncModuleSFPStatusesProperty::read(ErrorCode *error_code) {
  return VARIANT();
}

void SyncModuleSFPStatusesProperty::write(const VARIANT &value,
                                     ErrorCode *error_code) {

}

RFModuleSFPStatusesProperty::RFModuleSFPStatusesProperty(const std::string &name,
                                                   const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}
VARIANT RFModuleSFPStatusesProperty::read(ErrorCode *error_code) {
  return VARIANT();
}

void RFModuleSFPStatusesProperty::write(const VARIANT &value,
                                     ErrorCode *error_code) {

}

SyncModuleStatusesProperty::SyncModuleStatusesProperty(const std::string &name,
                                                         const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}
VARIANT SyncModuleStatusesProperty::read(ErrorCode *error_code) {
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_sync_module_tx(),,return {};,error_code)
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_sync_module_rx(),,return {};,error_code)

  auto module_statuses = spec_device->getSyncModuleStatuses(error_code);
  auto result = {SCALAR_VARIANT(module_statuses.rx_loss), SCALAR_VARIANT(module_statuses.tx_fault)};
  return result;
}

void SyncModuleStatusesProperty::write(const VARIANT &value,
                                        ErrorCode *error_code) {
  SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST)
}

RFModuleStatusesProperty::RFModuleStatusesProperty(const std::string &name,
                                                         const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}
VARIANT RFModuleStatusesProperty::read(ErrorCode *error_code) {
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_rf_module_tx(),,return {};,error_code)
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_rf_module_rx(),,return {};,error_code)

  auto module_statuses = spec_device->getRFModuleStatuses(error_code);
  auto result = {SCALAR_VARIANT(module_statuses.rx_loss), SCALAR_VARIANT(module_statuses.tx_fault)};
  return result;
}

void RFModuleStatusesProperty::write(const VARIANT &value,
                                        ErrorCode *error_code) {
  SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST);
}

SyncModuleDesLockProperty::SyncModuleDesLockProperty(const std::string &name,
                                                         const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}
VARIANT SyncModuleDesLockProperty::read(ErrorCode *error_code) {
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_des_lock(),
                                return spec_device->getSyncDesLock();,,error_code)
  return VARIANT();
}

void SyncModuleDesLockProperty::write(const VARIANT &value,
                                        ErrorCode *error_code) {
  SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST)
}

SyncModuleOscLockProperty::SyncModuleOscLockProperty(const std::string &name,
                                                         const std::shared_ptr<ModbusDevice> &modbus_device) : ModbusProperty(
    name,
    modbus_device) {

}
VARIANT SyncModuleOscLockProperty::read(ErrorCode *error_code) {
  auto spec_device = static_pointer_cast<EPSSDevice>(device);
  MODBUS_RW_DEVICE_ERROR_HANDLE(spec_device->read_osc_lock(),
                                return spec_device->getSyncOscLock();,,error_code)
  return VARIANT();
}

void SyncModuleOscLockProperty::write(const VARIANT &value,
                                        ErrorCode *error_code) {
  SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST)
}
