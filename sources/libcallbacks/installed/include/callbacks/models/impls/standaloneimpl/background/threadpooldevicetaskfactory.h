#ifndef TEST_PROJECT_WITH_MODULE_ARCH_SERVICES_MODELS_IMPLS_STANDALONEIMPL_BACKGROUND_THREADPOOLDEVICETASKFACTORY_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_SERVICES_MODELS_IMPLS_STANDALONEIMPL_BACKGROUND_THREADPOOLDEVICETASKFACTORY_H_

#include "threadpooling/iprocessable.h"

#include "modbuswrappers/modbuswrapper.h"



class ThreadPoolDeviceTaskFactory {
 public:
  virtual std::shared_ptr<IProcessable> createTask(const std::shared_ptr<ModbusWrapper> &modbus_wrapper,
                                                   const std::shared_ptr<IProcessable> &base_device_entity) = 0;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_SERVICES_MODELS_IMPLS_STANDALONEIMPL_BACKGROUND_THREADPOOLDEVICETASKFACTORY_H_
