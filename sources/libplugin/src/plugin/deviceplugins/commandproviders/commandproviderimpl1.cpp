#include "plugin/deviceplugins/commandproviders/commandproviderimpl1.h"

bool CommandProviderImpl1::hasCommand(const QString &command_name) {
  bool result = _commands.contains(command_name);
  return result;
}

CommandResponse CommandProviderImpl1::executeCommand(CommandRequest request) {
  CommandResponse response{};

  auto command_name = request.command_name;
  auto command_request = request.request;


  if (hasCommand(request.command_name)) {
    auto command = _commands[command_name];

    if (command != nullptr) {
      auto command_response = command->execute(command_request);
      response.response = command_response;
      response.error_code = SUCCESS;
    } else {
      response.error_code = INVALID_REQUEST;
    }
  }

  return response;
}

ErrorCode CommandProviderImpl1::addCommand(const QString &command_name, const std::shared_ptr<Command> &command) {
  ErrorCode result = OPERATION_INTERRUPTED;

  if (!hasCommand(command_name)) {
    _commands.insert(command_name, command);
    result = SUCCESS;
  }

  return result;
}

ErrorCode CommandProviderImpl1::removeCommand(const QString &command_name) {
  ErrorCode result = OPERATION_INTERRUPTED;

  if (hasCommand(command_name)) {
    _commands.remove(command_name);
    result = SUCCESS;
  }

  return result;
}
