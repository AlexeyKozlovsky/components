#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_ABSTRACTS_MANAGEMENTPART_MANAGEMENTPARTFACTORY_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_ABSTRACTS_MANAGEMENTPART_MANAGEMENTPARTFACTORY_H_

#include <memory>

#include "plugin/storages/pluginproviderstorage.h"
#include "modbuswrappers/modbuswrapperfactory.h"
#include "plugin/deviceplugins/pluginprovider.h"

struct ManagementPartFactoryRequest {
  std::shared_ptr<PluginProviderStorage> device_pack_storage = nullptr;

  std::shared_ptr<ModbusWrapperFactory> modbus_wrapper_factory = nullptr;
  std::shared_ptr<ThreadPoolBuilder> thread_pool_builder = nullptr;
};

struct ManagementPartFactoryResponse {
  std::shared_ptr<PluginProvider> plugin_provider = nullptr;
};


class ManagementPartFactory {
 public:
  virtual ManagementPartFactoryResponse createManagementPart(ManagementPartFactoryRequest request) = 0;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_ABSTRACTS_MANAGEMENTPART_MANAGEMENTPARTFACTORY_H_
