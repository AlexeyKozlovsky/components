#ifndef TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_COMMANDPROVIDER_H_
#define TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_COMMANDPROVIDER_H_

#include <string>
#include <memory>

#include <QVariant>
#include <utils/baseutils.h>

struct CommandRequest {
  const QString &command_name;
  QVariant request;
};

struct CommandResponse {
  ErrorCode error_code = OPERATION_INTERRUPTED;
  QVariant response;
};

class Command {
 public:
  virtual QVariant execute(QVariant request) = 0;
};

class PluginCommandProvider {
 public:
  virtual bool hasCommand(const QString &command_name) = 0;
  virtual CommandResponse executeCommand(CommandRequest request) = 0;

  virtual ErrorCode addCommand(const QString &command_name,
                               const std::shared_ptr<Command> &command) = 0;
  virtual ErrorCode removeCommand(const QString &command_name) = 0;
};

#endif //TEST_PROJECT_WITH_MODULE_ARCH_DEVICEPLUGINS_COMMANDPROVIDER_H_
