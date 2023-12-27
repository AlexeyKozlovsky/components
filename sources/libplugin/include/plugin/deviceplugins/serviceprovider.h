#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_SERVICEPROVIDER_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_SERVICEPROVIDER_H_

#include <memory>
#include <string>

#include "threadpooling/iprocessable.h"

class PluginServiceProvider {
 public:
  virtual std::shared_ptr<IProcessable> getBackgroundTask() = 0;

  virtual bool hasBackgroundTaskByKey(const std::string &key) = 0;
  virtual std::shared_ptr<IProcessable> getBackgroundTaskByKey(const std::string &key) = 0;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_SERVICEPROVIDER_H_
