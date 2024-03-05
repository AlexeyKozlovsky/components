#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_PLUGINPROVIDERFACTORY_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_PLUGINPROVIDERFACTORY_H_

#include "pluginprovider.h"
#include "plugin/storages/pluginproviderstorage.h"
#include <plugin/export.h>


struct PluginProviderRequest {
  std::string name;
  std::string description;
  std::string data;
};

struct PluginProviderResponse {
  std::shared_ptr<PluginProvider> plugin_provider = nullptr;
};


class PLUGIN_EXPORT PluginProviderFactory {
 public:
  explicit PluginProviderFactory(const std::shared_ptr<QWidget> &plugin_provider_factory_view,
                                 const std::shared_ptr<PluginProviderStorage> &plugin_provider_storage,
                                 const std::shared_ptr<ThreadPoolBuilder> &thread_pool_builder);

  virtual PluginProviderResponse createPluginProvider(PluginProviderRequest request) = 0;
  virtual ErrorCode destroyPluginProvider(const std::string &uid);

  virtual std::shared_ptr<QWidget> getPluginProviderFactoryView();

 protected:
  std::shared_ptr<QWidget> _plugin_provider_factory_view = nullptr;
  std::shared_ptr<PluginProviderStorage> _plugin_provider_storage = nullptr;
  std::shared_ptr<ThreadPoolBuilder> _thread_pool_builder = nullptr;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_PLUGINPROVIDERFACTORY_H_
