#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_ABSTRACTS_CREATIONPART_CREATIONPARTFACTORY_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_ABSTRACTS_CREATIONPART_CREATIONPARTFACTORY_H_

#include <memory>

#include <modbuswrappers/modbuswrapperfactory.h>
#include <utils/services/uidgenerator.h>

#include "plugin/storages/pluginproviderstorage.h"
#include "plugin/storages/pluginproviderfactorystorage.h"

#include "plugin/deviceplugins/pluginproviderfactory.h"


struct CreationPartFactoryRequest {
  std::shared_ptr<PluginProviderStorage> device_pack_storage = nullptr;
  std::shared_ptr<ModbusWrapperFactory> modbus_wrapper_factory = nullptr;
  std::shared_ptr<ThreadPoolBuilder> thread_pool_builder = nullptr;
  std::shared_ptr<UIDGenerator> uid_generator = nullptr;

  std::shared_ptr<PluginProviderFactoryStorage> plugin_provider_factory_storage = nullptr;
};

struct CreationPartFactoryResponse {
  std::shared_ptr<PluginProviderFactory> plugin_provider_factory = nullptr;
  std::shared_ptr<QWidget> view = nullptr;
};

class CreationPartFactory {
 public:
  virtual CreationPartFactoryResponse createCreationPart(CreationPartFactoryRequest request) = 0;
};

#define DevicePluginInterface_iid "org.dialtek.syncsys.device-plugin"
Q_DECLARE_INTERFACE(CreationPartFactory, DevicePluginInterface_iid)

#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_ABSTRACTS_CREATIONPART_CREATIONPARTFACTORY_H_
