
#include "modbuswrappers/modbusasyncclientwrapper/modbuswrapperpoll.h"

ModbusWrapperPoll::ModbusWrapperPoll(const std::shared_ptr<ModbusAsyncClientWrapper> &modbus_client_wrapper):
 _modbus_async_client_wrapper(modbus_client_wrapper) {

}

void ModbusWrapperPoll::process() {
  if (_modbus_async_client_wrapper != nullptr) {
    _modbus_async_client_wrapper->process();
  }
}
