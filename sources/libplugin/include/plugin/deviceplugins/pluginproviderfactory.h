#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_PLUGINPROVIDERFACTORY_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_PLUGINPROVIDERFACTORY_H_

#include "pluginprovider.h"

struct TestPluginProviderRequest {
  std::string name;
  std::string description;
};

struct TestPluginProviderResponse {
  std::shared_ptr<PluginProvider> plugin_provider = nullptr;
};

class PluginProviderFactory {
 public:
  virtual TestPluginProviderResponse createPluginProvider(TestPluginProviderRequest request) = 0;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_PLUGINPROVIDERFACTORY_H_
