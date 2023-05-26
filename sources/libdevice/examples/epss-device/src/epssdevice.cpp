#include "epssdevice.h"

#include "examples/epss-device/src/epsscommands.h"
#include "examples/epss-device/src/epssproperties.h"

#include "examples/epss-device/src/consts.h"

static const int CHANNEL_COUNT = 12;
static const int DEFAULT_NANO_DISCRETE = 25;
static const std::string DEFAULT_CHANNEL_NAME = "Канал";

#define CHANNEL_NUM_CHECK(channel_num, error_code, return_value) if (channel_num < 0 || channel_num >= channel_count) { \
  SET_ERROR_CODE(error_code, ErrorCode::INVALID_REQUEST)                                                                \
  return return_value; \
}


std::shared_ptr<EPSSDevice> EPSSDevice::createEPSSDevice(const std::string &name,
                                                         const std::string &ip,
                                                         int port,
                                                         int modbus_id,
                                                         ErrorCode *error_code) {
  auto modbus_client = std::make_shared<ModbusClient>(ip, port);
  std::shared_ptr<ModbusDevice> base_device = std::shared_ptr<EPSSDevice>(new EPSSDevice(name, modbus_client));

  ModbusDevice::createModbusDevice(base_device, error_code);
//  std::shared_ptr<EPSSDevice> base_modbus_device = std::static_pointer_cast<EPSSDevice>(ModbusDevice::createModbusDevice(name, ip, port, modbus_id, error_code));
  IS_ERROR__D(
      error_code,
      return nullptr;
  );

  std::shared_ptr<EPSSDevice> device = std::static_pointer_cast<EPSSDevice>(base_device);
  device->initChannels(CHANNEL_COUNT);

  auto inner_start_period_property = std::make_shared<InnerStartPeriodProperty>(INNER_START_PERIOD_PROP_NAME, device);
  auto inner_start_width_property = std::make_shared<InnerStartPeriodProperty>(INNER_START_WIDTH_PROP_NAME, device);
  auto inner_start_on_property = std::make_shared<InnerStartOnProperty>(INNER_START_ON_PROP_NAME, device);
  auto inner_start_inv_property = std::make_shared<InnerStartInvProperty>(INNER_START_INV_PROP_NAME, device);
  auto channels_delay_property = std::make_shared<ChannelsDelayProperty>(CHANNELS_DELAY_PROP_NAME, device);
  auto channels_width_property = std::make_shared<ChannelsWidthProperty>(CHANNELS_WIDTH_PROP_NAME, device);
  auto channels_on_property = std::make_shared<ChannelsOnProperty>(CHANNELS_ON_PROP_NAME, device);
  auto channels_inv_property = std::make_shared<ChannelsInvProperty>(CHANNELS_INV_PROP_NAME, device);
  auto channels_start_source_property = std::make_shared<ChannelsStartSourceProperty>(CHANNELS_START_SOURCE_PROP_NAME, device);
  auto channels_start_mode_property = std::make_shared<ChannelsStartModeProperty>(CHANNELS_START_MODE_PROP_NAME, device);
  auto sync_module_sfp_statuses_property = std::make_shared<SyncModuleSFPStatusesProperty>(SYNC_MODULE_SFP_STATUSES_PROP_NAME, device);
  auto rf_module_sfp_statuses_property = std::make_shared<RFModuleSFPStatusesProperty>(RF_MODULE_SFP_STATUSES_PROP_NAME, device);
  auto sync_module_statuses_property = std::make_shared<SyncModuleStatusesProperty>(SYNC_MODULE_STATUSES_PROP_NAME, device);
  auto rf_module_statuses_property = std::make_shared<RFModuleStatusesProperty>(RF_MODULE_STATUSES_PROP_NAME, device);
  auto sync_module_des_lock_property = std::make_shared<SyncModuleDesLockProperty>(SYNC_MODULE_DES_LOCK_PROP_NAME, device);
  auto sync_module_osc_lock_property = std::make_shared<SyncModuleOscLockProperty>(SYNC_MODULE_OSC_LOCK_PROP_NAME, device);

  auto set_channel_delay_command = std::make_shared<SetChannelDelayCommand>(SET_CHANNEL_DELAY_COMM_NAME, device);
  auto get_channel_delay_command = std::make_shared<GetChannelDelayCommand>(GET_CHANNEL_DELAY_COMM_NAME, device);
  auto set_channel_width_command = std::make_shared<SetChannelWidthCommand>(SET_CHANNEL_WIDTH_COMM_NAME, device);
  auto get_channel_width_command = std::make_shared<GetChannelWidthCommand>(GET_CHANNEL_WIDTH_COMM_NAME, device);
  auto set_channel_enabled_command = std::make_shared<SetChannelEnabledCommand>(SET_CHANNEL_ENABLED_COMM_NAME, device);
  auto is_channel_enabled_command = std::make_shared<IsChannelEnabledCommand>(IS_CHANNEL_ENABLED_COMM_NAME, device);
  auto set_channel_inverted_command = std::make_shared<SetChannelInvertedCommand>(SET_CHANNEL_INVERTED_COMM_NAME, device);
  auto is_channel_inverted_command = std::make_shared<IsChannelInvertedCommand>(IS_CHANNEL_INVERTED_COMM_NAME, device);
  auto set_channel_start_source_command = std::make_shared<SetChannelStartSourceCommand>(SET_CHANNEL_START_SOURCE_COMM_NAME, device);
  auto get_channel_start_source_command = std::make_shared<GetChannelStartSourceCommand>(GET_CHANNEL_START_SOURCE_COMM_NAME, device);
  auto set_channel_start_mode_command = std::make_shared<SetChannelStartModeCommand>(SET_CHANNEL_START_MODE_COMM_NAME, device);
  auto get_channel_start_mode_command = std::make_shared<GetChannelStartModeCommand>(GET_CHANNEL_START_MODE_COMM_NAME, device);
  auto set_channel_name_command = std::make_shared<SetChannelNameCommand>(SET_CHANNEL_NAME_COMM_NAME, device);
  auto get_channel_name_command = std::make_shared<GetChannelNameCommand>(GET_CHANNEL_NAME_COMM_NAME, device);
  auto set_inner_start_period_command = std::make_shared<SetInnerStartPeriodCommand>(SET_INNER_START_PERIOD_COMM_NAME, device);
  auto get_inner_start_period_command = std::make_shared<GetInnerStartPeriodCommand>(GET_INNER_START_PERIOD_COMM_NAME, device);
  auto set_inner_start_width_command = std::make_shared<SetInnerStartWidthCommand>(SET_INNER_START_WIDTH_COMM_NAME, device);
  auto get_inner_start_width_command = std::make_shared<GetInnerStartWidthCommand>(GET_INNER_START_WIDTH_COMM_NAME, device);
  auto set_inner_start_enabled_command = std::make_shared<SetInnerStartEnabledCommand>(SET_INNER_START_ENABLED_COMM_NAME, device);
  auto is_inner_start_enabled_command = std::make_shared<IsInnerStartEnabledCommand>(IS_INNER_START_ENABLED_COMM_NAME, device);
  auto set_inner_start_inverted_command = std::make_shared<SetInnerStartInvertedCommand>(SET_INNER_START_INVERTED_COMM_NAME, device);
  auto is_inner_start_inverted_command = std::make_shared<IsInnerStartInvertedCommand>(IS_INNER_START_INVERTED_COMM_NAME, device);
  auto get_sync_module_statuses_command = std::make_shared<GetSyncModuleStatusesCommand>(GET_SYNC_MODULE_STATUSES_COMM_NAME, device);
  auto get_rf_module_statuses_command = std::make_shared<GetRFModuleStatusesCommand>(GET_RF_MODULE_STATUSES_COMM_NAME, device);
  auto get_sync_sfp_params_command = std::make_shared<GetSyncSFPParamsCommand>(GET_SYNC_SFP_PARAMS_COMM_NAME, device);
  auto get_rf_sfp_params_command = std::make_shared<GetRFSFPParamsCommand>(GET_RF_SFP_PARAMS_COMM_NAME, device);
  auto get_sync_des_lock_command = std::make_shared<GetSyncDesLockCommand>(GET_SYNC_DES_LOCK_COMM_NAME, device);
  auto get_sync_osc_lock_command = std::make_shared<GetSyncOscLockCommand>(GET_SYNC_OSC_LOCK_COMM_NAME, device);

  sync_module_statuses_property->setPollingPeriod(3000, error_code);
  rf_module_statuses_property->setPollingPeriod(3000, error_code);
  sync_module_des_lock_property->setPollingPeriod(3000, error_code);
  sync_module_osc_lock_property->setPollingPeriod(3000, error_code);

  CREATE_DEVICE_ADD_PROPERTY(inner_start_period_property, device, error_code)
  CREATE_DEVICE_ADD_PROPERTY(inner_start_width_property, device, error_code)
  CREATE_DEVICE_ADD_PROPERTY(inner_start_on_property, device, error_code)
  CREATE_DEVICE_ADD_PROPERTY(inner_start_inv_property, device, error_code)
  CREATE_DEVICE_ADD_PROPERTY(channels_delay_property, device, error_code)
  CREATE_DEVICE_ADD_PROPERTY(channels_width_property, device, error_code)
  CREATE_DEVICE_ADD_PROPERTY(channels_on_property, device, error_code)
  CREATE_DEVICE_ADD_PROPERTY(channels_inv_property, device, error_code)
  CREATE_DEVICE_ADD_PROPERTY(channels_start_source_property, device, error_code)
  CREATE_DEVICE_ADD_PROPERTY(channels_start_mode_property, device, error_code)
  CREATE_DEVICE_ADD_PROPERTY(sync_module_statuses_property, device, error_code)
  CREATE_DEVICE_ADD_PROPERTY(rf_module_statuses_property, device, error_code)
  CREATE_DEVICE_ADD_PROPERTY(sync_module_des_lock_property, device, error_code)
  CREATE_DEVICE_ADD_PROPERTY(sync_module_osc_lock_property, device, error_code)

  CREATE_DEVICE_ADD_COMMAND(set_channel_delay_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(get_channel_delay_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(set_channel_width_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(get_channel_width_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(set_channel_enabled_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(is_channel_enabled_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(set_channel_inverted_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(is_channel_inverted_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(set_channel_start_source_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(get_channel_start_source_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(set_channel_start_mode_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(get_channel_start_mode_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(set_channel_name_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(get_channel_name_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(set_inner_start_period_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(get_inner_start_period_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(set_inner_start_width_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(get_inner_start_width_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(set_inner_start_enabled_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(is_inner_start_enabled_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(set_inner_start_inverted_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(is_inner_start_inverted_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(get_sync_module_statuses_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(get_rf_module_statuses_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(get_sync_sfp_params_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(get_rf_sfp_params_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(get_sync_des_lock_command, device, error_code)
  CREATE_DEVICE_ADD_COMMAND(get_sync_osc_lock_command, device, error_code)

  SET_ERROR_CODE(error_code, ErrorCode::SUCCESS);

  device->init();
  return device;
}

EPSSDevice::EPSSDevice(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client) :
    ModbusDevice(name, modbus_client) {
  init();
}

void EPSSDevice::init() {
  channel_count = CHANNEL_COUNT;
  if (channel_count <= 0) return;
//  this->channel_count = channel_count;

  channel_delays.resize(channel_count);
  channel_widths.resize(channel_count);
  channel_enables.resize(channel_count);
  channel_invs.resize(channel_count);
  channel_start_sources.resize(channel_count);
  channel_start_modes.resize(channel_count);
  channel_names.resize(channel_count);
  inited = true;
}

void EPSSDevice::initChannels(int channel_count) {
  this->channel_count = channel_count;
  if (channel_count <= 0) return;
//  this->channel_count = channel_count;

  channel_delays.resize(channel_count);
  channel_widths.resize(channel_count);
  channel_enables.resize(channel_count);
  channel_invs.resize(channel_count);
  channel_start_sources.resize(channel_count);
  channel_start_modes.resize(channel_count);
  channel_names.resize(channel_count);

  inited = true;
}

uint64_t EPSSDevice::getInnerStartPeriod(ErrorCode *error_code) const {
  SET_ERROR_CODE_SUCCESS(error_code)
  return inner_start_period;
}

uint64_t EPSSDevice::getInnerStartWidth(ErrorCode *error_code) const {
  SET_ERROR_CODE_SUCCESS(error_code)
  return inner_start_width;
}

bool EPSSDevice::getInnerStartEnabled(ErrorCode *error_code) const {
  SET_ERROR_CODE_SUCCESS(error_code)
  return inner_start_enabled;
}

bool EPSSDevice::getInnerStartInverted(ErrorCode *error_code) const {
  SET_ERROR_CODE_SUCCESS(error_code)
  return inner_start_inverted;
}

uint64_t EPSSDevice::getChannelDelay(int channel_num, ErrorCode *error_code) const {
  CHANNEL_NUM_CHECK(channel_num, error_code, 0)
  SET_ERROR_CODE_SUCCESS(error_code)
  return channel_delays[channel_num];
}

uint64_t EPSSDevice::getChannelWidth(int channel_num, ErrorCode *error_code) const {
  CHANNEL_NUM_CHECK(channel_num, error_code, 0)
  SET_ERROR_CODE_SUCCESS(error_code);
  return channel_widths[channel_num];
}

bool EPSSDevice::getChannelEnabled(int channel_num, ErrorCode *error_code) const {
  CHANNEL_NUM_CHECK(channel_num, error_code, false)
  SET_ERROR_CODE_SUCCESS(error_code)
  return channel_enables[channel_num];
}

bool EPSSDevice::getChannelInverted(int channel_num, ErrorCode *error_code) const {
  CHANNEL_NUM_CHECK(channel_num, error_code, false)
  SET_ERROR_CODE_SUCCESS(error_code)
  return channel_invs[channel_num];
}

int16_t EPSSDevice::getChannelStartSource(int channel_num, ErrorCode *error_code) const {
  CHANNEL_NUM_CHECK(channel_num, error_code, 0)
  SET_ERROR_CODE_SUCCESS(error_code)
  return channel_start_sources[channel_num];
}

int16_t EPSSDevice::getChannelStartMode(int channel_num, ErrorCode *error_code) const {
  CHANNEL_NUM_CHECK(channel_num, error_code, 0)
  SET_ERROR_CODE_SUCCESS(error_code)
  return channel_start_modes[channel_num];
}

SFPStatuses EPSSDevice::getSyncSFPStatuses(ErrorCode *error_code) const {
  SET_ERROR_CODE_SUCCESS(error_code)
  return sync_module_sfp_params;
}

SFPStatuses EPSSDevice::getRFSFPStatuses(ErrorCode *error_code) const {
  SET_ERROR_CODE_SUCCESS(error_code)
  return rf_module_sfp_params;
}

ModuleStatuses EPSSDevice::getSyncModuleStatuses(ErrorCode *error_code) const {
  SET_ERROR_CODE_SUCCESS(error_code)
  return sync_module_statuses;
}

ModuleStatuses EPSSDevice::getRFModuleStatuses(ErrorCode *error_code) const {
  SET_ERROR_CODE_SUCCESS(error_code)
  return rf_module_statuses;
}

bool EPSSDevice::getSyncDesLock(ErrorCode *error_code) const {
  SET_ERROR_CODE_SUCCESS(error_code)
  return sync_des_lock;
}

bool EPSSDevice::getSyncOscLock(ErrorCode *error_code) const {
  SET_ERROR_CODE_SUCCESS(error_code)
  return sync_osc_lock;
}

modbus::ModbusResult EPSSDevice::read_inner_start_period() {
  std::vector<uint16_t> values(2);
  uint32_t value;

  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readHoldingRegisters(2, 2, values),
      modbus::fromMsbLsb(values[0], values[1], value);
          inner_start_period = value * DEFAULT_NANO_DISCRETE;,
  ,
      error_status
  );

  return error_status;
}

modbus::ModbusResult EPSSDevice::write_inner_start_period(uint64_t value) {
  std::vector<uint16_t> values(2);
  value /= DEFAULT_NANO_DISCRETE;
  modbus::toMsbLsb((uint32_t) value, values[0], values[1]);

  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->writeHoldingRegisters(2, values),
      inner_start_period = value * DEFAULT_NANO_DISCRETE;,
  ,
      error_status
  );

  return error_status;
}

modbus::ModbusResult EPSSDevice::read_inner_start_width() {
  std::vector<uint16_t> values(2);
  uint32_t value;

  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readHoldingRegisters(4, 2, values),
      modbus::fromMsbLsb(values[0], values[1], value);
          inner_start_width = value * DEFAULT_NANO_DISCRETE;,
  ,
      error_status
  );

  return error_status;
}

modbus::ModbusResult EPSSDevice::write_inner_start_width(uint64_t w_val) {
  std::vector<uint16_t> values(2);
  uint32_t value = w_val / DEFAULT_NANO_DISCRETE;
  modbus::toMsbLsb(value, values[0], values[1]);

  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->writeHoldingRegisters(4, values),
      inner_start_width = value * DEFAULT_NANO_DISCRETE;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_inner_start_enabled() {
  uint16_t value;

  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readHoldingRegister(6, value),
      bool enabled = modbus::readByteValue(0, 1, value);
          inner_start_enabled = enabled;,
  ,
      error_status
  );

  return error_status;
}

modbus::ModbusResult EPSSDevice::write_inner_start_enabled(bool enabled) {
  uint16_t value = enabled ? 1: 0;
  modbus::ModbusResult error_status = modbus_client->readHoldingRegister(6, value);
  if (error_status == modbus::NO_MODBUS_ERROR) {
    if (!modbus::writeByteValue(0, 1, enabled, value))
      return modbus::UNHANDLED_ERROR;

    MODBUS_RW_ERROR_HANDLE(
        modbus_client->writeHoldingRegister(6, value),
        inner_start_enabled = enabled;,
    ,
        error_status
    );
  }

  return error_status;
}

modbus::ModbusResult EPSSDevice::read_inner_start_inv() {
  uint16_t value;

  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readHoldingRegister(6, value),
      bool inverted = modbus::readByteValue(1, 1, value);
          inner_start_inverted = inverted;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::write_inner_start_inv(bool inverted) {
  uint16_t value = inverted ? 1: 0;
  modbus::ModbusResult error_status = modbus_client->readHoldingRegister(6, value);

  if (error_status == modbus::NO_MODBUS_ERROR) {
    if (!modbus::writeByteValue(1, 1, inverted, value))
      return modbus::UNHANDLED_ERROR;

    MODBUS_RW_ERROR_HANDLE(
        modbus_client->writeHoldingRegister(6, value),
        inner_start_inverted = inverted;,
    ,
        error_status
    );
  }
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_rf_module_existence() {
  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(2, value),
      bool status = modbus::readByteValue(1, 1, value);
          rf_module_existence = status;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_sync_module_existence() {
  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(2, value),
      bool status = modbus::readByteValue(0, 1, value);
          sync_module_existence = status;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_rf_module_rx() {
  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(3, value),
      bool status = modbus::readByteValue(1, 1, value);
          rf_module_statuses.rx_loss = status;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_sync_module_rx() {
  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(3, value),
      bool status = modbus::readByteValue(0, 1, value);
          sync_module_statuses.rx = status;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_rf_module_tx() {
  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(4, value),
      bool status = modbus::readByteValue(1, 1, value);
          rf_module_statuses.tx = status;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_sync_module_tx() {
  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(4, value),
      bool status = modbus::readByteValue(0, 1, value);
          sync_module_statuses.tx = status;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_des_lock() {
  uint16_t result;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(10, result),
      bool value = modbus::readByteValue(2, 1, result);
          sync_des_lock = value;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_osc_lock() {
  uint16_t result;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(10, result),
      bool value = modbus::readByteValue(2, 1, result);
          sync_osc_lock = value;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_sfp_sync_module_temperature(bool already_selected) {
  if (!already_selected) {
    modbus::ModbusResult error_status = select_sfp(0);
    MODBUS_RW_ERROR_HANDLE(
        error_status,
    ,
        return error_status,
        error_status
    );
  }

  uint16_t value;

  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(5, value),
      float result_value = (float) value / 256.0f;
          if (result_value >= 128) result_value -= 128;

          sync_module_sfp_params.temperature = result_value;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_sfp_sync_module_voltage(bool already_selected) {
  if (!already_selected) {
    modbus::ModbusResult error_status = select_sfp(0);
    MODBUS_RW_ERROR_HANDLE(
        error_status,
    ,
        return error_status,
        error_status
    );
  }

  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(6, value),
      float result_value = (float) value * 0.1f;
          sync_module_sfp_params.voltage = result_value;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_sfp_sync_module_tx_amperage(bool already_selected) {
  if (!already_selected) {
    modbus::ModbusResult error_status = select_sfp(0);
    MODBUS_RW_ERROR_HANDLE(
        error_status,
    ,
        return error_status,
        error_status
    );
  }

  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(7, value),
      float result_value = (float) value * 2.0f;
          sync_module_sfp_params.tx_shift_amperage = result_value;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_sfp_sync_module_tx_power(bool already_selected) {
  if (!already_selected) {
    modbus::ModbusResult error_status = select_sfp(0);
    MODBUS_RW_ERROR_HANDLE(
        error_status,
    ,
        return error_status,
        error_status
    );
  }

  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(8, value),
      float result_value = (float) value * 0.1f;
          sync_module_sfp_params.tx_optical_power = result_value;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_sfp_sync_module_rx_power(bool already_selected) {
  if (!already_selected) {
    modbus::ModbusResult error_status = select_sfp(0);
    MODBUS_RW_ERROR_HANDLE(
        error_status,
    ,
        return error_status,
        error_status
    );
  }

  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(9, value),
      float result_value = (float) value * 0.1f;
          sync_module_sfp_params.rx_power = result_value;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_sfp_rf_module_temperature(bool already_selected) {
  if (!already_selected) {
    modbus::ModbusResult error_status = select_sfp(1);
    MODBUS_RW_ERROR_HANDLE(
        error_status,
    ,
        return error_status,
        error_status
    );
  }

  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(5, value),
      float result_value = (float) value / 256.0f;
          if (result_value >= 128) result_value -= 128;

          rf_module_sfp_params.temperature = result_value;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_sfp_rf_module_voltage(bool already_selected) {
  if (!already_selected) {
    modbus::ModbusResult error_status = select_sfp(1);
    MODBUS_RW_ERROR_HANDLE(
        error_status,
    ,
        return error_status,
        error_status
    );
  }

  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(6, value),
      float result_value = (float) value * 0.1f;
          rf_module_sfp_params.voltage = result_value;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_sfp_rf_module_tx_amperage(bool already_selected) {
  if (!already_selected) {
    modbus::ModbusResult error_status = select_sfp(1);
    MODBUS_RW_ERROR_HANDLE(
        error_status,
    ,
        return error_status,
        error_status
    );
  }

  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(7, value),
      float result_value = (float) value * 2.0f;
          rf_module_sfp_params.tx_shift_amperage = result_value;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_sfp_rf_module_tx_power(bool already_selected) {
  if (!already_selected) {
    modbus::ModbusResult error_status = select_sfp(1);
    MODBUS_RW_ERROR_HANDLE(
        error_status,
    ,
        return error_status,
        error_status
    );
  }

  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(8, value),
      float result_value = (float) value * 0.1f;
          rf_module_sfp_params.tx_optical_power = result_value;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_sfp_rf_module_rx_power(bool already_selected) {
  if (!already_selected) {
    modbus::ModbusResult error_status = select_sfp(1);
    MODBUS_RW_ERROR_HANDLE(
        error_status,
    ,
        return error_status,
        error_status
    );
  }

  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readInputRegister(9, value),
      float result_value = (float) value * 0.1f;
          rf_module_sfp_params.rx_power = result_value;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::select_sfp(int sfp_module_num) {
  // TODO: Дописать обработку ошибок там, где вызывается этот метод
  return modbus_client->writeHoldingRegister(9, sfp_module_num);
}

modbus::ModbusResult EPSSDevice::read_channel_delay(uint16_t channel_num) {
  if (channel_num < 0 || channel_num >= CHANNEL_COUNT) return modbus::INVALID_REQUEST;

  uint32_t value;
  std::vector<uint16_t> values(2);
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readHoldingRegisters(10 + 5 * channel_num, 2, values),
      modbus::fromMsbLsb(values[0], values[1], value);
          channel_delays[channel_num] = value * DEFAULT_NANO_DISCRETE;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::write_channel_delay(uint16_t channel_num, uint64_t value) {
  if (channel_num < 0 || channel_num >= CHANNEL_COUNT) return modbus::INVALID_REQUEST;

  uint32_t delay_value = value / DEFAULT_NANO_DISCRETE;
  std::vector<uint16_t> values(2);
  modbus::toMsbLsb(delay_value, values[0], values[1]);

  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->writeHoldingRegisters(10 + channel_num * 5, values),
      channel_delays[channel_num] = value * DEFAULT_NANO_DISCRETE;, ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_channel_width(uint16_t channel_num) {
  if (channel_num < 0 || channel_num >= CHANNEL_COUNT) return modbus::INVALID_REQUEST;

  uint32_t value;
  std::vector<uint16_t> values(2);
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readHoldingRegisters(12 + 5 * channel_num, 2, values),
      modbus::fromMsbLsb(values[0], values[1], value);
          channel_widths[channel_num] = value * DEFAULT_NANO_DISCRETE;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::write_channel_width(uint16_t channel_num, uint64_t value) {
  if (channel_num < 0 || channel_num >= CHANNEL_COUNT) return modbus::INVALID_REQUEST;

  uint32_t width_value = value / DEFAULT_NANO_DISCRETE;
  std::vector<uint16_t> values(2);
  modbus::toMsbLsb(width_value, values[0], values[1]);

  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->writeHoldingRegisters(12 + channel_num * 5, values),
      channel_widths[channel_num] = value * DEFAULT_NANO_DISCRETE;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_channel_enabled(uint16_t channel_num) {
  if (channel_num < 0 || channel_num >= CHANNEL_COUNT) return modbus::INVALID_REQUEST;

  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readHoldingRegister(14 + channel_num * 5, value),
      bool status = modbus::readByteValue(0, 1, value);
          channel_enables[channel_num] = status;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::write_channel_enabled(uint16_t channel_num, bool enabled) {
  if (channel_num < 0 || channel_num >= CHANNEL_COUNT) return modbus::INVALID_REQUEST;

  uint16_t value;
  modbus::ModbusResult error_status = modbus_client->readHoldingRegister(14 + channel_num * 5, value);
  if (error_status == modbus::NO_MODBUS_ERROR) {
    if (!modbus::writeByteValue(0, 1, enabled, value)) return modbus::INVALID_RESPONSE;

    MODBUS_RW_ERROR_HANDLE(
        modbus_client->writeHoldingRegister(14 + channel_num * 5, value),
        channel_enables[channel_num] = enabled;,
    ,
        error_status
    );
  }
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_channel_inverted(uint16_t channel_num) {
  if (channel_num < 0 || channel_num >= CHANNEL_COUNT) return modbus::INVALID_REQUEST;

  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readHoldingRegister(14 + channel_num * 5, value),
      bool status = modbus::readByteValue(1, 1, value);
          channel_invs[channel_num] = status;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::write_channel_inverted(uint16_t channel_num, bool inverted) {
  if (channel_num < 0 || channel_num >= CHANNEL_COUNT) return modbus::INVALID_REQUEST;

  uint16_t value;
  modbus::ModbusResult error_status = modbus_client->readHoldingRegister(14 + channel_num * 5, value);
  if (error_status == modbus::NO_MODBUS_ERROR) {
    if (!modbus::writeByteValue(1, 1, inverted, value)) return modbus::INVALID_RESPONSE;

    MODBUS_RW_ERROR_HANDLE(
        modbus_client->writeHoldingRegister(14 + channel_num * 5, value),
        channel_invs[channel_num] = inverted;, ,
        error_status
    );
    return error_status;
  }

  return error_status;
}

modbus::ModbusResult EPSSDevice::read_channel_source(uint16_t channel_num) {
  if (channel_num < 0 || channel_num >= CHANNEL_COUNT) return modbus::INVALID_REQUEST;

  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readHoldingRegister(14 + channel_num * 5, value),
      uint16_t source = modbus::readByteValue(2, 5, value);
          if (source > 0b10011) return modbus::INVALID_RESPONSE;

          channel_start_sources[channel_num] = source;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::write_channel_source(uint16_t channel_num, int16_t source) {
  if (channel_num < 0 || channel_num >= CHANNEL_COUNT) return modbus::INVALID_REQUEST;
  if (source > 0b10011) return modbus::INVALID_REQUEST;

  uint16_t value;
  modbus::ModbusResult error_status = modbus_client->readHoldingRegister(14 + channel_num * 5, value);

  if (error_status == modbus::NO_MODBUS_ERROR) {
    if (!modbus::writeByteValue(2, 5, source, value)) return modbus::INVALID_RESPONSE;

    MODBUS_RW_ERROR_HANDLE(
        modbus_client->writeHoldingRegister(14 + channel_num * 5, value),
        channel_start_sources[channel_num] = source;,
    ,
        error_status
    );
  }
  return error_status;
}

modbus::ModbusResult EPSSDevice::read_channel_mode(uint16_t channel_num) {
  if (channel_num < 0 || channel_num >= CHANNEL_COUNT) return modbus::INVALID_REQUEST;

  uint16_t value;
  modbus::ModbusResult error_status;
  MODBUS_RW_ERROR_HANDLE(
      modbus_client->readHoldingRegister(14 + channel_num * 5, value),
      uint16_t mode = modbus::readByteValue(7, 1, value) & 0b1;
          channel_start_modes[channel_num] = mode;,
  ,
      error_status
  );
  return error_status;
}

modbus::ModbusResult EPSSDevice::write_channel_mode(uint16_t channel_num, int16_t mode) {
  if (channel_num < 0 || channel_num >= CHANNEL_COUNT) return modbus::INVALID_REQUEST;
  if ((mode & 0b1) != mode) return modbus::INVALID_REQUEST;

  uint16_t value;
  modbus::ModbusResult error_status = modbus_client->readHoldingRegister(14 + channel_num * 5, value);
  if (error_status == modbus::NO_MODBUS_ERROR) {
    if (!modbus::writeByteValue(7, 1, mode, value)) return modbus::INVALID_RESPONSE;
    MODBUS_RW_ERROR_HANDLE(
        modbus_client->writeHoldingRegister(14 + channel_num * 5, value),
        channel_start_modes[channel_num] = mode;,
    ,
        error_status
    )
  }

  return error_status;
}

const std::string &EPSSDevice::getChannelName(uint16_t channel_num, ErrorCode *error_code) {
  CHANNEL_NUM_CHECK(channel_num, error_code, DEFAULT_CHANNEL_NAME)
  SET_ERROR_CODE_SUCCESS(error_code)
  return channel_names[channel_num];
}

void EPSSDevice::setChannelName(uint16_t channel_num, const std::string &name, ErrorCode *error_code) {
  CHANNEL_NUM_CHECK(channel_num, error_code,)

  channel_names[channel_num] = name;
  SET_ERROR_CODE_SUCCESS(error_code)
}
