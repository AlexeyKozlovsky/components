#include "modbuswrappers/modbuswrapper.h"

void ModbusWrapper::addConnectable(const std::shared_ptr<Connectable> &connectable) {
  _connectables.push_back(connectable);
}

void ModbusWrapper::sendConnectionStatus(bool connection_status) {
  std::for_each(std::begin(_connectables), std::end(_connectables), [&](const std::shared_ptr<Connectable> &connectable) {
    connectable->setConnectionStatus(connection_status);
  });
}

void ModbusWrapper::process() {

}
