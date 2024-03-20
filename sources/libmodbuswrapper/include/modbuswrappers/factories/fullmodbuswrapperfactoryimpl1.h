#ifndef MODBUSWRAPPERS_SRC_MODBUSWRAPPERS_FACTORIES_FULLMODBUSWRAPPERFACTORYIMPL1_H_
#define MODBUSWRAPPERS_SRC_MODBUSWRAPPERS_FACTORIES_FULLMODBUSWRAPPERFACTORYIMPL1_H_

#include "modbuswrappers/modbuswrapperfactory.h"
#include "modbuswrappers/modbuswrapperstorage.h"

#include <modbuswrappers/export.h>

class MODBUSWRAPPERS_EXPORT FullModbusWrapperFactoryImpl1: public ModbusWrapperFactory {
 public:
  explicit FullModbusWrapperFactoryImpl1();

  std::shared_ptr<ModbusWrapper> createModbusWrapper(const std::string &ip,
                                                     int port,
                                                     int modbus_id,
                                                     int holding_regs_count,
                                                     int input_regs_count) override;
  std::shared_ptr<ModbusWrapper> createBaseModbusWrapper(const std::string &ip, int port) override;

 private:
  std::shared_ptr<ModbusWrapperFactory> _base_modbus_wrapper_factory = nullptr;
  std::shared_ptr<ModbusWrapperFactory> _modbus_wrapper_factory = nullptr;
  std::shared_ptr<ModbusWrapperStorage> _modbus_wrapper_storage = nullptr;
};

#endif //MODBUSWRAPPERS_SRC_MODBUSWRAPPERS_FACTORIES_FULLMODBUSWRAPPERFACTORYIMPL1_H_
