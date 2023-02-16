#ifndef LIBDEVICE_EXAMPLES_EPSS_DEVICE_DEVICE_H_
#define LIBDEVICE_EXAMPLES_EPSS_DEVICE_DEVICE_H_

#include <devices/modbus/modbusdevice.h>

struct SFPStatuses {
  double temperature;
  double voltage;
  double tx_shift_amperage;
  double tx_optical_power;
  double rx_power;
};

struct ModuleStatuses {
  bool rx;
  bool tx;
  bool rx_loss;
  bool tx_fault;
};


class EPSSDevice: public ModbusDevice {
 public:
  static std::shared_ptr<EPSSDevice> createEPSSDevice(const std::string &name,
                                                      const std::string &ip,
                                                      int port,
                                                      int modbus_id,
                                                      ErrorCode *error_code = nullptr);

  uint64_t getInnerStartPeriod(ErrorCode *error_code = nullptr) const;
  uint64_t getInnerStartWidth(ErrorCode *error_code = nullptr) const;
  bool getInnerStartEnabled(ErrorCode *error_code = nullptr) const;
  bool getInnerStartInverted(ErrorCode *error_code = nullptr) const;

  uint64_t getChannelDelay(int channel_num, ErrorCode *error_code = nullptr) const;
  uint64_t getChannelWidth(int channel_num, ErrorCode *error_code = nullptr) const;
  bool getChannelEnabled(int channel_num, ErrorCode *error_code = nullptr) const;
  bool getChannelInverted(int channel_num, ErrorCode *error_code = nullptr) const;
  int16_t getChannelStartSource(int channel_num, ErrorCode *error_code = nullptr) const;
  int16_t getChannelStartMode(int channel_num, ErrorCode *error_code = nullptr) const;

  SFPStatuses getSyncSFPStatuses(ErrorCode *error_code = nullptr) const;
  SFPStatuses getRFSFPStatuses(ErrorCode *error_code = nullptr) const;
  ModuleStatuses getSyncModuleStatuses(ErrorCode *error_code = nullptr) const;
  ModuleStatuses getRFModuleStatuses(ErrorCode *error_code = nullptr) const;

  bool getSyncDesLock(ErrorCode *error_code = nullptr) const;
  bool getSyncOscLock(ErrorCode *error_code = nullptr) const;

  const std::string &getChannelName(uint16_t channel_num, ErrorCode *error_code = nullptr);
  void setChannelName(uint16_t channel_num, const std::string &name, ErrorCode *error_code = nullptr);

  modbus::ModbusResult read_inner_start_period();
  modbus::ModbusResult write_inner_start_period(uint64_t value);

  modbus::ModbusResult read_inner_start_width();
  modbus::ModbusResult write_inner_start_width(uint64_t value);

  modbus::ModbusResult read_inner_start_enabled();
  modbus::ModbusResult write_inner_start_enabled(bool enabled);

  modbus::ModbusResult read_inner_start_inv();
  modbus::ModbusResult write_inner_start_inv(bool inverted);

  modbus::ModbusResult read_rf_module_existence();
  modbus::ModbusResult read_sync_module_existence();
  modbus::ModbusResult read_rf_module_rx();
  modbus::ModbusResult read_sync_module_rx();
  modbus::ModbusResult read_rf_module_tx();
  modbus::ModbusResult read_sync_module_tx();

  modbus::ModbusResult read_des_lock();
  modbus::ModbusResult read_osc_lock();

  modbus::ModbusResult read_sfp_sync_module_temperature(bool already_selected = true);
  modbus::ModbusResult read_sfp_sync_module_voltage(bool already_selected = true);
  modbus::ModbusResult read_sfp_sync_module_tx_amperage(bool already_selected = true);
  modbus::ModbusResult read_sfp_sync_module_tx_power(bool already_selected = true);
  modbus::ModbusResult read_sfp_sync_module_rx_power(bool already_selected = true);

  modbus::ModbusResult read_sfp_rf_module_temperature(bool already_selected = true);
  modbus::ModbusResult read_sfp_rf_module_voltage(bool already_selected = true);
  modbus::ModbusResult read_sfp_rf_module_tx_amperage(bool already_selected = true);
  modbus::ModbusResult read_sfp_rf_module_tx_power(bool already_selected = true);
  modbus::ModbusResult read_sfp_rf_module_rx_power(bool already_selected = true);

  modbus::ModbusResult select_sfp(int sfp_module_num);

  modbus::ModbusResult read_channel_delay(uint16_t channel_num);
  modbus::ModbusResult write_channel_delay(uint16_t channel_num, uint64_t value);

  modbus::ModbusResult read_channel_width(uint16_t channel_num);
  modbus::ModbusResult write_channel_width(uint16_t channel_num, uint64_t value);

  modbus::ModbusResult read_channel_enabled(uint16_t channel_num);
  modbus::ModbusResult write_channel_enabled(uint16_t channel_num, bool enabled);

  modbus::ModbusResult read_channel_inverted(uint16_t channel_num);
  modbus::ModbusResult write_channel_inverted(uint16_t channel_num, bool inverted);

  modbus::ModbusResult read_channel_source(uint16_t channel_num);
  modbus::ModbusResult write_channel_source(uint16_t channel_num, int16_t source);

  modbus::ModbusResult read_channel_mode(uint16_t channel_num);
  modbus::ModbusResult write_channel_mode(uint16_t channel_num, int16_t mode);

 protected:
  EPSSDevice(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client);

 private:
  ModuleStatuses sync_module_statuses;
  ModuleStatuses rf_module_statuses;
  SFPStatuses sync_module_sfp_params;
  SFPStatuses rf_module_sfp_params;
  bool sync_module_existence;
  bool rf_module_existence;
  bool sync_des_lock;
  bool sync_osc_lock;

  uint64_t inner_start_period;
  uint64_t inner_start_width;
  bool inner_start_enabled;
  bool inner_start_inverted;

  std::vector<uint64_t> channel_delays;
  std::vector<uint64_t> channel_widths;
  std::vector<bool> channel_enables;
  std::vector<bool> channel_invs;

  std::vector<int16_t> channel_start_sources;
  std::vector<int16_t> channel_start_modes;

  int channel_count;
  std::vector<std::string> channel_names;

  void initChannels(int channel_count);
};


#endif //LIBDEVICE_EXAMPLES_EPSS_DEVICE_DEVICE_H_
