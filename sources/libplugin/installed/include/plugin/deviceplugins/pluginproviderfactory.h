#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_PLUGINPROVIDERFACTORY_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_PLUGINPROVIDERFACTORY_H_

#include "pluginprovider.h"

struct PluginProviderRequest {
  std::string name;
  std::string description;
};

struct PluginProviderResponse {
  std::shared_ptr<PluginProvider> plugin_provider = nullptr;
};

class PluginProviderFactory {
 public:
  virtual PluginProviderResponse createPluginProvider(PluginProviderRequest request) = 0;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_PLUGINPROVIDERFACTORY_H_
