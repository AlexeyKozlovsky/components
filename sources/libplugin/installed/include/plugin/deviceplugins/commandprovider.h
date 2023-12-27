#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_COMMANDPROVIDER_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_COMMANDPROVIDER_H_

#include <string>

#include <QVariant>
#include <utils/baseutils.h>

struct CommandRequest {
  const std::string command_name;
  QVariant request;
};

struct CommandResponse {
  ErrorCode error_code = OPERATION_INTERRUPTED;
  QVariant response;
};

class PluginCommandProvider {
 public:
  virtual bool hasCommand(const std::string &command_name) = 0;
  virtual CommandResponse executeCommand(CommandRequest request) = 0;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_COMMANDPROVIDER_H_
