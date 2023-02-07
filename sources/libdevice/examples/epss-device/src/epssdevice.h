#ifndef LIBDEVICE_EXAMPLES_EPSS_DEVICE_DEVICE_H_
#define LIBDEVICE_EXAMPLES_EPSS_DEVICE_DEVICE_H_

#include <devices/modbus/modbusdevice.h>


class EPSSDevice: public ModbusDevice {
 public:
  std::shared_ptr<EPSSDevice> createEPSSDevice(const std::string &name,
                                               const std::string &ip,
                                               int port,
                                               int modbus_id,
                                               ErrorCode *error_code = nullptr);

 protected:
  EPSSDevice(const std::string &name, const std::shared_ptr<ModbusClient> &modbus_client);
};


#endif //LIBDEVICE_EXAMPLES_EPSS_DEVICE_DEVICE_H_
