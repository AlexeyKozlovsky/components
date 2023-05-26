#ifndef EPSS13_STANDALONE_SERVER_EPSS13_SRC_CONSTS_H_
#define EPSS13_STANDALONE_SERVER_EPSS13_SRC_CONSTS_H_

#include <string>

// TODO: Это потом перенести в библиотеку
static const std::string CONNECT_COMM_NAME = "connect";
static const std::string UPDATE_ADDRESS_COMM_NAME = "update_address";
static const std::string GET_CONNECTION_STATUS_COMM_NAME = "get_connection_status";


// Вот отсюда уже не переносить.
static const std::string INNER_START_PERIOD_PROP_NAME = "inner_start_period";
static const std::string INNER_START_WIDTH_PROP_NAME = "inner_start_width";
static const std::string INNER_START_ON_PROP_NAME = "inner_start_on";
static const std::string INNER_START_INV_PROP_NAME = "inner_start_inv";
static const std::string CHANNELS_DELAY_PROP_NAME = "channels_delay";
static const std::string CHANNELS_WIDTH_PROP_NAME = "channels_width";
static const std::string CHANNELS_ON_PROP_NAME = "channels_on";
static const std::string CHANNELS_INV_PROP_NAME = "channels_inv";
static const std::string CHANNELS_START_SOURCE_PROP_NAME = "channels_start_source";
static const std::string CHANNELS_START_MODE_PROP_NAME = "channels_start_mode";
static const std::string SYNC_MODULE_SFP_STATUSES_PROP_NAME = "sync_module_sfp_statuses";
static const std::string RF_MODULE_SFP_STATUSES_PROP_NAME = "rf_module_sfp_statuses";
static const std::string SYNC_MODULE_STATUSES_PROP_NAME = "sync_module_statuses";
static const std::string RF_MODULE_STATUSES_PROP_NAME = "rf_module_statuses";
static const std::string SYNC_MODULE_DES_LOCK_PROP_NAME = "sync_module_des_lock";
static const std::string SYNC_MODULE_OSC_LOCK_PROP_NAME = "sync_module_osc_lock";

static const std::string SET_CHANNEL_DELAY_COMM_NAME = "set_channel_delay";
static const std::string GET_CHANNEL_DELAY_COMM_NAME = "get_channel_delay";
static const std::string SET_CHANNEL_WIDTH_COMM_NAME = "set_channel_width";
static const std::string GET_CHANNEL_WIDTH_COMM_NAME = "get_channel_width";
static const std::string SET_CHANNEL_ENABLED_COMM_NAME = "set_channel_enabled";
static const std::string IS_CHANNEL_ENABLED_COMM_NAME = "is_channel_enabled";
static const std::string SET_CHANNEL_INVERTED_COMM_NAME = "set_channel_inverted";
static const std::string IS_CHANNEL_INVERTED_COMM_NAME = "is_channel_inverted";
static const std::string SET_CHANNEL_START_SOURCE_COMM_NAME = "set_channel_start_source";
static const std::string GET_CHANNEL_START_SOURCE_COMM_NAME = "get_channel_start_source";
static const std::string SET_CHANNEL_START_MODE_COMM_NAME = "set_channel_start_mode";
static const std::string GET_CHANNEL_START_MODE_COMM_NAME = "get_channel_start_mode";
static const std::string GET_CHANNEL_NAME_COMM_NAME = "get_channel_name";
static const std::string SET_CHANNEL_NAME_COMM_NAME = "set_channel_name";
static const std::string SET_INNER_START_PERIOD_COMM_NAME = "set_inner_start_period";
static const std::string GET_INNER_START_PERIOD_COMM_NAME = "get_inner_start_period";
static const std::string SET_INNER_START_WIDTH_COMM_NAME = "set_inner_start_width";
static const std::string GET_INNER_START_WIDTH_COMM_NAME = "get_inner_start_width";
static const std::string SET_INNER_START_ENABLED_COMM_NAME = "set_inner_start_enabled";
static const std::string IS_INNER_START_ENABLED_COMM_NAME = "is_inner_start_enabled";
static const std::string SET_INNER_START_INVERTED_COMM_NAME = "set_inner_start_inverted";
static const std::string IS_INNER_START_INVERTED_COMM_NAME = "is_inner_start_inverted";
static const std::string GET_SYNC_MODULE_STATUSES_COMM_NAME = "get_sync_module_statuses";
static const std::string GET_RF_MODULE_STATUSES_COMM_NAME = "get_rf_module_statuses";
static const std::string GET_SYNC_SFP_PARAMS_COMM_NAME = "get_sync_sfp_params";
static const std::string GET_RF_SFP_PARAMS_COMM_NAME = "get_rf_sfp_params";
static const std::string GET_SYNC_DES_LOCK_COMM_NAME = "get_sync_des_lock";
static const std::string GET_SYNC_OSC_LOCK_COMM_NAME = "get_sync_osc_lock";


#endif //EPSS13_STANDALONE_SERVER_EPSS13_SRC_CONSTS_H_
