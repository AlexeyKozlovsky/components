#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_PLUGINFACTORY_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_PLUGINFACTORY_H_

#include <memory>

#include "plugin/storages/pluginproviderstorage.h"
#include "modbuswrappers/modbuswrapperfactory.h"
#include "threadpooling/threadpoolbuilder.h"


#include "pluginprovider.h"
#include "pluginproviderfactory.h"

#include <utils/services/uidgenerator.h>

#include <QtPlugin>

struct CreatePluginProviderRequest {
  std::shared_ptr<PluginProviderStorage> device_plugin_storage = nullptr;

  std::shared_ptr<ModbusWrapperFactory> modbus_wrapper_factory = nullptr;
  std::shared_ptr<ThreadPoolBuilder> thread_pool_builder = nullptr;
  std::shared_ptr<UIDGenerator> uid_generator = nullptr;
};



struct CreatePluginProviderResponse {
  std::shared_ptr<QWidget> plugin_provider_factory_view = nullptr;
};


class PluginFactory {
 public:
  virtual ~PluginFactory() {};
  virtual CreatePluginProviderResponse createPluginProvider(CreatePluginProviderRequest request) = 0;
};


#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_PLUGINFACTORY_H_
