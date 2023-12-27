#ifndef TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_DEVICEPACK_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_DEVICEPACK_H_

#include <memory>

#include "plugin/deviceplugins/pluginprovider.h"


class DevicePack {
 public:
  virtual std::shared_ptr<PluginProvider> getPluginProvider() = 0;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_STORAGES_DEVICEPACK_H_
